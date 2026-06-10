//
// Created by mcoto on 6/9/2026.
//

#include "WorldLoader.h"

unique_ptr<DamageStrategy> WorldLoader::makeStrategy(const string& type, int maxMana, int lineNum, const string& file) {
    if (type == "sword") return make_unique<SwordStrategy>();
    if (type == "bow")   return make_unique<BowStrategy>();
    if (type == "spell") return make_unique<SpellStrategy>(maxMana);
    throw runtime_error("Error en " + file + " linea " + to_string(lineNum) + ": tipo de arma desconocido '" + type + "' (use sword, bow o spell)");
}

void WorldLoader::loadConfig(const string& path, World& world) {
    ifstream file(path);
    if (!file.is_open()) {
        throw runtime_error("No se pudo abrir el archivo de configuracion: " + path);
    }

    string knightName, knightDesc;
    int knightHealth = 0, knightMaxHealth = 0, knightGold = 0, knightBandages = 0;
    seed = 0;
    bandagePrice = 0;
    bandageHeal = 0;

    string line;
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        stringstream ss(line);
        string key, value;
        getline(ss, key, '=');
        getline(ss, value);

        if (key == "semilla") {
            seed = stoi(value);
        } else if (key == "sala_inicial") {
            startRoomId = value;
        } else if (key == "caballero_nombre") {
            knightName = value;
        } else if (key == "caballero_descripcion") {
            knightDesc = value;
        } else if (key == "caballero_vida") {
            knightHealth = stoi(value);
        } else if (key == "caballero_vida_max") {
            knightMaxHealth = stoi(value);
        } else if (key == "caballero_oro") {
            knightGold = stoi(value);
        } else if (key == "caballero_vendajes") {
            knightBandages = stoi(value);
        } else if (key == "precio_vendaje") {
            bandagePrice = stoi(value);
        } else if (key == "dano_vendaje") {
            bandageHeal = stoi(value);
        }
    }

    if (knightName.empty()) {
        throw runtime_error("Error en " + path + ": falta la clave 'caballero_nombre'");
    }
    if (startRoomId.empty()) {
        throw runtime_error("Error en " + path + ": falta la clave 'sala_inicial'");
    }

    auto fists = make_unique<Weapon>("Puños", 1, make_unique<SwordStrategy>());
    auto noArmor = make_unique<Armor>("Sin Armadura", 0);
    world.setKnight(make_unique<Knight>(knightName, knightDesc, knightHealth, knightMaxHealth, knightGold, move(fists), move(noArmor), knightBandages));
}

void WorldLoader::loadWorld(const string& path, World& world) {
    ifstream file(path);
    if (!file.is_open()) {
        throw runtime_error("No se pudo abrir el archivo de mundo: " + path);
    }

    string line;
    int lineNum = 0;
    while (getline(file, line)) {
        lineNum++;
        if (line.empty()) continue;

        stringstream ss(line);
        string id, type, desc, connsField;
        getline(ss, id,        '|');
        getline(ss, type,      '|');
        getline(ss, desc,      '|');
        getline(ss, connsField);

        if (id.empty() || type.empty() || desc.empty()) {
            throw runtime_error("Error en " + path + " linea " + to_string(lineNum) + ": formato invalido (se esperan al menos 3 campos separados por '|')");
        }

        auto room = make_unique<Room>(id, type, desc);

        if (!connsField.empty()) {
            stringstream cs(connsField);
            string conn;
            while (getline(cs, conn, ',')) {
                if (!conn.empty()) room->addConnection(conn);
            }
        }

        world.addRoom(move(room));
    }
}

