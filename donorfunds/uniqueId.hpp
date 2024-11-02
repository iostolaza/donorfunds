#ifndef UNIQUEID_HPP
#define UNIQUEID_HPP

#include <string>
#include <unordered_set>
#include <random>

using namespace std;

class uniqueID {
public:
    uniqueID();
    string generateUniqueID();
    bool isUnique(const string& id);
    void addID(const string& id);
    void removeID(const string& id);

private:
    unordered_set<string> idSet;
    random_device rd;
    mt19937 gen;
    uniform_int_distribution<> dis;

    string generateRandomID();
};

#endif /* UNIQUEID_HPP */
