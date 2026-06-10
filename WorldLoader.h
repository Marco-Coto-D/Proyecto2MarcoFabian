//
// Created by mcoto on 6/9/2026.
//

#ifndef PROYECTO2MARCOFABIAN_WORLDLOADER_H
#define PROYECTO2MARCOFABIAN_WORLDLOADER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <stdexcept>
#include "World.h"
#include "Goblin.h"
#include "Dragon.h"
#include "Mage.h"
#include "Villager.h"
#include "SwordStrategy.h"
#include "BowStrategy.h"
#include "SpellStrategy.h"
using namespace std;


class WorldLoader {
public:
    World load(
        const string& configPath,
        const string& worldPath,
        const string& entitiesPath,
        const string& villagerStockPath,
        const string& armorStockPath
    );
    int getBandagePrice() const;
    int getBandageHeal() const;

private:
    int bandagePrice;
    int bandageHeal;
    string startRoomId;
    vector<string> villagerIds;
    vector<Villager*> villagerPtrs;

    void loadConfig(const string& path, World& world);
    void loadWorld(const string& path, World& world);
    void loadEntities(const string& path, World& world);
    void loadVillagerStock(const string& path, World& world);
    void loadArmorStock(const string& path, World& world);
    unique_ptr<DamageStrategy> makeStrategy(const string& type, int maxMana, int lineNum, const string& file);
};

#endif //PROYECTO2MARCOFABIAN_WORLDLOADER_H
