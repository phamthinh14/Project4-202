//
// Created by phamt on 11/4/2019.
//

#include "Wizard.h"

Wizard::Wizard() {}

Wizard::Wizard(string name, int health) : Character(name, health) {
}

Wizard::~Wizard() {}

int Wizard::SpecialAttack() {
    int damage = rand() % 9 + 3;
    cout << GetName() << " casts magic missile and deals " << damage << endl;
    return damage;
}