//
// Created by mcoto on 6/9/2026.
//

#include "SimulationEngine.h"


SimulationEngine::SimulationEngine(World &world, Logger &logger, int bandageHealAmount,
                                   int bandagePrice) : world(world), logger(logger) {
    this->bandageHealAmount = bandageHealAmount;
    this->bandagePrice = bandagePrice;
    goblinsKilled = 0;
    magesKilled = 0;
    dragonsKilled = 0;
    turnCount = 0;
    gameOver = false;
    victory = false;
}


void SimulationEngine::run() {
    cout << "=== SIMULACION INICIADA ===" << endl;
    cout << "Bienvenido, " << world.getKnight().getName() << ". El destino del reino esta en tus manos." << endl;

    while (!gameOver) {
        Room *room = world.getCurrentRoom();
        visitedRooms.push_back(room->getID());
        logger.logRoomEntry(room->getID());

        cout << "\n========================================" << endl;
        cout << room->getID() << " [" << room->getType() << "]" << endl;
        cout << room->describe() << endl;
        cout << "========================================" << endl;

        runRoom(room);
    }

    if (victory) {
        logger.logVictory();
        cout << "\n*** VICTORIA ***" << endl;
        cout << "Las tinieblas han sido derrotadas. " << world.getKnight().getName() << " es el heroe del reino." <<
                endl;
    } else {
        logger.logDefeat();
        cout << "\n*** DERROTA ***" << endl;
        cout << "La oscuridad cubre el reino. El nombre de " << world.getKnight().getName() <<
                " se pierde en el olvido." << endl;
    }

    ReportGenerator report;
    report.generate("reporte_final.txt", victory, world.getKnight(),
                    goblinsKilled, magesKilled, dragonsKilled, visitedRooms, turnCount);
    cout << "\nReporte guardado en reporte_final.txt" << endl;
    cout << "Bitacora guardada en bitacora.txt" << endl;
}


void SimulationEngine::runRoom(Room *room) {
    string type = room->getType();
    bool isDungeon = (type == "castillo" || type == "cuevas");
    int maxTurns = (type == "aldea") ? 3 : (type == "bosque") ? 4 : 9999;
    int localTurns = 0;

    while (localTurns < maxTurns && !gameOver) {
        turnCount++;
        localTurns++;
        cout << "\n--- Turno " << turnCount << " ---" << endl;

        Entity *encountered = rollEncounter(room);
        Villager *metVillager = nullptr;

        if (encountered == nullptr) {
            cout << room->getAmbientLine() << endl;
        } else {
            Villager *v = dynamic_cast<Villager *>(encountered);
            Enemy *e = dynamic_cast<Enemy *>(encountered);

            if (v != nullptr) {
                cout << "Te encuentras con " << v->getName() << "." << endl;
                metVillager = v;
            } else if (e != nullptr && e->isFriendly() && !isDungeon) {
                Knight &k = world.getKnight();
                cout << "El mago " << e->getName() << " aparece ante ti." << endl;
                cout << "\"Viajero, te veo herido. Permite que te ayude.\"" << endl;
                cout << "Una luz dorada te envuelve. Tu vida se restaura por completo." << endl;
                logger.logInteraction("Mago amistoso " + e->getName() + " curo al caballero");
                k.heal(k.getMaxHealth());
                if (e->getIsUnique()) room->removeEntity(e);
            } else if (e != nullptr) {
                runCombat(e, room);
                if (gameOver) return;
            }
        }

        bool canExplore = (!isDungeon && localTurns < maxTurns);
        bool moved = handleMainMenu(room, metVillager, isDungeon, canExplore);
        if (moved) return;
    }

    if (!isDungeon && !gameOver) {
        cout << "\nHas explorado todo lo que esta sala tiene para ofrecer. Debes seguir tu camino." << endl;
        handleMove(room);
    }
}


Entity *SimulationEngine::rollEncounter(Room *room) {
    const vector<unique_ptr<Entity> > &entities = room->getEntities();

    int available = 0;
    for (int i = 0; i < (int) entities.size(); i++) {
        Enemy *e = dynamic_cast<Enemy *>(entities[i].get());
        if (e == nullptr || !e->isDead()) available++;
    }
    if (available == 0) return nullptr;

    string type = room->getType();
    bool isDungeon = (type == "castillo" || type == "cuevas");
    int noEncounterChance = isDungeon ? 30 : 25;
    if (rand() % 100 < noEncounterChance) return nullptr;

    int pick = rand() % available;
    int count = 0;
    for (int i = 0; i < (int) entities.size(); i++) {
        Enemy *e = dynamic_cast<Enemy *>(entities[i].get());
        if (e == nullptr || !e->isDead()) {
            if (count == pick) return entities[i].get();
            count++;
        }
    }
    return nullptr;
}


