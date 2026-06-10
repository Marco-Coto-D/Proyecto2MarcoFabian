//
// Created by mcoto on 5/31/2026.
//

#include "Enemy.h"

Enemy::Enemy(string name, string description, int health, int maxHealth, unique_ptr<Weapon> equippedWeapon,
    unique_ptr<Armor> equippedArmor, bool isUnique) : Entity(name, description) {
    this->health = health;
    this->maxHealth = maxHealth;
    this->equippedWeapon = move(equippedWeapon);
    this->equippedArmor = move(equippedArmor);
    this->isUnique = isUnique;
}

string Enemy::describe() const {
    return description;
}

int Enemy::getHealth() const {
    return health;
}

int Enemy::getMaxHealth() const {
    return maxHealth;
}

bool Enemy::getIsUnique() const {
    return isUnique;
}

const Weapon & Enemy::getEquippedWeapon() const {
    return *equippedWeapon;
}

const Armor & Enemy::getEquippedArmor() const {
    return *equippedArmor;
}
