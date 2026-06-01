//
// Created by mcoto on 5/31/2026.
//

#ifndef PROYECTO2MARCOFABIAN_WEAPON_H
#define PROYECTO2MARCOFABIAN_WEAPON_H
#include <iostream>
#include <memory>
using namespace std;
#include "DamageStrategy.h"


class Weapon {
private:
    string name;
    int baseDamage;
    unique_ptr<DamageStrategy> damageStrategy;
    public:
    Weapon(string name, int baseDamage, unique_ptr<DamageStrategy>);
    double calculateDamage() const;
    bool operator<(const Weapon& other) const;
    string getName() const;
    int getBaseDamage() const;

};



#endif //PROYECTO2MARCOFABIAN_WEAPON_H
