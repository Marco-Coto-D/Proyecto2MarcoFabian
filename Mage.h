//
// Created by mcoto on 6/2/2026.
//

#ifndef PROYECTO2MARCOFABIAN_MAGE_H
#define PROYECTO2MARCOFABIAN_MAGE_H
#include "Enemy.h"

class Mage : public Enemy {
    public:
    Mage(string name, string description, int health, int maxHealth, unique_ptr<Weapon> equippedWeapon, unique_ptr<Armor> equippedArmor, bool isUnique): Enemy(name, description, health, maxHealth, move(equippedWeapon), move(equippedArmor), isUnique) {};
};

#endif //PROYECTO2MARCOFABIAN_MAGE_H
