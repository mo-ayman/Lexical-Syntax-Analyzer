#ifndef DFA_H
#define DFA_H

#include <vector>
#include <string>
#include <map>
#include <queue>
#include <set>
#include <tuple>
#include <unordered_map>

#include "../LexicalRules/RuleTree.h"

class DFA {
    std::vector<std::map<char, std::set<int>>> TransitionTable;
    std::unordered_map<int, std::tuple<std::string, Priority, int>> finalStates;
    int initialState;
    std::vector<std::map<char, int>> DFA_States;

    //this for DFA
    // this map for storing each state and it's maping states under sone input
    std::map<std::set<int>, std::vector<std::set<int>>> stateMap;
    // this map for storing each state and it's maping input in same order of stateMap
    std::map<std::set<int>, std::vector<char>> InputMap;
    // this queue used to check that i visited all states 
    std::queue<std::set<int>> QueueStates;
    //This is the new final states after DFA is done
    std::unordered_map<int, std::tuple<std::string, Priority, int>> New_finalStates;

public:
    DFA(const std::vector<std::map<char, std::vector<int>>>& table,const std::unordered_map<int, std::tuple<std::string, Priority, int>>& finals, int initial);

    std::vector<std::map<char, int>> getDFA();

    void fillDFA();

    std::map<std::set<int>, int> makeEachStateIndx();

    void handleState(std::set<int>& states);

    std::unordered_map<int, std::tuple<std::string, Priority, int>> getFinalStates();

    void updateFinalStates(int indx, const std::set<int>& OldState);

    static std::tuple<std::string, Priority, int> bestFinal( std::vector<std::tuple<std::string, Priority, int>>& temp_final_states);
};

#endif
