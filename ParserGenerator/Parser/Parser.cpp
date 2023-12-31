#include <stack>
#include <random>
#include <algorithm>
#include "Parser.h"

#include <memory>


bool operator==(const Definition* lhs, const Token& rhs) {
    return lhs->getIsTerminal() && lhs->getName() == rhs.type;
}

bool operator==(const Token& lhs, const Definition* rhs) {
    return rhs->getIsTerminal() && lhs.type == rhs->getName();
}

bool operator==(const ParseTreeNode& lhs, const Token& rhs) {
    return lhs.content == rhs;
}

bool operator==(const Token& lhs, const ParseTreeNode& rhs) {
    return lhs == rhs.content;
}

Parser::Parser(const unordered_map<Definition *, unordered_map<string, vector<Definition *>>>& parsingTable)
    : table(parsingTable) {
}

std::shared_ptr<const ParseTreeNode> Parser::parse(LexicalAnalyzer& lexicalAnalyzer, Definition* startSymbol) {
    // Initialize a stack of parseTree nodes
    stack<std::shared_ptr<ParseTreeNode>> nodeStack;
    Token currentToken;

    // Define repetitive routines
    auto nextToken = [&]() {
        currentToken = lexicalAnalyzer.getNextToken();
    };
    auto matchToken = [&]() {
        nodeStack.pop();
        nextToken();
    };
    // The parse tree root node (has the start symbol)
    const auto rootNode = std::make_shared<ParseTreeNode>(startSymbol);

    // Push $ node  into the stack
    nodeStack.push(std::make_shared<ParseTreeNode>(Definition::getDollar()));
    // Push the root node into the stack
    nodeStack.push(rootNode);
    // Read first Token
    nextToken();
    while (!nodeStack.empty()) {
        auto stackTopNode = nodeStack.top();

        if ((currentToken.isEOF && stackTopNode.get()->content == Definition::getDollar()) || (
                !currentToken.isEOF && currentToken == *stackTopNode)) {
            matchToken();
            continue;
        }

        if (stackTopNode->getIsTerminal()) {
            // Error Recovery: insert the stack top onto the input, match and continue.
            cerr << "Error, inserting " << stackTopNode->content->getName() << " onto the input" << endl;
            matchToken();
            continue;
        }
        Definition* row = stackTopNode->content;
        if (table.find(row) == table.end()) {
            throw out_of_range("No such row in the parsing table!");
        }
        // Specify what column of the table corresponds to the current token.
        string column = currentToken.type;
        if (currentToken.isEOF) {
            column = Definition::DOLLAR;
        }
        auto productionEntry = table[row].find(column);
        if (const bool productionExists = (productionEntry != table[row].end()); !productionExists) {
            // Empty table cell
            if (currentToken.isEOF) {
                break;
            }
            cerr << "Error, discarding " << currentToken.type << " from the input." << endl;
            nextToken();
            continue;
        }
        // Extract the production rule
        auto production = productionEntry->second;
        if (production.empty()) {
            // Sync rule
            cerr << "Error, sync popping " << row->getName() << " from the stack." << endl;
            nodeStack.pop();
            continue;
        }
        // Non-sync rule is found:
        nodeStack.pop();
        for (int k = static_cast<int>(production.size()) - 1; k >= 0; k--) {
            auto childNode = std::make_shared<ParseTreeNode>(production[k]);
            stackTopNode->insertLeft(childNode);
            if (production[k] != Definition::getEpsilon()) {
                nodeStack.push(childNode);
            }
        }
    }
    if (!lexicalAnalyzer.isEOF() || !currentToken.isEOF) {
        cerr << "Excess tokens:" << endl;
        if (!currentToken.isEOF) {
            cerr << "    -" << currentToken.type << endl;
        }
        while (!lexicalAnalyzer.isEOF()) {
            cerr << "    -" << lexicalAnalyzer.getNextToken().type << endl;
        }
    }
    if (!nodeStack.empty()) {
        cerr << "Error: Unexpected End Of File." << endl;
    }
    return rootNode;
}
