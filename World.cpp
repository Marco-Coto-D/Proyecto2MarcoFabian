//
// Created by mcoto on 6/3/2026.
//

#include "World.h"

void World::setStartRoom(string id) {
    currentRoomId = id;
}

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
    throw runtime_error("Sala no encontrada: " + id);
}

Room* World::getCurrentRoom() {
   return getRoomById(currentRoomId);
}

Knight & World::getKnight() {
    return *knight;
}

const vector<unique_ptr<Room>>& World::getRooms() const {
    return rooms;
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
