#include "Skeleton.h"

//
// Created by phamt on 11/4/2019.
//
Skeleton::Skeleton() {}

Skeleton::Skeleton(string name, int health) : Monster(name, health) {
}

int Skeleton::SpecialAttack() {
    cout << GetName() << " bashes you with its own arm and deals 1 damage" << endl;
    return 1;
}