//
// Created by mcoto on 6/9/2026.
//

#include "ReportGenerator.h"

void ReportGenerator::generate( const string& filename, bool victory, const Knight& knight, int goblinsKilled, int magesKilled, int dragonsKilled, const vector<string>& visitedRooms, int turnCount) {
    ofstream report;
    report.open(filename, ios::trunc);
    if (!report.is_open()) {
        throw runtime_error("No se pudo abrir el archivo de reporte: " + filename);
    }

    if (victory) {
        report << "=== RESULTADO: VICTORIA ==="<<endl;
        report << "El valiente caballero " << knight.getName() << " ha triunfado sobre las sombras y rescatado al reino de la oscuridad."<<endl<<endl;
    } else {
        report << "=== RESULTADO: DERROTA ==="<<endl;
        report << "Las tinieblas han consumido al caballero " << knight.getName() << ". El reino cae en la desesperanza eterna." <<endl<<endl;
    }

    report << "=== ESTADO FINAL DEL CABALLERO ===" <<endl;
    report << "Nombre: " << knight.getName() <<endl;
    report << "Vida: " << knight.getHealth() << " / " << knight.getMaxHealth()<<endl;
    report << "Oro: " << knight.getGold()<<endl;
    report << "Vendajes: " << knight.getBandages()<<endl<<endl;

    report << "Arma equipada: " << knight.getEquippedWeapon().getName() << " (daño base: " << knight.getEquippedWeapon().getBaseDamage() << ")" <<endl;
    report << "Armadura equipada: " << knight.getEquippedArmor().getName() << " (reducción: " << knight.getEquippedArmor().getDamageReduction() << ")" <<endl<<endl;

    report << "Inventario de armas:"<<endl;
    const auto& inv = knight.getInventory();
    if (inv.empty()) {
        report << "  (sin armas en inventario)" <<endl<<endl;
    } else {
        for (int i = 0; i < (int)inv.size(); i++) {
            report << "  - " << inv[i]->getName()
                   << " (daño base: " << inv[i]->getBaseDamage() << ")"<<endl<<endl;
        }
    }

    // Statistics
    report << "=== ESTADÍSTICAS ===" <<endl;
    report << "Goblins derrotados: " << goblinsKilled <<endl;
    report << "Magos derrotados: " << magesKilled <<endl;
    report << "Dragones derrotados: " << dragonsKilled <<endl;
    report << "Total de turnos jugados: " << turnCount <<endl<<endl;

    report << "Salas visitadas (en orden cronológico):" << endl;
    for (int i = 0; i < (int)visitedRooms.size(); i++) {
        report << "  - " << visitedRooms[i] <<endl;
    }

    report.close();
}
