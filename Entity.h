//
// Created by mcoto on 5/31/2026.
//

#ifndef PROYECTO2MARCOFABIAN_ENTITY_H
#define PROYECTO2MARCOFABIAN_ENTITY_H
#include <iostream>
using namespace std;

class Entity {
    protected:
    string name;
    string description;
    public:
    Entity(string name, string description) {
        this->name = name;
        this->description = description;
    }
    virtual ~Entity() = default;
    virtual string describe() const = 0;
    string getName() const {
        return this->name;
    }
    string getDescription() const {
        return this->description;
    }
};

#endif //PROYECTO2MARCOFABIAN_ENTITY_H
