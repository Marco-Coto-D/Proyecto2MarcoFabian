//
// Created by mcoto on 6/2/2026.
//

#ifndef PROYECTO2MARCOFABIAN_ROOM_H
#define PROYECTO2MARCOFABIAN_ROOM_H
#include <iostream>
#include <vector>
#include <memory>
using namespace std;
#include "Entity.h"



class Room {
    private:
    string id;
    string type;
    string description;
    vector<unique_ptr<Entity>> entities;
    vector<string> connections;
    public:
    Room(string id, string type, string description);
    void addEntity(unique_ptr<Entity> other);
    void addConnection(string other);
    string describe() const;
    string getID() const;
    string getType() const;
    const vector<unique_ptr<Entity>>& getEntities() const;
    const vector<string>& getConnections() const;
};



#endif //PROYECTO2MARCOFABIAN_ROOM_H
