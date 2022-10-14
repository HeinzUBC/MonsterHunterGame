//
// Created by Aihua on 2020-08-13.
//

#ifndef MONSTERHUNTERGAME_CREATURE_H
#define MONSTERHUNTERGAME_CREATURE_H

#include <string>
#include <iostream>

class Creature {
protected:
    std::string name{};
    char symbol{};
    int healthLevel{};
    int damageDonePerAttack{};
    int amountOfGoldCarried{};
public:
    Creature(const std::string& name, char symbol, int healthLevel, int damagePerAttack, int goldAmount)
            : name{name}, symbol{symbol}, healthLevel{healthLevel}, damageDonePerAttack{damagePerAttack},
              amountOfGoldCarried{goldAmount} {}

    const std::string& getName() const {
        return name;
    }

    char getSymbol() const {
        return symbol;
    }

    int getHealthLevel() const {
        return healthLevel;
    }

    int getDamageDonePerAttack() const {
        return damageDonePerAttack;
    }

    int getAmountOfGoldCarried() const {
        return amountOfGoldCarried;
    }

    void reduceHealth(int lossAmount) {
        healthLevel = healthLevel - lossAmount;
    }

    bool isDead() const {
        return (healthLevel <= 0);
    }

    void addGold(int addAmount) {
        amountOfGoldCarried = amountOfGoldCarried + addAmount;
    }

    static void reportOnHealthLevel(const Creature& creature);
};

#endif //MONSTERHUNTERGAME_CREATURE_H
