//
// Created by mcoto on 5/31/2026.
//

#ifndef PROYECTO2MARCOFABIAN_SPELLSTRATEGY_H
#define PROYECTO2MARCOFABIAN_SPELLSTRATEGY_H
#include "DamageStrategy.h"


class SpellStrategy : public DamageStrategy {
    private:
    mutable int mana; // mutable so mana can be managed via const references
    int maxMana;
    public:
    SpellStrategy(int maxMana);
    bool canCast() const;
    double calculateDamage(int baseDamage) const override;
    unique_ptr<DamageStrategy> clone() const override;
    void regenerate() const;        // restores 25% of maxMana
    void consumeMana(int amount) const;
    int getMaxMana() const;
};



#endif //PROYECTO2MARCOFABIAN_SPELLSTRATEGY_H