void SimulationEngine::runCombat(Enemy *enemy, Room *room) {
    Knight &knight = world.getKnight();

    cout << "\n¡Encuentro hostil! " << enemy->getName() << " bloquea tu camino." << endl;
    cout << enemy->describe() << endl;
    logger.logCombat(enemy->getName());

    bool isVictory = enemy->isVictoryKill();
    bool isMageEnemy = (!enemy->isFriendly() && dynamic_cast<Mage *>(enemy) != nullptr);
    bool isUnique = enemy->getIsUnique();
    string enemyName = enemy->getName();

    bool knightFirst = (rand() % 2 == 0);
    cout << (knightFirst ? "Tomas la iniciativa y atacas primero." : (enemyName + " ataca primero.")) << endl;

    while (!knight.isDead() && !enemy->isDead()) {
        if (knightFirst) {
            doKnightAttack(*enemy);
            if (enemy->isDead()) break;
            doEnemyAttack(*enemy);
        } else {
            doEnemyAttack(*enemy);
            if (knight.isDead()) break;
            doKnightAttack(*enemy);
        }

        if (!knight.isDead() && !enemy->isDead()) {
            waitForEnter();
        }
    }

    if (enemy->isDead()) {
        cout << "\n¡Has derrotado a " << enemyName << "!" << endl;
        logger.logCombatResult("Derroto a " + enemyName);

        int gold = enemy->getGoldDrop();
        if (gold > 0) {
            goblinsKilled++;
            knight.addGold(gold);
            cout << "El goblin caido suelta una pequena bolsa con " << gold << " de oro." << endl;
            logger.logInteraction("Recogió " + to_string(gold) + " de oro del goblin caído");
        } else if (isMageEnemy) {
            magesKilled++;
        } else if (isVictory) {
            dragonsKilled++;
        }

        if (isUnique) room->removeEntity(enemy);

        if (isVictory) {
            cout << "\n*** La escamas de " << enemyName << " caen al suelo. El fuego negro se extingue. ***" << endl;
            cout << "*** ¡" << knight.getName() << " ha liberado al reino! ¡VICTORIA! ***" << endl;
            victory = true;
            gameOver = true;
        }
    } else {
        logger.logCombatResult("Fue derrotado por " + enemyName);
        cout << "\n" << knight.getName() << " cae ante " << enemyName << "." << endl;
        cout << "Las tinieblas reclaman su alma. El reino esta perdido." << endl;
        victory = false;
        gameOver = true;
    }
}

void SimulationEngine::doKnightAttack(Enemy &target) {
    Knight &knight = world.getKnight();
    const Weapon &w = knight.getEquippedWeapon();

    w.regenerateMana();

    if (!w.canCast()) {
        cout << "  [" << knight.getName() << "] Sin mana para lanzar el hechizo. Pierde el turno." << endl;
        return;
    }

    int hitChance = w.getHitChance();
    if (rand() % 100 < hitChance) {
        double rawDmg = w.calculateDamage();
        int armorRed = target.getEquippedArmor().getDamageReduction();
        int finalDmg = (int) (rawDmg * (100 - armorRed) / 100.0);
        if (finalDmg < 1) finalDmg = 1;
        target.takeDamage(finalDmg);
        w.consumeMana(finalDmg);
        cout << "  [" << knight.getName() << "] Golpea con " << w.getName()
                << " -> " << finalDmg << " danio. "
                << "(Enemigo: " << target.getHealth() << "/" << target.getMaxHealth() << " HP)" << endl;
    } else {
        cout << "  [" << knight.getName() << "] Falla el ataque." << endl;
    }
}


