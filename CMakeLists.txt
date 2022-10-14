cmake_minimum_required(VERSION 3.16)
project(MonsterHunterGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(MonsterHunterGame main.cpp Creature.cpp Creature.h Player.cpp Player.h Monster.cpp Monster.h RandomNumberGeneration.h GameLogic.cpp GameLogic.h RandomNumberGeneration.cpp)