
#include "Character.h"
//
// Created by phamt on 11/4/2019.
//

Character::Character() {}

Character::Character(string name, int health) : Entity(name, health) {}

Character::~Character() {}

int Character::Attack() {
    int damage = rand() % 6 + 1;
    cout << GetName() << " attacks dealing " << damage << endl;
    return damage;
}

int Character::SpecialAttack() {
    return 0;
}