void SimulationEngine::doEnemyAttack(Enemy &attacker) {
    Knight &knight = world.getKnight();
    const Weapon &w = attacker.getEquippedWeapon();

    w.regenerateMana();

    if (!w.canCast()) {
        cout << "  [" << attacker.getName() << "] Sin mana. Pierde el turno." << endl;
        return;
    }

    int hitChance = w.getHitChance();
    if (rand() % 100 < hitChance) {
        double rawDmg = w.calculateDamage();
        int armorRed = knight.getEquippedArmor().getDamageReduction();
        int finalDmg = (int) (rawDmg * (100 - armorRed) / 100.0);
        if (finalDmg < 1) finalDmg = 1;
        knight.takeDamage(finalDmg);
        w.consumeMana(finalDmg);
        cout << "  [" << attacker.getName() << "] Golpea con " << w.getName()
                << " -> " << finalDmg << " danio. "
                << "(Caballero: " << knight.getHealth() << "/" << knight.getMaxHealth() << " HP)" << endl;
    } else {
        cout << "  [" << attacker.getName() << "] Falla el ataque." << endl;
    }
}


bool SimulationEngine::handleMainMenu(Room *room, Villager *villager, bool isDungeon, bool canExplore) {
    Knight &knight = world.getKnight();

    while (true) {
        bool canUseBandage = (knight.getBandages() > 0 && knight.getHealth() < knight.getMaxHealth());
        bool hasVillager = (villager != nullptr);

        int n = 1;
        int optExplore = canExplore ? n++ : -1;
        int optMove = !isDungeon ? n++ : -1;
        int optInv = n++;
        int optBandage = canUseBandage ? n++ : -1;
        int optVillager = hasVillager ? n++ : -1;
        int optEscape = isDungeon ? n++ : -1;

        cout << "\n¿Que deseas hacer?" << endl;
        if (canExplore) cout << " " << optExplore << ". Explorar (quedarse y buscar mas)" << endl;
        if (!isDungeon) cout << " " << optMove << ". Avanzar a otra sala" << endl;
        cout << " " << optInv << ". Revisar inventario" << endl;
        if (canUseBandage) cout << " " << optBandage << ". Usar vendaje (" << knight.getBandages() << " disponibles)" <<
                           endl;
        if (hasVillager) cout << " " << optVillager << ". Hablar con " << villager->getName() << endl;
        if (isDungeon) cout << " " << optEscape << ". Intentar escapar (50% de exito)" << endl;
        cout << "Opcion: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cin.ignore(1000, '\n');
        if (canExplore && choice == optExplore) {
            return false;
        } else if (!isDungeon && choice == optMove) {
            handleMove(room);
            return true;
        } else if (choice == optInv) {
            knight.printInventory();
        } else if (canUseBandage && choice == optBandage) {
            knight.useBandage(bandageHealAmount);
            cout << "Vida tras vendaje: " << knight.getHealth() << "/" << knight.getMaxHealth() << endl;
        } else if (hasVillager && choice == optVillager) {
            handleVillagerInteraction(villager);
        } else if (isDungeon && choice == optEscape) {
            if (rand() % 100 < 50) {
                cout << "Logras escabullirte entre las sombras." << endl;
                if (!previousRoomId.empty()) {
                    world.moveKnight(previousRoomId);
                } else {
                    const vector<string> &conns = room->getConnections();
                    for (int i = 0; i < (int) conns.size(); i++) {
                        Room *r = world.getRoomById(conns[i]);
                        if (r->getType() != "castillo" && r->getType() != "cuevas") {
                            world.moveKnight(conns[i]);
                            break;
                        }
                    }
                }
                return true;
            } else {
                cout << "El paso esta bloqueado. No puedes escapar este turno." << endl;
                return false;
            }
        } else {
            cout << "Opcion invalida. Intenta de nuevo." << endl;
        }
    }
}


void SimulationEngine::handleMove(Room *room) {
    const vector<string> &conns = room->getConnections();

    if (conns.empty()) {
        cout << "No hay salidas de esta sala." << endl;
        return;
    }

    bool hasDanger = false;
    for (int i = 0; i < (int) conns.size(); i++) {
        Room *r = world.getRoomById(conns[i]);
        if (r->getType() == "castillo" || r->getType() == "cuevas") {
            hasDanger = true;
            break;
        }
    }

    if (!hasDanger) {
        int idx = rand() % (int) conns.size();
        previousRoomId = room->getID();
        world.moveKnight(conns[idx]);
        cout << "Avanzas hacia " << conns[idx] << "." << endl;
        return;
    }

    cout << "\nCaminos disponibles:" << endl;
    for (int i = 0; i < (int) conns.size(); i++) {
        Room *r = world.getRoomById(conns[i]);
        bool danger = (r->getType() == "castillo" || r->getType() == "cuevas");
        cout << "  " << (i + 1) << ". " << conns[i]
                << (danger ? " [PELIGROSO — " + r->getType() + "]" : "") << endl;
    }
    cout << "Elige destino (numero): ";
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(1000, '\n');
        choice = 1;
    } else {
        cin.ignore(1000, '\n');
        if (choice < 1 || choice > (int) conns.size()) choice = 1;
    }

    string chosenId = conns[choice - 1];
    Room *chosen = world.getRoomById(chosenId);
    bool chosenDanger = (chosen->getType() == "castillo" || chosen->getType() == "cuevas");

    if (chosenDanger) {
        cout << "Te adentras en " << chosenId << "... el aire se vuelve frio y denso." << endl;
    } else {
        cout << "Avanzas hacia " << chosenId << "." << endl;
    }

    previousRoomId = room->getID();
    world.moveKnight(chosenId);
}


