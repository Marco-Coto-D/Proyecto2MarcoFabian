//
// Created by mcoto on 6/2/2026.
//

#include "Room.h"
Room::Room(string id, string type, string description) {
    this->id = id;
    this->type = type;
    this->description = description;
}

void Room::addEntity(unique_ptr<Entity> other) {
    entities.push_back(move(other));
}

void Room::addConnection(string other) {
    connections.push_back(other);
}

string Room::describe() const {
    return description;
}

string Room::getID() const {
    return id;
}

string Room::getType() const {
    return type;
}

const vector<unique_ptr<Entity>> & Room::getEntities() const {
    return entities;
}

const vector<string> & Room::getConnections() const {
    return connections;
}

void Room::removeEntity(Entity* ptr) {
    for (int i = 0; i < (int)entities.size(); i++) {
        if (entities[i].get() == ptr) {
            entities.erase(entities.begin() + i);
            return;
        }
    }
}

string Room::getAmbientLine() const {
    if (type == "aldea")    return "Los aldeanos susurran historias de tiempos mas oscuros.";
    if (type == "bosque")   return "El viento entre los arboles suena como lamentos olvidados.";
    if (type == "castillo") return "Sombras se mueven en las paredes del castillo. Algo acecha.";
    if (type == "cuevas")   return "El goteo del agua resuena en la oscuridad. Algo respira cerca.";
    return "Un momento de silencio inquietante.";
}
