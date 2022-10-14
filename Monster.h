//
// Created by Aihua on 2020-08-13.
//

#ifndef MONSTERHUNTERGAME_MONSTER_H
#define MONSTERHUNTERGAME_MONSTER_H

#include "Creature.h"
#include <vector>

class Player;

class Monster : public Creature {
private:
    struct MonsterData {
        std::string monsterName{};
        char monsterSymbol{};
        int monsterHealthLevel{};
        int monsterDamageDonePerAttack{};
        int monsterAmountOfGoldCarried{};
    };

    static const std::vector<MonsterData> monsterDataTable;

public:
    enum Type {
        DRAGON,
        ORC,
        SLIME,
        DEMON,
        WEREWOLF,
        NUM_TYPES,
    };

    Monster(Type monsterType) : Creature{monsterDataTable[monsterType].monsterName,
                                         monsterDataTable[monsterType].monsterSymbol,
                                         monsterDataTable[monsterType].monsterHealthLevel,
                                         monsterDataTable[monsterType].monsterDamageDonePerAttack,
                                         monsterDataTable[monsterType].monsterAmountOfGoldCarried} {}

    static Monster getRandomMonster();

    void attackPerson(Player& player);
};

#endif //MONSTERHUNTERGAME_MONSTER_H
