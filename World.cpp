//
// Created by mcoto on 6/3/2026.
//

#include "World.h"
void World::addRoom(unique_ptr<Room> room) {
    rooms.push_back(move(room));
}

void World::setKnight(unique_ptr<Knight> knight) {
    this->knight = move(knight);
}

Room * World::getRoomById(string id) {
    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i]->getID() == id) {
            return rooms[i].get();
        }
    }
    return nullptr;
}

Room* World::getCurrentRoom() {
   return getRoomById(currentRoomId);
}

Knight & World::getKnight() {
    return *knight;
}

void World::moveKnight(string targetRoomID) {
    Room* current = getCurrentRoom();
    const vector<string>& connections = current->getConnections();

    bool found = false;
    for (int i = 0; i < connections.size(); i++) {
        if (connections[i] == targetRoomID) {
            found = true;
            break;
        }
    }

    if (!found) {
        throw runtime_error("Conexion invalida: no puedes moverte a esa sala");
    }

    currentRoomId = targetRoomID;
}
