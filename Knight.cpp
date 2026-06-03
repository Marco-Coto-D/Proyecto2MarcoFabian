//
// Created by mcoto on 5/31/2026.
//

#include "Knight.h"

Knight::Knight(string name, string description, int health, int maxHealth, int gold, unique_ptr<Weapon> equippedWeapon,
    unique_ptr<Armor> equippedArmor): Entity(name, description) {
    this->health = health;
    this->maxHealth = maxHealth;
    this->gold = gold;
    this->equippedWeapon = move(equippedWeapon);
    this->equippedArmor = move(equippedArmor);
}

void Knight::sortWeapon() {
    for (int i = 0; i < inventory.size(); i++) {
        for (int j = 0; j < inventory.size() - i - 1; j++) {
            if (*inventory[j] < *inventory[j + 1]) {
                swap(inventory[j], inventory[j + 1]);
            }
        }
    }
    equippedWeapon = move(inventory[0]);
    inventory.erase(inventory.begin());
}

void Knight::addWeapon(Weapon* other) {
    inventory.push_back(make_unique<Weapon>(*other));
}

string Knight::describe() const {
    return description;
}

int Knight::getHealth() const {
    return health;
}

int Knight::getMaxHealth() const {
    return maxHealth;
}

int Knight::getGold() const {
    return gold;
}

const Weapon & Knight::getEquippedWeapon() const {
    return *equippedWeapon;
}

const Armor & Knight::getEquippedArmor() const {
    return *equippedArmor;
}

void Knight::spendGold(int gold) {
    this->gold = this->gold - gold;
}
