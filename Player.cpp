//
// Created by Aihua on 2020-08-13.
//

#include "Player.h"
#include "Monster.h"

void Player::attackMonster(Monster& monster) {
    std::cout << "You took a mighty swing of the sword and slashed the "
              << monster.getName() << " viciously.\nThe " << monster.getName()
              << " is wounded, losing " << damageDonePerAttack << " health points!!\n\n";

    monster.reduceHealth(damageDonePerAttack);
}

void Player::increaseHealth(int healthPts) {
    healthLevel = healthLevel + healthPts;
    std::cout << "With the monster slayed, you have time to scavenge for health potions.\n"
                 "You found some luckily, and have now increased your health by " << healthPts
              << " points!!\n\n";
}



