//
// Created by mcoto on 5/31/2026.
//

#ifndef PROYECTO2MARCOFABIAN_ARMOR_H
#define PROYECTO2MARCOFABIAN_ARMOR_H
#include <iostream>
using namespace std;


class Armor {
    private:
    string name;
    int damageReduction = 0;
    public:
    Armor(string name, int damageReduction);
    string getName() const;
    int getDamageReduction() const;
};



#endif //PROYECTO2MARCOFABIAN_ARMOR_H
