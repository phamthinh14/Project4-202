//
// Created by phamt on 11/5/2019.

#include "Game.h"

const string INVALID_INPUT_NOTICE = "Invalid Option. Please choose again";

Game::Game() {

}

// Name: Game(string filename) - Overloaded Constructor
// Description: Creates a new Game
// Preconditions: None
// Postconditions: Uses filesname to LoadMap, calls create character,
//                 and sets both numRests and m_numSpecial using constants.
Game::Game(string File_name) {
    LoadMap(File_name);
    CharacterCreation();
    m_numRests = NUM_RESTS;
    m_numSpecial = NUM_SPECIAL;
    m_curRoom = START_ROOM;
    m_myMap[m_curRoom]->PrintRoom();
//    Stats();
    Action();

}

Game::~Game() {

}

void Game::LoadMap(string FILE_NAME) {
    int count = 0;
    char vertical = '|';
    int ID;
    string tempID;
    string roomName;
    string roomDescript;
    int north;
    string tempNorth;
    int east;
    string tempEast;
    int south;
    string tempSouth;
    int west;
    string tempWest;

    ifstream theFile(FILE_NAME);
    if (!theFile.is_open()) {
        cout << " Failed to open" << endl;
    } else {
        cout << "File Opened Successfully" << endl;
    }

    while (theFile.good()) {
        getline(theFile, tempID, vertical);
        ID = stoi(tempID);
        getline(theFile, roomName, vertical);
        getline(theFile, roomDescript, vertical);
        getline(theFile, tempNorth, vertical);
        north = stoi(tempNorth);
        getline(theFile, tempEast, vertical);
        east = stoi(tempEast);
        getline(theFile, tempSouth, vertical);
        south = stoi(tempSouth);
        getline(theFile, tempWest, vertical);
        west = stoi(tempWest);
        m_myMap.push_back(new Room(ID, roomName, roomDescript, north, east, south, west));
//        m_allFoundables[count] = tempFoundable;
        ++count;
        if (count == 2 && FILE_NAME == "map1_data.txt") {
            theFile.close();
            break;
        }
        if (count == 10 && FILE_NAME == "map2_data.txt") {
            theFile.close();
            break;
        }
    }
// For testing
//    for (int i = 0; i < m_myMap.size(); ++i) {
//        cout << "Room " << i << endl;
//        m_myMap[i]->PrintRoom();
//    }
}

void Game::CharacterCreation() {
    int option;
    string userName;
    bool isValidOption = false;

    cout << "Welcome to UMBC Adventure" << endl;
    cout << "What is your Character name?" << endl;
    cin >> userName;
    while (!isValidOption) {
        cout << "What class do you want be?" << endl;
        cout << "1 Paladin" << endl;
        cout << "2 Rogue" << endl;
        cout << "3 Wizard" << endl;
        cout << "4 No class" << endl;
        cin >> option;
        switch (option) {
            case 1:
                m_myCharacter = new Paladin(userName, PALADIN_HEALTH);
                isValidOption = true;
                break;
            case 2:
                m_myCharacter = new Rogue(userName, ROGUE_HEALTH);
                isValidOption = true;
                break;
            case 3:
                m_myCharacter = new Wizard(userName, WIZARD_HEALTH);
                isValidOption = true;
                break;
            case 4:
                m_myCharacter = new Character(userName, 10);
                isValidOption = true;
                break;
            default:
                cout << INVALID_INPUT_NOTICE << endl;
        }
    }
}

void Game::Action() {
    int option;
    bool isQuit = false;
    do {
        cout << "What would you like to do?" << endl;
        cout << "1. Look" << endl;
        cout << "2. Move" << endl;
        cout << "3. Attack Monster" << endl;
        cout << "4. Rest" << endl;
        cout << "5. Check Stats" << endl;
        cout << "6. Quit" << endl;
        cin >> option;
        switch (option) {
            case 1:
                m_myMap[m_curRoom]->PrintRoom();
                break;
            case 2:
                Move();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                Stats();
                break;
            case 6:
                isQuit = true;
                cout << "\nGood bye" << endl;
                break;
            default:
                cout << INVALID_INPUT_NOTICE << endl;
        }
    } while (!isQuit);

}

void Game::Attack() {
    int attackOption;
    if (GetisMonsterSpawned()) {
        do {
            cout << "1. Normal Attack" << endl;
            cout << "2. Special Attack" << endl;
            cin >> attackOption;
            switch (attackOption) {
                case 1:
                    cout << m_myCharacter->Attack();

                    break;
                case 2:

                    break;
                default:
                    cout << "Invalid Option" << endl;
            }

        } while (m_curMonster->GetHealth() == 0);
    } else {
        cout << "There is no monster to fight" << endl;
    }
}

void Game::SetisMonsterSpawned(bool isMonsterSpawned) {
    m_isMonsterSpawned = isMonsterSpawned;
}

bool Game::GetisMonsterSpawned() {
    return m_isMonsterSpawned;
}

void Game::SetisCharMoved(bool isCharMoved) {
    m_isCharMoved = isCharMoved;
}

bool Game::GetisCharMoved() {
    return m_isCharMoved;
}

// Description: Moves a player from one room to another (updates m_curRoom)
// Preconditions: Must be valid move (room must exist)
// Postconditions: Displays room information, checks for new monster (deletes old)
void Game::Move() {
//            North
//West                  East
//            South
    char option;
//    bool isValid = false;
    int tempNum;
    int randNum = rand() % 2;
//    cout << "The size: " << m_myMap.size() << endl;

    cout << "Which direction? (N W E S)" << endl;
    cin >> option;
    tempNum = m_myMap[m_curRoom]->CheckDirection(option);
    if (tempNum != -1) {
        m_curRoom = tempNum;
        cout << m_curRoom << endl;
        m_myMap[m_curRoom]->PrintRoom();
        SetisCharMoved(true);
    }
    if (GetisMonsterSpawned() && GetisCharMoved()) {
        delete m_curMonster;
        SetisMonsterSpawned(false);
    }
    if (randNum == 1) {
        m_curMonster = RandomMonster();
        cout << m_curMonster->GetName() << " is lurking around the room" << endl;
        SetisMonsterSpawned(true);
    } else {
        cout << "It is peaceful in here" << endl;
    }


}

Entity *Game::RandomMonster() {
    Entity *monster;
    int randNum = rand() % 3;
    if (randNum == 0) {
        monster = new BabyDragon("Baby Dragon", DRAGON_HEALTH);
        return monster;
    }
    if (randNum == 1) {
        monster = new Goblin("Goblin", GOBLIN_HEALTH);
        return monster;
    }
    if (randNum == 2) {
        monster = new Skeleton("Skeleton", SKELETON_HEALTH);
        return monster;
    }
}

void Game::Stats() {
    cout << "Character name: " << m_myCharacter->GetName() << endl;
    cout << "Health: " << m_myCharacter->GetHealth() << endl;
    cout << "Rests: " << m_numRests << endl;
    cout << "Special Attack: " << m_numSpecial << endl;

}


