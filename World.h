//
// Created by mcoto on 6/3/2026.
//

#ifndef PROYECTO2MARCOFABIAN_WORLD_H
#define PROYECTO2MARCOFABIAN_WORLD_H
#include "Room.h"
#include "Knight.h"


class World {
    private:
    vector<unique_ptr<Room>> rooms;
    unique_ptr<Knight> knight;
    string currentRoomId;
    public:
    void addRoom(unique_ptr<Room> room);
    void setKnight(unique_ptr<Knight> knight);
    Room* getRoomById(string id);
    Room* getCurrentRoom();
    Knight& getKnight();
    void moveKnight(string targetRoomID);

};



#endif //PROYECTO2MARCOFABIAN_WORLD_H
