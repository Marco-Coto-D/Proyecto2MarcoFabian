//
// Created by mcoto on 6/9/2026.
//

#ifndef PROYECTO2MARCOFABIAN_REPORTGENERATOR_H
#define PROYECTO2MARCOFABIAN_REPORTGENERATOR_H
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;
#include "Knight.h"

class ReportGenerator {
public:
    void generate(const string& filename, bool victory, const Knight& knight, int goblinsKilled, int magesKilled, int dragonsKilled, const vector<string>& visitedRooms, int turnCoun);
};

#endif //PROYECTO2MARCOFABIAN_REPORTGENERATOR_H
