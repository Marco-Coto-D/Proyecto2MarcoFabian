//
// Created by mcoto on 5/31/2026.
//

#ifndef PROYECTO2MARCOFABIAN_DAMAGESTRATEGY_H
#define PROYECTO2MARCOFABIAN_DAMAGESTRATEGY_H

class DamageStrategy {
    public:
    virtual double calculateDamage(int baseDamage) const = 0;
    virtual ~DamageStrategy() = default;
};

#endif //PROYECTO2MARCOFABIAN_DAMAGESTRATEGY_H
