cmake_minimum_required(VERSION 3.15)
project(Project4)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project4 main.cpp
        Entity.h
        Game.h
        Goblin.h
        Monster.h
        Paladin.h
        Rogue.h
        Room.h
        Character.h
        BabyDragon.h
        Skeleton.h
        Wizard.h
        Entity.cpp
        Monster.cpp
        Goblin.cpp
        Skeleton.cpp
        BabyDragon.cpp
        Character.cpp
        Paladin.cpp
        Rogue.cpp
        Wizard.cpp
        Room.cpp
        Game.cpp)

#add_executable(Project4_2 main.cpp
#        Entity.h
#        Game.h
#        Goblin.h
#        Monster.h
#        Paladin.h
#        Rogue.h
#        Room.h
#        Character.h
#        BabyDragon.h
#        Skeleton.h
#        Wizard.h
#        Entity.cpp
#        Monster.cpp
#        Goblin.cpp
#        Skeleton.cpp
#        BabyDragon.cpp
#        Character.cpp
#        Paladin.cpp
#        Rogue.cpp
#        Wizard.cpp
#        Room.cpp
#        Game.cpp)