//
// Created by phamt on 11/4/2019.
//

#include "Monster.h"

Monster::Monster() {

}

Monster::Monster(string name, int health) : Entity(name, health) {

}

int Monster::Attack() {
    cout << GetName() << " deals 1 point of damage" << endl;
    return 1;
}

