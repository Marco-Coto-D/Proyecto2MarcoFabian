//
// Created by mcoto on 6/9/2026.
//

#include "Logger.h"

Logger::Logger(const string& filename) {
    logFile.open(filename, ios::trunc);
    if (!logFile.is_open()) {
        throw runtime_error("No se pudo abrir el archivo de bitacora: " + filename);
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::logRoomEntry(const string& roomName) {
    logFile << "Entro a " << roomName<<endl;
}

void Logger::logInteraction(const string& description) {
    logFile << description <<endl;
}

void Logger::logCombat(const string& enemyName) {
    logFile << "Lucho con " << enemyName <<endl;
}

void Logger::logCombatResult(const string& result) {
    logFile << result <<endl;
}

void Logger::logVictory() {
    logFile << "--- VICTORIA ---" <<endl;
}

void Logger::logDefeat() {
    logFile << "--- DERROTA ---" <<endl;
}