void SimulationEngine::handleVillagerInteraction(Villager *villager) {
    Knight &knight = world.getKnight();
    cout << "\n" << villager->getName() << ": \"Bienvenido, viajero. Mira lo que tengo para ti.\"" << endl;

    if (villager->getStockSize() >= 3) {
        unique_ptr<Weapon> loot = villager->giveLoot();
        if (loot != nullptr) {
            cout << villager->getName() << " te obsequia: " << loot->getName() << endl;
            knight.addWeapon(loot.get());
            knight.sortWeapon();
            cout << "Arma equipada actualizada: " << knight.getEquippedWeapon().getName() << endl;
        }
    }

    cout << "\n¿Deseas comprar algo? (1=Si, 0=No): ";
    int resp;
    if (!(cin >> resp)) {
        cin.clear();
        cin.ignore(1000, '\n');
        resp = 0;
    } else cin.ignore(1000, '\n');

    if (resp == 1) {
        cout << "1. Comprar arma" << endl;
        cout << "2. Comprar vendaje (" << bandagePrice << " de oro)" << endl;
        cout << "3. Comprar armadura" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        int shopChoice;
        if (!(cin >> shopChoice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            shopChoice = 0;
        } else cin.ignore(1000, '\n');

        if (shopChoice == 1) {
            villager->getAvailableWeapons();
            int maxIdx = villager->getStockSize() - 1;
            cout << "Indices disponibles: 0 a " << maxIdx << endl;
            cout << "Indice del arma (o -1 para cancelar): ";
            int idx;
            if (!(cin >> idx)) {
                cin.clear();
                cin.ignore(1000, '\n');
                idx = -1;
            } else cin.ignore(1000, '\n');
            if (idx >= 0 && idx <= maxIdx) {
                if (villager->sellWeapon(idx, knight)) {
                    knight.sortWeapon();
                    cout << "Arma equipada actualizada: " << knight.getEquippedWeapon().getName() << endl;
                }
            }
        } else if (shopChoice == 2) {
            if (knight.getGold() >= bandagePrice) {
                knight.spendGold(bandagePrice);
                knight.addBandage();
                cout << "Compraste un vendaje. Vendajes: " << knight.getBandages()
                        << " | Oro restante: " << knight.getGold() << endl;
            } else {
                cout << "No tienes suficiente oro (necesitas " << bandagePrice
                        << ", tienes " << knight.getGold() << ")." << endl;
            }
        } else if (shopChoice == 3) {
            if (villager->getArmorStockSize() == 0) {
                cout << "Este aldeano no vende armaduras." << endl;
            } else {
                villager->getAvailableArmors();
                int maxIdx = villager->getArmorStockSize() - 1;
                cout << "Indices disponibles: 0 a " << maxIdx << endl;
                cout << "Indice de la armadura (o -1 para cancelar): ";
                int idx;
                if (!(cin >> idx)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    idx = -1;
                } else cin.ignore(1000, '\n');
                if (idx >= 0 && idx <= maxIdx) {
                    if (villager->sellArmor(idx, knight)) {
                        cout << "Armadura equipada: " << knight.getEquippedArmor().getName() << " (reduccion: " <<
                                knight.getEquippedArmor().getDamageReduction() << "%)" << " | Oro restante: " << knight.
                                getGold() << endl;
                    }
                }
            }
        }
    }

    logger.logInteraction("Interactuo con " + villager->getName());
}

void SimulationEngine::waitForEnter() {
    cout << "\nPresione Enter para continuar..." << flush;
    string dummy;
    getline(cin, dummy);
}
