//
// Created by mcoto on 5/31/2026.
//

#ifndef PROYECTO2MARCOFABIAN_SPELLSTRATEGY_H
#define PROYECTO2MARCOFABIAN_SPELLSTRATEGY_H
#include "DamageStrategy.h"


class SpellStrategy : public DamageStrategy {
    private:
    int mana;
    int maxMana;
    public:
    SpellStrategy(int maxMana);
    bool canCast() const;
    double calculateDamage(int baseDamage) const override;
};



#endif //PROYECTO2MARCOFABIAN_SPELLSTRATEGY_H
