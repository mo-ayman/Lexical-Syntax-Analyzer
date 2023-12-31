#ifndef PPT_H
#define PPT_H

#include <string> 
#include <vector>
#include <map>
#include <unordered_map>
#include "../Definition/Definition.h"
using namespace std;


class PPT {
private:
    unordered_map<Definition*,unordered_map<string,vector<Definition*>>>* PPTable =new unordered_map<Definition*,unordered_map<string,vector< Definition*>>>();

public:
    [[nodiscard]] unordered_map<Definition*, unordered_map<string, vector<Definition*>>>* pp_table() const;

private:
    map<Definition*, vector<vector<Definition*>>> InputRulesM;
    map<Definition*, vector<pair<int, Definition*>>> firstM;
    map<Definition*, vector<Definition*>> followM;
public:
    PPT(const map<Definition*, vector<vector<Definition *>>>& InputRules, map<Definition*, vector<pair<int,Definition*>>>& first, map<Definition*,vector<Definition*>>& follow);
    unordered_map<Definition*, unordered_map<string, vector<Definition*>>>* computePPT();
    void fillFirstChunck();
    void fillFollowChunck();
    static int checkEpslon(const vector<pair<int, Definition *>>& mappingFirst);
    static void print(unordered_map<Definition*, unordered_map<string, vector<Definition*>>>* table);
};

#endif
