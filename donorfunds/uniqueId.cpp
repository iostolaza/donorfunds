
#include "uniqueId.hpp"

uniqueID::uniqueID() : gen(rd()), dis(0, 15) {}

string uniqueID::generateRandomID() {
    string id;
    for (int i = 0; i < 16; ++i) {
        id += "0123456789ABCDEF"[dis(gen)];
    }
    return id;
}

string uniqueID::generateUniqueID() {
    string newID;
    do {
        newID = generateRandomID();
    } while (!isUnique(newID));
    addID(newID);
    return newID;
}

bool uniqueID::isUnique(const string& id) {
    return idSet.find(id) == idSet.end();
}

void uniqueID::addID(const string& id) {
    idSet.insert(id);
}

void uniqueID::removeID(const string& id) {
    idSet.erase(id);
}
