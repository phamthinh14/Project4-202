//
// Created by phamt on 11/4/2019.
//

#include "Room.h"

Room::Room(int ID, string roomName, string roomDescript, int north, int east, int south, int west) {
    m_ID = ID;
    m_name = roomName;
    m_desc = roomDescript;
    m_direction[0] = north;
    m_direction[1] = east;
    m_direction[2] = south;
    m_direction[3] = west;
}

int Room::GetID() {
    return m_ID;
}

string Room::GetName() {
    return m_name;
}

string Room::GetDesc() {
    return m_desc;
}

//Name: CheckDirection
//Precondition: Must have valid room
//You pass it a char (N/n, E/e, S/s, or W/w) and if that is a valid exit it
//returns the ID of the room in that direction
//Postcondition: Returns id of room in that direction if the exit exists
//If there is no exit in that direction, returns -1
int Room::CheckDirection(char myDirection) {
//Enum defining the directions in array n/N = 0, e/E = 1, s/S = 2, w/W = 3
    int tempNum = 0;
    if (myDirection == 'n' || myDirection == 'N') {
        tempNum = 0;
    }
    if (myDirection == 'e' || myDirection == 'E') {
        tempNum = 1;
    }
    if (myDirection == 's' || myDirection == 'S') {
        tempNum = 2;
    }
    if (myDirection == 'w' || myDirection == 'W') {
        tempNum = 3;
    }
    return m_direction[tempNum] > -1 ? m_direction[tempNum] : -1;
}

//Name: PrintRoom
//Precondition: Room must be complete
//Postcondition: Outputs the room name, room desc, then possible exits
void Room::PrintRoom() {
    cout << "Room Name: " << m_name << endl;
    cout << "Room Description: " << m_desc << endl;
    if (m_direction[0] != -1) {
        cout << "Possible Direction: " << "N" << endl;
    }
    if (m_direction[1] != -1) {
        cout << "Possible Direction: " << "E" << endl;
    }
    if (m_direction[2] != -1) {
        cout << "Possible Direction: " << "S" << endl;
    }
    if (m_direction[3] != -1) {
        cout << "Possible Direction: " << "W" << endl;
    }
}