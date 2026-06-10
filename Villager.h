//
// Created by mcoto on 6/2/2026.
//

#ifndef PROYECTO2MARCOFABIAN_VILLAGER_H
#define PROYECTO2MARCOFABIAN_VILLAGER_H
#include <vector>
#include "Knight.h"
#include "Entity.h"
#include "Weapon.h"


class Villager : public Entity {
    private:
    vector<unique_ptr<Weapon>> stock;
    vector<int> prices;
    string id;
    public:
    Villager(string id, string name, string description);
    void sortStock();
    void addWeapon(unique_ptr<Weapon> other, int price);
    unique_ptr<Weapon> giveLoot();
    void getAvailableWeapons() const;
    string getId() const;
    bool sellWeapon(int index, Knight& buyer);
    string describe() const override;
    int getStockSize() const;
};



#endif //PROYECTO2MARCOFABIAN_VILLAGER_H
