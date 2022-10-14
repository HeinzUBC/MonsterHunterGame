//
// Created by Aihua on 2020-08-13.
//

#ifndef MONSTERHUNTERGAME_PLAYER_H
#define MONSTERHUNTERGAME_PLAYER_H

#include "Creature.h"
class Monster;

inline constexpr int maxLevel{20};

class Player : public Creature {
private:
    int playerLevel{};
public:
    Player(const std::string& playerName)
          : Creature{playerName, '@', 50, 5, 0}, playerLevel{0} {}

    void levelUp() {
        ++playerLevel;
        if (damageDonePerAttack < 15) {
            ++damageDonePerAttack;
        }
    }

    int getLevel() const {
        return playerLevel;
    }

    bool hasWon() {
        return (playerLevel == maxLevel);
    }

    void increaseHealth(int healthPts);

    void attackMonster(Monster& monster);
};

#endif //MONSTERHUNTERGAME_PLAYER_H
