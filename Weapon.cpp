//
// Created by mcoto on 5/31/2026.
//

#include "Weapon.h"
#include "SpellStrategy.h"
#include "BowStrategy.h"

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

string Weapon::getStrategyType() const {
    if (dynamic_cast<const SpellStrategy*>(damageStrategy.get())) return "spell";
    if (dynamic_cast<const BowStrategy*>(damageStrategy.get()))   return "bow";
    return "sword";
}

bool Weapon::canCast() const {
    const SpellStrategy* ss = dynamic_cast<const SpellStrategy*>(damageStrategy.get());
    if (ss == nullptr) return true;
    return ss->canCast();
}

void Weapon::regenerateMana() const {
    const SpellStrategy* ss = dynamic_cast<const SpellStrategy*>(damageStrategy.get());
    if (ss != nullptr) ss->regenerate();
}

void Weapon::consumeMana(int amount) const {
    const SpellStrategy* ss = dynamic_cast<const SpellStrategy*>(damageStrategy.get());
    if (ss != nullptr) ss->consumeMana(amount);
}
