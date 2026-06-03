//
// Created by mcoto on 5/31/2026.
//

#include "SwordStrategy.h"

double SwordStrategy::calculateDamage(int baseDamage) const {
    return baseDamage;
}

unique_ptr<DamageStrategy> SwordStrategy::clone() const {
    return make_unique<SwordStrategy>();
}