void WorldLoader::loadEntities(const string& path, World& world) {
    ifstream file(path);
    if (!file.is_open()) {
        throw runtime_error("No se pudo abrir el archivo de entidades: " + path);
    }

    string line;
    int lineNum = 0;
    while (getline(file, line)) {
        lineNum++;
        if (line.empty()) continue;

        vector<string> f;
        stringstream ss(line);
        string token;
        while (getline(ss, token, '|')) {
            f.push_back(token);
        }
        if (f.empty()) continue;

        string tipo = f[0];

        if (tipo == "VILLAGER") {
            if ((int)f.size() < 5) {
                throw runtime_error("Error en " + path + " linea " + to_string(lineNum) + ": VILLAGER requiere 5 campos");
            }
            string aldId= f[1];
            string roomId= f[2];
            string name= f[3];
            string desc= f[4];

            auto villager = make_unique<Villager>(aldId, name, desc);
            Villager* ptr = villager.get();

            Room* room = nullptr;
            try {
                room = world.getRoomById(roomId);
            } catch (const runtime_error&) {
                throw runtime_error("Error en " + path + " linea " + to_string(lineNum) + ": sala '" + roomId + "' no encontrada");
            }
            room->addEntity(move(villager));

            villagerIds.push_back(aldId);
            villagerPtrs.push_back(ptr);

        } else if (tipo == "GOBLIN" || tipo == "DRAGON" || tipo == "MAGE") {
            if ((int)f.size() < 13) {
                throw runtime_error("Error en " + path + " linea " + to_string(lineNum) + ": " + tipo + " requiere 13 campos, se encontraron " + to_string((int)f.size()));
            }
            string roomId= f[1];
            string name= f[2];
            string desc= f[3];
            int hp = stoi(f[4]);
            int maxHp = stoi(f[5]);
            bool isUnique = (f[6] == "true");
            string weapName= f[7];
            int weapBase = stoi(f[8]);
            string weapType= f[9];
            int maxMana = stoi(f[10]);
            string armName = f[11];
            int armRed = stoi(f[12]);

            auto strategy = makeStrategy(weapType, maxMana, lineNum, path);
            auto weapon = make_unique<Weapon>(weapName, weapBase, move(strategy));
            auto armor = make_unique<Armor>(armName, armRed);

            unique_ptr<Entity> entity;
            if  (tipo == "GOBLIN") {
                entity = make_unique<Goblin>(name, desc, hp, maxHp, move(weapon), move(armor), isUnique);
            } else if (tipo == "DRAGON") {
                entity = make_unique<Dragon>(name, desc, hp, maxHp, move(weapon), move(armor), isUnique);
            } else {
                entity = make_unique<Mage>  (name, desc, hp, maxHp, move(weapon), move(armor), isUnique);
            }

            Room* room = nullptr;
            try {
                room = world.getRoomById(roomId);
            } catch (const runtime_error&) {
                throw runtime_error("Error en " + path + " linea " + to_string(lineNum) + ": sala '" + roomId + "' no encontrada");
            }
            room->addEntity(move(entity));

        } else {
            throw runtime_error("Error en " + path + " linea " + to_string(lineNum) + ": tipo de entidad desconocido '" + tipo + "'");
        }
    }
}

void WorldLoader::loadVillagerStock(const string& path, World& world) {
    ifstream file(path);
    if (!file.is_open()) {
        throw runtime_error("No se pudo abrir el archivo de armas de aldeanos: " + path);
    }

    string line;
    int lineNum = 0;
    while (getline(file, line)) {
        lineNum++;
        if (line.empty()) continue;

        vector<string> f;
        stringstream ss(line);
        string token;
        while (getline(ss, token, '|')) {
            f.push_back(token);
        }
        if ((int)f.size() < 6) {
            throw runtime_error("Error en " + path + " linea " + to_string(lineNum) +": se requieren 6 campos");
        }

        string aldId = f[0];
        string weapName= f[1];
        int baseDmg = stoi(f[2]);
        string weapType= f[3];
        int maxMana = stoi(f[4]);
        int price = stoi(f[5]);

        Villager* villager = nullptr;
        for (int i = 0; i < (int)villagerIds.size(); i++) {
            if (villagerIds[i] == aldId) {
                villager = villagerPtrs[i];
                break;
            }
        }
        if (villager == nullptr) {
            throw runtime_error("Error en " + path + " linea " + to_string(lineNum) + ": aldeano '" + aldId + "' no encontrado (no fue definido en entidades.txt)");
        }

        auto strategy = makeStrategy(weapType, maxMana, lineNum, path);
        auto weapon   = make_unique<Weapon>(weapName, baseDmg, move(strategy));
        villager->addWeapon(move(weapon), price);
    }
}

World WorldLoader::load(
    const string& configPath,
    const string& worldPath,
    const string& entitiesPath,
    const string& villagerStockPath
) {
    World world;
    villagerIds.clear();
    villagerPtrs.clear();

    loadConfig(configPath, world);
    loadWorld(worldPath, world);

    try {
        world.getRoomById(startRoomId);
    } catch (const runtime_error&) {
        throw runtime_error("La sala_inicial '" + startRoomId + "' no existe en mundo.txt");
    }
    
    const vector<unique_ptr<Room>>& rooms = world.getRooms();
    for (int i = 0; i < (int)rooms.size(); i++) {
        const vector<string>& conns = rooms[i]->getConnections();
        for (int j = 0; j < (int)conns.size(); j++) {
            bool found = false;
            for (int k = 0; k < (int)rooms.size(); k++) {
                if (rooms[k]->getID() == conns[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                throw runtime_error("Error en mundo.txt: la sala '" + rooms[i]->getID() +
                    "' referencia una conexion inexistente '" + conns[j] + "'");
            }
        }
    }

    loadEntities(entitiesPath, world);
    loadVillagerStock(villagerStockPath, world);

    world.setStartRoom(startRoomId);
    return world;
}

int WorldLoader::getSeed() const {
    return seed;
}
