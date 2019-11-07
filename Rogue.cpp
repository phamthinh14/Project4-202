//
// Created by phamt on 11/4/2019.
//

#include "Rogue.h"

Rogue::Rogue() {}

Rogue::Rogue(string name, int health) : Character(name, health) {
}

Rogue::~Rogue() {}

int Rogue::SpecialAttack() {
    int damage = rand() % 11 + 2;
    cout << GetName() << " performs a sneak attack and deals " << damage << endl;
    return damage;
}