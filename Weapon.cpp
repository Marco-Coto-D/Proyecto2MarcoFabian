//
// Created by mcoto on 5/31/2026.
//

#include "Weapon.h"

Weapon::Weapon(string name, int baseDamage, unique_ptr<DamageStrategy> damageStrategy) {
    this->name = name;
    this->baseDamage = baseDamage;
    this-> damageStrategy = move(damageStrategy);
}

Weapon::Weapon(const Weapon &other) {
    this->name = other.name;
    this->baseDamage = other.baseDamage;
    this->damageStrategy = other.damageStrategy->clone();
}

double Weapon::calculateDamage() const {
    return damageStrategy->calculateDamage(baseDamage);
}

bool Weapon::operator<(const Weapon& other) const {
    return this->baseDamage < other.baseDamage;
}

string Weapon::getName() const {
    return name;
}

int Weapon::getBaseDamage() const {
    return baseDamage;
}
