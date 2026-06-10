#include <iostream>
#include <cstdlib>
using namespace std;
#include "WorldLoader.h"

int main() {
    WorldLoader loader;
    World world;

    try {
        world = loader.load(
            "config.txt",
            "mundo.txt",
            "entidades.txt",
            "armas_aldeanos.txt"
        );
    } catch (const runtime_error& e) {
        cerr << "Error al cargar el mundo: " << e.what() << endl;
        return 1;
    }

    srand(loader.getSeed());

    // Knight summary
    Knight& knight = world.getKnight();
    cout << "=== CABALLERO ===" << endl;
    cout << "Nombre:   " << knight.getName() << endl;
    cout << "Desc:     " << knight.describe() << endl;
    cout << "Vida:     " << knight.getHealth() << " / " << knight.getMaxHealth() << endl;
    cout << "Oro:      " << knight.getGold() << endl;
    cout << "Vendajes: " << knight.getBandages() << endl;
    cout << "Arma:     " << knight.getEquippedWeapon().getName()
         << " (dano base: " << knight.getEquippedWeapon().getBaseDamage() << ")" << endl;
    cout << "Armadura: " << knight.getEquippedArmor().getName() << endl;
    cout << endl;

    // Rooms summary
    cout << "=== SALAS (" << world.getRooms().size() << " total) ===" << endl;
    const vector<unique_ptr<Room>>& rooms = world.getRooms();
    for (int i = 0; i < (int)rooms.size(); i++) {
        Room* room = rooms[i].get();
        cout << "[" << room->getID() << "] tipo=" << room->getType() << endl;
        cout << "  " << room->describe() << endl;

        // Connections
        cout << "  Conexiones: ";
        const vector<string>& conns = room->getConnections();
        for (int j = 0; j < (int)conns.size(); j++) {
            if (j > 0) cout << ", ";
            cout << conns[j];
        }
        cout << endl;

        // Entities
        const vector<unique_ptr<Entity>>& entities = room->getEntities();
        cout << "  Entidades (" << entities.size() << "):" << endl;
        for (int j = 0; j < (int)entities.size(); j++) {
            Entity* e = entities[j].get();

            string tipo = "DESCONOCIDO";
            if      (dynamic_cast<Goblin*>(e))   tipo = "GOBLIN";
            else if (dynamic_cast<Dragon*>(e))   tipo = "DRAGON";
            else if (dynamic_cast<Mage*>(e))     tipo = "MAGE";
            else if (dynamic_cast<Villager*>(e)) tipo = "VILLAGER";

            cout << "    [" << tipo << "] " << e->getName() << endl;

            // Print villager stock
            Villager* v = dynamic_cast<Villager*>(e);
            if (v != nullptr) {
                v->getAvailableWeapons();
            }
        }
        cout << endl;
    }

    cout << "Mundo cargado correctamente." << endl;
    return 0;
}
