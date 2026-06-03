//
// Created by mcoto on 5/31/2026.
//

#ifndef PROYECTO2MARCOFABIAN_KNIGHT_H
#define PROYECTO2MARCOFABIAN_KNIGHT_H
#include <iostream>
#include <vector>
using namespace std;
#include "Entity.h"
#include "Weapon.h"
#include "Armor.h"



class Knight : public Entity {
private:
    int health;
    int maxHealth;
    int gold;
    unique_ptr<Weapon> equippedWeapon;
    unique_ptr<Armor> equippedArmor;
    vector<unique_ptr<Weapon>> inventory;
    public:
    Knight(string name, string description, int health, int maxHealth, int gold, unique_ptr<Weapon> equippedWeapon, unique_ptr<Armor> equippedArmor);
    void sortWeapon();
    void addWeapon(Weapon* other);
    string describe() const override;
    int getHealth() const;
    int getMaxHealth() const;
    int getGold() const;
    const Weapon& getEquippedWeapon() const;
    const Armor& getEquippedArmor() const;
    void spendGold(int gold);
};



#endif //PROYECTO2MARCOFABIAN_KNIGHT_H
