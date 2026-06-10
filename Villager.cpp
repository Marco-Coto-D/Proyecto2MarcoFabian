//
// Created by mcoto on 6/2/2026.
//

#include "Villager.h"
#include <cstdlib>
#include <ctime>

Villager::Villager(string id, string name, string description): Entity(name, description) {
    this->id = id;
}

void Villager::sortStock() {
    for (int i = 0; i < stock.size(); i++) {
        for (int j = 0; j < stock.size() - i - 1; j++) {
            if (stock[j]->getBaseDamage() < stock[j + 1]->getBaseDamage()) {
                swap(stock[j], stock[j + 1]);
                swap(prices[j], prices[j + 1]);
            }
        }
    }
}

void Villager::addWeapon(unique_ptr<Weapon> other, int price) {
    stock.push_back(move(other));
    prices.push_back(price);
    sortStock();
}

unique_ptr<Weapon> Villager::giveLoot() {
    if (stock.size() < 3) {
        throw runtime_error("El aldeano no tiene suficientes armas en stock");
    }
    int probLoot = rand() % 100;
    int calLoot = rand() % 100;
    if (probLoot < 50) {
        if (calLoot < 40) {
            cout<<"Recibiste un simple palo, inutil para combate y decides dejarlo"<<endl<<endl;
            return nullptr;
        }
        if (calLoot >= 40 && calLoot < 70) {
            cout<<"Recibiste una espada de madera, algo humilde pero te puede servir"<<endl<<endl;
            return make_unique<Weapon>(*stock[2]);
        }
        if (calLoot >= 70 && calLoot < 90) {
            cout<<"El aldeano te ha dado una espada de piedra, ya tienes bastante poder"<<endl<<endl;
            return make_unique<Weapon>(*stock[1]);
        }
        if (calLoot >= 90 && calLoot < 100) {
            cout<<"Felicidades, le caiste bien al aldeano y te dio una espada de hierro"<<endl<<endl;
            return make_unique<Weapon>(*stock[0]);
        }
        return nullptr;
    }
    return nullptr;
}

void Villager::getAvailableWeapons() const {
    cout<<"----Armas disponibles----"<<endl<<endl;
    for (int i = 0; i < stock.size(); i++) {
        cout<<"Indice: "<<i<<endl;
        cout <<"Nombre del arma:"<< stock[i]->getName() <<endl;
        cout <<"Fuerza Base: "<<stock[i]->getBaseDamage()<<endl;
        cout<<"Precio:" <<prices[i] <<endl;
    }
}

string Villager::getId() const {
    return id;
}

bool Villager::sellWeapon(int index, Knight &buyer) {
    getAvailableWeapons();
    cout<<"Indica el arma que quieres comprar por su indice"<<endl;
    if (buyer.getGold() >= prices[index]) {
        buyer.addWeapon(stock[index].get());
        buyer.spendGold(prices[index]);
        return true;
    }
    cout<<"No tienes dinero suficiente"<<endl;
    return false;
}

string Villager::describe() const {
    return description;
}

int Villager::getStockSize() const {
    return (int)stock.size();
}

void Villager::addArmor(unique_ptr<Armor> armor, int price) {
    armorStock.push_back(move(armor));
    armorPrices.push_back(price);
}

int Villager::getArmorStockSize() const {
    return (int)armorStock.size();
}

void Villager::getAvailableArmors() const {
    cout << "----Armaduras disponibles----" << endl << endl;
    for (int i = 0; i < (int)armorStock.size(); i++) {
        cout << "Indice: " << i << endl;
        cout << "Nombre: " << armorStock[i]->getName() << endl;
        cout << "Reduccion de danio: " << armorStock[i]->getDamageReduction() << "%" << endl;
        cout << "Precio: " << armorPrices[i] << endl << endl;
    }
}

bool Villager::sellArmor(int index, Knight& buyer) {
    if (buyer.getGold() < armorPrices[index]) {
        cout << "No tienes oro suficiente (necesitas " << armorPrices[index]
             << ", tienes " << buyer.getGold() << ")." << endl;
        return false;
    }
    if (armorStock[index]->getDamageReduction() <= buyer.getEquippedArmor().getDamageReduction()) {
        cout << "Esta armadura no es mejor que la que ya llevas puesta." << endl;
        return false;
    }
    buyer.spendGold(armorPrices[index]);
    buyer.setArmor(make_unique<Armor>(*armorStock[index]));
    return true;
}
