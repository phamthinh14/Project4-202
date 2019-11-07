#include "Goblin.h"

//
// Created by phamt on 11/4/2019.
//
Goblin::Goblin() {

}

Goblin::Goblin(string name, int health) : Monster(name, health) {

}

int Goblin::SpecialAttack() {
    cout << GetName() << " knaws at your ankle and deals 2 damage" << endl;
    return 2;
}