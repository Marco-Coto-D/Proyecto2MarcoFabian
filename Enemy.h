//
// Created by mcoto on 5/31/2026.
//

#ifndef PROYECTO2MARCOFABIAN_ENEMY_H
#define PROYECTO2MARCOFABIAN_ENEMY_H
#include <iostream>
using namespace std;
#include <memory>
#include "Weapon.h"
#include "Armor.h"
#include "Entity.h"


class Enemy : public Entity {
    private:
    int health;
    int maxHealth;
    unique_ptr<Weapon> equippedWeapon;
    unique_ptr<Armor> equippedArmor;
    public:
    Enemy(string name, string description, int health, int maxHealth, unique_ptr<Weapon> equippedWeapon, unique_ptr<Armor> equippedArmor);
    string describe() const override;
    int getHealth() const;
    int getMaxHealth() const;
    const Weapon& getEquippedWeapon() const;
    const Armor& getEquippedArmor() const;
};



#endif //PROYECTO2MARCOFABIAN_ENEMY_H
