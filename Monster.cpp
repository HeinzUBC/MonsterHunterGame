//
// Created by Aihua on 2020-08-13.
//

#include "Monster.h"
#include "Player.h"
#include "RandomNumberGeneration.h"

const std::vector<Monster::MonsterData> Monster::monsterDataTable = {{"dragon", 'D',
                                                                      25, 15,
                                                                      100},
                                                                     {"orc", 'o',
                                                                      20, 5,
                                                                      25},
                                                                     {"slime", 's',
                                                                      5, 5,
                                                                      10},
                                                                     {"demon", '*',
                                                                      20, 10,
                                                                      75},
                                                                     {"werewolf",'&',
                                                                      20, 10,
                                                                      40}};

Monster Monster::getRandomMonster() {
    std::uniform_int_distribution randNum{0, Type::NUM_TYPES - 1};
    int monsterTypeNumber{randNum(myRand::mersenne)};
    return Monster{static_cast<Type>(monsterTypeNumber)};
}

// allows monster to attack the player, decreasing player's health by
// the monster's damage points
void Monster::attackPerson(Player& player) {
    switch (symbol) {
        case 'D':
            std::cout << "Ahh!!! The " << name << " has just unleashed a massive fire attack!\n"
                      << "You have been toasted .... and lost "
                      << damageDonePerAttack << " health points ... \n\n";
            break;
        case 'o':
            std::cout << "Ahh!!! The " << name << " has just unleashed a massive punch attack!\n"
                      << "You have been smashed .... and lost "
                      << damageDonePerAttack << " health points ... \n\n";
            break;
        case 's':
            std::cout << "Ahh!!! The " << name << " has just unleashed an acidic goo attack!\n"
                      << "You have been corroded .... and lost "
                      << damageDonePerAttack << " health points ... \n\n";
            break;
        case '*':
            std::cout << "Ahh!!! The " << name << " has just conjured a dark magic attack!\n"
                      << "You have been ravaged .... and lost "
                      << damageDonePerAttack << " health points ... \n\n";
            break;
        case '&':
            std::cout << "Ahh!!! The " << name << " has just took a ferocious bite at its prey!\n"
                      << "You is bleeding profusely .... and lost "
                      << damageDonePerAttack << " health points ... \n\n";
            break;
        default:
            std::cout << "Something wrong here. Debug code immediately!!\n\n";
            break;
    }
    player.reduceHealth(damageDonePerAttack);
}
