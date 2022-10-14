//
// Created by Aihua on 2020-08-13.
//

#include "Creature.h"

void Creature::reportOnHealthLevel(const Creature &creature) {
    std::cout << creature.getName() << " have " << creature.getHealthLevel() << " health left ..\n\n";
}
