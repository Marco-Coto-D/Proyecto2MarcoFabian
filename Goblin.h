//
// Created by mcoto on 6/1/2026.
//

#ifndef PROYECTO2MARCOFABIAN_GOBLIN_H
#define PROYECTO2MARCOFABIAN_GOBLIN_H
#include "Enemy.h"

class Goblin : public Enemy {
    public:
    Goblin(string name, string description, int health, int maxHealth, unique_ptr<Weapon> equippedWeapon, unique_ptr<Armor> equippedArmor, bool isUnique): Enemy(name, description, health, maxHealth, move(equippedWeapon), move(equippedArmor), isUnique) {};
    int getGoldDrop() const override {
        return 20;
    }
};

#endif //PROYECTO2MARCOFABIAN_GOBLIN_H
