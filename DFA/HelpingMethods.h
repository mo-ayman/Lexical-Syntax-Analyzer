#ifndef HELPINGMETHODS_H
#define HELPINGMETHODS_H
using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

class HelpingMethods {
public:
    void printSet(const std::set<int>& mySet);
    void printVector(const std::vector<int>& myvec);
    void printvecMapSet(std::vector<map<char, set<int>>>& vec);
    void finalMap(map<int, string>& map);
};

#endif