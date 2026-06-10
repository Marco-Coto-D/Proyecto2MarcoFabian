//
// Created by mcoto on 6/9/2026.
//

#ifndef PROYECTO2MARCOFABIAN_LOGGER_H
#define PROYECTO2MARCOFABIAN_LOGGER_H
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

class Logger {
private:
    ofstream logFile;
public:
    Logger(const string& filename);
    ~Logger();
    void logRoomEntry(const string& roomName);
    void logInteraction(const string& description);
    void logCombat(const string& enemyName);
    void logCombatResult(const string& result);
    void logVictory();
    void logDefeat();
};

#endif //PROYECTO2MARCOFABIAN_LOGGER_H
