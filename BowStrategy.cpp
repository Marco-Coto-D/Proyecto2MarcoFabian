//
// Created by mcoto on 5/31/2026.
//

#include "BowStrategy.h"

double BowStrategy::calculateDamage(int baseDamage) const {
    return baseDamage - 2;
}

unique_ptr<DamageStrategy> BowStrategy::clone() const {
    return make_unique<BowStrategy>();
}
