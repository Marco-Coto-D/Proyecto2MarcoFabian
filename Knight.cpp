//
// Created by mcoto on 5/31/2026.
//

#include "Knight.h"

Knight::Knight(string name, string description, int health, int maxHealth, int gold, unique_ptr<Weapon> equippedWeapon,
    unique_ptr<Armor> equippedArmor, int bandages): Entity(name, description) {
    this->health = health;
    this->maxHealth = maxHealth;
    this->gold = gold;
    this->bandages = bandages;
    this->equippedWeapon = move(equippedWeapon);
    this->equippedArmor = move(equippedArmor);
}

void Knight::sortWeapon() {
    if (equippedWeapon != nullptr) {
        inventory.push_back(move(equippedWeapon));
    }

    if (inventory.empty()) {
        return;
    }

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

int Knight::getBandages() const {
    return bandages;
}

const Weapon & Knight::getEquippedWeapon() const {
    return *equippedWeapon;
}

const Armor & Knight::getEquippedArmor() const {
    return *equippedArmor;
}

const vector<unique_ptr<Weapon>>& Knight::getInventory() const {
    return inventory;
}

void Knight::spendGold(int gold) {
    this->gold = this->gold - gold;
}

void Knight::gainGold(int amount) {
    this->gold += amount;
}

void Knight::addGold(int amount) {
    this->gold += amount;
}

void Knight::setArmor(unique_ptr<Armor> newArmor) {
    equippedArmor = move(newArmor);
}

void Knight::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

void Knight::heal(int amount) {
    health += amount;
    if (health > maxHealth) health = maxHealth;
}

bool Knight::isDead() const {
    return health <= 0;
}

void Knight::addBandage() {
    this->bandages = bandages + 1;
}

void Knight::useBandage(int healthamount) {
    if (bandages > 0 && health < maxHealth) {
        bandages = bandages - 1;
        int calcHealth = health + healthamount;
        if (calcHealth > maxHealth) {
            health = maxHealth;
        }else {
            health = calcHealth;
        }
    }else if (bandages == 0) {
        cout<<"No tienes vendas disponibles"<<endl;
    }else if (health == maxHealth) {
        cout<<"Ya estas full de vida"<<endl;
    }
}
