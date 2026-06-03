//
// Created by mcoto on 5/31/2026.
//

#include "SpellStrategy.h"

SpellStrategy::SpellStrategy(int maxMana) {
    this->maxMana = maxMana;
    this-> mana = maxMana;
}

bool SpellStrategy::canCast() const{
    return mana > 0;
}

double SpellStrategy::calculateDamage(int baseDamage) const {
    return baseDamage * 1.5;
}

unique_ptr<DamageStrategy> SpellStrategy::clone() const {
    return make_unique<SpellStrategy>(maxMana);
}
