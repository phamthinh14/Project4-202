//
// Created by phamt on 11/4/2019.
//

#include "Paladin.h"

Paladin::Paladin() {}

Paladin::Paladin(string name, int health) : Character(name, health) {
}

Paladin::~Paladin() {}


int Paladin::SpecialAttack() {
    int damage = rand() % 8 + 1;
    cout << GetName() << " uses smite evil and deals " << damage << endl;
    return damage;
}