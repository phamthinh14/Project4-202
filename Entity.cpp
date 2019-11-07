#include "Entity.h"

using namespace std;

//
// Created by phamt on 11/4/2019.
//
//string m_name; //Name of entity
//int m_health; //Health of entity
//int m_level; //Level of entity
Entity::Entity() {

}

Entity::Entity(string name, int health) {
    m_name = name;
    m_health = health;
}

void Entity::SetName(string name) {
    m_name = name;
}

string Entity::GetName() {
    return m_name;
}

void Entity::SetHealth(int health) {
    m_health = health;
}

int Entity::GetHealth() {
    return m_health;
}

ostream &operator<<(ostream &ostream1, Entity &entity) {
    ostream1 << "Health: " << entity.GetHealth() << endl;
    ostream1 << "Name: " << entity.GetHealth() << endl;
    return ostream1;
}

Entity::~Entity() {}

