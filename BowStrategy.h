//
// Created by mcoto on 5/31/2026.
//

#ifndef PROYECTO2MARCOFABIAN_BOWSTRATEGY_H
#define PROYECTO2MARCOFABIAN_BOWSTRATEGY_H
#include "DamageStrategy.h"



class BowStrategy : public DamageStrategy{
    public:
    double calculateDamage(int baseDamage) const override;
    unique_ptr<DamageStrategy> clone() const override;
};



#endif //PROYECTO2MARCOFABIAN_BOWSTRATEGY_H
