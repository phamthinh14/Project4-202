#include "BabyDragon.h"

//
// Created by phamt on 11/4/2019.
//
BabyDragon::BabyDragon() {}

BabyDragon::BabyDragon(string name, int health) : Monster(name, health) {
}

int BabyDragon::SpecialAttack() {
    cout << GetName() << " breaths a cone fire at you and deals 4 damage" << endl;
    return 4;
}