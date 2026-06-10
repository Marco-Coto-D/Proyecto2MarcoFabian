#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#include "WorldLoader.h"
#include "Logger.h"
#include "SimulationEngine.h"

int main() {
    WorldLoader loader;
    World world;

    try {
        world = loader.load("config.txt", "mundo.txt", "entidades.txt", "armas_aldeanos.txt", "armaduras_aldeanos.txt");
    } catch (const runtime_error& e) {
        cerr << "Error al cargar el mundo: " << e.what() << endl;
        return 1;
    }

    srand(time(nullptr));

    Logger logger("bitacora.txt");
    SimulationEngine engine(world, logger, loader.getBandageHeal(), loader.getBandagePrice());
    engine.run();

    return 0;
}
