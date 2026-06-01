cmake_minimum_required(VERSION 4.2)
project(Proyecto2MarcoFabian)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyecto2MarcoFabian main.cpp
        Entity.h
        Armor.cpp
        Armor.h
        DamageStrategy.h
        SwordStrategy.cpp
        SwordStrategy.h
        BowStrategy.cpp
        BowStrategy.h
        SpellStrategy.cpp
        SpellStrategy.h
        Weapon.cpp
        Weapon.h
        Enemy.cpp
        Enemy.h
        Knight.cpp
        Knight.h
        Goblin.h)
