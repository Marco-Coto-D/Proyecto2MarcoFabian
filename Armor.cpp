//
// Created by mcoto on 5/31/2026.
//

#include "Armor.h"


Armor::Armor(string name, int damageReduction) {
    this-> name = name;
    this->damageReduction = damageReduction;
}

string Armor::getName() const {
    return name;
}

int Armor::getDamageReduction() const {
    return damageReduction;
}
