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
    for (int i = 0; i < m_myMap.size(); ++i) {
        delete m_myMap[i];
    }
    delete m_myCharacter;
    delete m_curMonster;
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
                SetOriginalHealth(PALADIN_HEALTH);
                isValidOption = true;
                break;
            case 2:
                m_myCharacter = new Rogue(userName, ROGUE_HEALTH);
                SetOriginalHealth(ROGUE_HEALTH);
                isValidOption = true;
                break;
            case 3:
                m_myCharacter = new Wizard(userName, WIZARD_HEALTH);
                SetOriginalHealth(WIZARD_HEALTH);
                isValidOption = true;
                break;
            case 4:
                m_myCharacter = new Character(userName, 10);
                SetOriginalHealth(10);
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
                Attack();
                if (m_myCharacter->GetHealth() <= 0) {
                    isQuit = true;
                }
                break;
            case 4:
                Rest();
                m_numRests--;
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
    bool isEnd = false;
    if (GetisMonsterSpawned()) {
        do {
            int attackOption;
            int charAttackHealth;
            int monsAttackHealth;
            int randSpecialAttack = rand() % 3 + 1;
            cout << "1. Normal Attack" << endl;
            cout << "2. Special Attack" << endl;
            cin >> attackOption;
            switch (attackOption) {
                case 1:
                    if (randSpecialAttack == 2) {
                        charAttackHealth = m_myCharacter->Attack();
                        monsAttackHealth = m_curMonster->SpecialAttack();
                        m_curMonster->SetHealth(m_curMonster->GetHealth() - charAttackHealth);
                        m_myCharacter->SetHealth(m_myCharacter->GetHealth() - monsAttackHealth);
                        if (m_curMonster->GetHealth() <= 0) {
                            cout << m_curMonster->GetName() << " has been defeated" << endl;
                            isEnd = true;
                        }
                        if (m_myCharacter->GetHealth() <= 0) {
                            cout << m_myCharacter->GetName() << " has been defeated" << endl;
                            isEnd = true;
                        }
                    } else {
                        charAttackHealth = m_myCharacter->Attack();
                        monsAttackHealth = m_curMonster->Attack();
                        m_curMonster->SetHealth(m_curMonster->GetHealth() - charAttackHealth);
                        m_myCharacter->SetHealth(m_myCharacter->GetHealth() - monsAttackHealth);
                        if (m_curMonster->GetHealth() <= 0) {
                            cout << m_curMonster->GetName() << " has been defeated" << endl;
                            isEnd = true;
                        }
                        if (m_myCharacter->GetHealth() <= 0) {
                            cout << m_myCharacter->GetName() << " has been defeated" << endl;
                            isEnd = true;
                        }
                    }
                    break;
                case 2:
                    if (randSpecialAttack == 2) {
                        if (m_numSpecial > 0) {
                            charAttackHealth = m_myCharacter->SpecialAttack();
                            m_numSpecial--;
                        } else {
                            cout << "You are out of special attack" << endl;
                            charAttackHealth = m_myCharacter->Attack();
                        }
                        monsAttackHealth = m_curMonster->SpecialAttack();
                        m_curMonster->SetHealth(m_curMonster->GetHealth() - charAttackHealth);
                        m_myCharacter->SetHealth(m_myCharacter->GetHealth() - monsAttackHealth);
                        if (m_curMonster->GetHealth() <= 0) {
                            cout << m_curMonster->GetName() << " has been defeated" << endl;
                            isEnd = true;
                        }
                        if (m_myCharacter->GetHealth() <= 0) {
                            cout << m_myCharacter->GetName() << " has been defeated" << endl;
                            isEnd = true;
                        }
                    } else {
                        if (m_numSpecial > 0) {
                            charAttackHealth = m_myCharacter->SpecialAttack();
                            m_numSpecial--;
                        } else {
                            cout << "You are out of special attack" << endl;
                            charAttackHealth = m_myCharacter->Attack();
                        }
                        monsAttackHealth = m_curMonster->Attack();
                        m_curMonster->SetHealth(m_curMonster->GetHealth() - charAttackHealth);
                        m_myCharacter->SetHealth(m_myCharacter->GetHealth() - monsAttackHealth);
                        if (m_curMonster->GetHealth() <= 0) {
                            cout << m_curMonster->GetName() << " has been defeated" << endl;
                            isEnd = true;
                        }
                        if (m_myCharacter->GetHealth() <= 0) {
                            cout << m_myCharacter->GetName() << " has been defeated" << endl;
                            isEnd = true;
                        }
                    }
                    break;
                default:
                    cout << "Invalid Option" << endl;
            }
        } while (!isEnd);
    } else {
        cout << "There is no monster to fight" << endl;
    }
}

void Game::Rest() {
    if ((!GetisMonsterSpawned() || m_curMonster->GetHealth() <= 0) &&
        m_numRests > 0 &&
        (m_myCharacter->GetHealth() <= GetOriginalHealth() || m_numSpecial < NUM_SPECIAL)) {
        if (m_numSpecial <= NUM_SPECIAL) {
            m_numSpecial = NUM_SPECIAL;
            cout << "Your special attack has been restored to the original" << endl;
        }

        if (m_myCharacter->GetHealth() <= GetOriginalHealth()) {
            int tempHealth;
            tempHealth = GetOriginalHealth() - m_myCharacter->GetHealth();
            if (tempHealth < REST_HEAL) {
                m_myCharacter->SetHealth(m_myCharacter->GetHealth() + tempHealth);
                cout << "Your health has been restored" << endl;
            }
            if (tempHealth == REST_HEAL) {
                m_myCharacter->SetHealth(m_myCharacter->GetHealth() + REST_HEAL);
                cout << "Your health has been restored" << endl;
            }
        }
    }
    if (GetisMonsterSpawned() && m_curMonster->GetHealth() > 0) {
        cout << "You cannot rest while the " << m_curMonster->GetName() << " is in " << m_myMap[m_curRoom]->GetName()
             << endl;
    }
    if (m_numRests <= 0) {
        cout << "You don't have any rest left" << endl;
    }
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

void Game::SetOriginalHealth(int ogHealth) {
    m_originalHealth = ogHealth;
}

int Game::GetOriginalHealth() {
    return m_originalHealth;
}


