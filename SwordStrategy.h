//
// Created by mcoto on 5/31/2026.
//

#ifndef PROYECTO2MARCOFABIAN_SWORDSTRATEGY_H
#define PROYECTO2MARCOFABIAN_SWORDSTRATEGY_H
#include "DamageStrategy.h"


class SwordStrategy : public DamageStrategy{
    public:
    double calculateDamage(int baseDamage) const override;
};



#endif //PROYECTO2MARCOFABIAN_SWORDSTRATEGY_H
