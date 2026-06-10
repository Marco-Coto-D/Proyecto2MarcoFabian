//
// Created by mcoto on 6/9/2026.
//

#ifndef PROYECTO2MARCOFABIAN_SIMULATIONENGINE_H
#define PROYECTO2MARCOFABIAN_SIMULATIONENGINE_H
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
#include "World.h"
#include "Logger.h"
#include "ReportGenerator.h"
#include "Mage.h"
#include "Villager.h"

class SimulationEngine {
public:
    SimulationEngine(World& world, Logger& logger, int bandageHealAmount, int bandagePrice);
    void run();

private:
    World& world;
    Logger& logger;
    int goblinsKilled;
    int magesKilled;
    int dragonsKilled;
    vector<string> visitedRooms;
    int turnCount;
    int bandageHealAmount;
    int bandagePrice;
    bool gameOver;
    bool victory;
    string previousRoomId;
    void runRoom(Room* room);
    Entity* rollEncounter(Room* room);
    void runCombat(Enemy* enemy, Room* room);
    void doKnightAttack(Enemy& target);
    void doEnemyAttack(Enemy& attacker);
    bool handleMainMenu(Room* room, Villager* villager, bool isDungeon, bool canExplore);
    void handleMove(Room* room);
    void handleVillagerInteraction(Villager* villager);
    void waitForEnter();
};

#endif //PROYECTO2MARCOFABIAN_SIMULATIONENGINE_H
