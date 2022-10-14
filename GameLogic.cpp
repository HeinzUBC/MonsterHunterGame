//
// Created by Aihua on 2020-08-13.
//

#include "GameLogic.h"
#include "RandomNumberGeneration.h"
#include <string>
#include <limits>

void gameIntroduction() {
    std::cout << "Welcome to playing Monster Hunter!!\n\n"
              << "The rules are as follows:\n\n"
              << "1) The player encounters one randomly generated monster at a time\n"
              << "2) For each monster, the player has two choices:\n"
              << "        I) Enter 'r' to run away\n"
              << "       II) Enter 'f' to fight the monster\n"
              << "3) If the player decides to run, they have a 50% chance of escaping\n"
              << "   to the next monster without harm\n"
              << "4) However, if the player failed to escape, the monster gets a free attack,\n"
                 "   and the player can decide whether to flee or to fight\n"
              << "5) If the player chooses to fight, the player attacks first. The monster's\n"
                 "   health is reduced by the player's damage\n"
              << "6) If the monster dies, the player takes any gold the monster is carrying.\n"
                 "   The player also levels up, increasing their level and damage by 1\n"
              << "7) If the monster does not die, the monster attacks the player back.\n"
                 "   The player's health is reduced by the monster's damage\n"
              << "8) The game ends when the player has died (loss) or reached level 20 (win)\n\n";
}

std::string obtainPlayerName() {
    std::string playerName{};
    std::cout << "Before we start though, you must create a character.\n\n"
                 "What is your character's name? ";
    std::cin >> playerName;
    std::cout << '\n';
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    return playerName;
}

// Welcomes the new player to the game, and sets the scene for battle
void gameStartMessage(const Player& player) {
    std::cout << "Welcome " << player.getName()
              << ". You possess " << player.getHealthLevel() << " health and can perform "
              << player.getDamageDonePerAttack() << " damage each time you attack.\n"
                 "You have now entered the battleground.\n\n"
              << "Good luck!!!\n\n";
}

// Describes the monster that the player will be facing
void monsterEntryMessage(const Monster& monster) {
    std::cout << "A " << monster.getName() << " (" << monster.getSymbol()
              << ") " << "appears!! It is looking very hungry and menacing!\n\n"
                      << "It has " << monster.getHealthLevel() << " health and does "
                      << monster.getDamageDonePerAttack() << " damage when it attacks!!\n\n";
}

// collects the player's decision on how to deal with the monster
char playerDecision() {
    char decision{};

    while (true) {
        std::cout << "What are you going to do now? "
                     "Enter 'f' to fight or 'r' to escape: ";
        std::cin >> decision;
        std::cout << '\n';
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        if ((decision == 'f') || (decision == 'r')) {
            return decision;
        }
        std::cout << "incorrect input. Please try again.\n\n";
    }
}

// returns true if player successfully escaped from monster
bool isEscapeSuccessful() {
    std::uniform_int_distribution randNum{0, 1};
    return static_cast<bool>(randNum(myRand::mersenne));
}

// Determines the outcome of a single round when battling a monster
BattleOutcomes decisionOutcomes(Monster& monster, Player& player, char decision) {
    if (decision == 'r') {
        std::cout << "You try to evade the " << monster.getName() << " .... ";
        if (isEscapeSuccessful()) {
            std::cout << "and you managed to escape!!\n"
                         "You were really lucky there!\n\n";
            Creature::reportOnHealthLevel(player);
            return BattleOutcomes::ESCAPED;
        }
        std::cout << "Oh no!!\nThe " << monster.getName() << " grabbed you as you ran and threw you on the ground!!\n"
                     "Ouch!! ... \n\n";

        monster.attackPerson(player);
        if (player.isDead()) {
            return BattleOutcomes::DEFEAT;
        }
        Creature::reportOnHealthLevel(player);

        return BattleOutcomes::ONGOING;
    }

    player.attackMonster(monster);
    if (monster.isDead()) {
        return BattleOutcomes::VICTORY;
    }
    Creature::reportOnHealthLevel(monster);

    monster.attackPerson(player);
    if (player.isDead()) {
        return BattleOutcomes::DEFEAT;
    }
    Creature::reportOnHealthLevel(player);
    return BattleOutcomes::ONGOING;
}

// models the entire battle sequence between a monster and a
// player
BattleOutcomes BattleEvents(Player& player, Monster& monster) {
    char decision{};
    BattleOutcomes outcome{};
    while (true) {
        decision = playerDecision();
        outcome = decisionOutcomes(monster, player, decision);
        if ((outcome == BattleOutcomes::ESCAPED) ||
            (outcome == BattleOutcomes::VICTORY) ||
            (outcome == BattleOutcomes::DEFEAT)) {
            return outcome;
        }
    }
}

// computes the amount of health points a player could recover.
// ranges from 1 to 5.
int generateHealthPointGain() {
    std::uniform_int_distribution randNum{1, 5};
    return randNum(myRand::mersenne);
}

// congratulates player on beating the monster, as well as letting
// them know about their rewards
void victoryMessage(Player& player, const Monster& monster) {
    std::cout << "WOW!! You took down the " << monster.getName()
              << "!! As reward, you shall receive " << monster.getAmountOfGoldCarried()
              << " gold coins,\nand your attack power is now " << player.getDamageDonePerAttack()
              << "!! You have also been upgraded\nto level " << player.getLevel()
              << " as well!!\n\n";
    player.increaseHealth(generateHealthPointGain());
    std::cout << "You now possess " << player.getAmountOfGoldCarried() << " gold coins in total "
                 "and " << player.getHealthLevel() << " health points\n\n";
}

// message for player if they were unfortunately slain by monsters
void sadEndingMessage(const Player& player) {
    std::cout << "You put up a heroic fight, " << player.getName()
              << " ... but there were too many monsters, and you have\n"
                 "lost your life on the scorched battlefield ... alas,"
                 "\nwe wished you could have made it home alive ... you just had\n"
              << (maxLevel - player.getLevel()) << " monsters left to slay ...\n\n";
}

// message for player if they managed to beat the odds and beat all monsters
void goodEndingMessage(const Player& player) {
    std::cout << "You have faced unthinkable horrors on the battleground,\n"
                 "yet you used your cunning and courage to survive ... \n"
                 "congratulations, warrior " << player.getName() << "!\n\n";
    std::cout << "We hope you can use the " << player.getAmountOfGoldCarried()
              << " gold coins you have earned to recover from the trauma\n\n";
}

// models the battleground, with waves of monsters attacking the player
void BattleGround(Player& player) {
    BattleOutcomes outcome{};
    while ((!player.isDead()) && (!player.hasWon())) {
        Monster beast{Monster::getRandomMonster()};
        monsterEntryMessage(beast);
        outcome = BattleEvents(player,beast);
        if (outcome == BattleOutcomes::VICTORY) {
            player.addGold(beast.getAmountOfGoldCarried());
            player.levelUp();
            victoryMessage(player, beast);
        }
    }

    if (outcome == BattleOutcomes::DEFEAT) {
        sadEndingMessage(player);
        return;
    }

    if (outcome == BattleOutcomes::VICTORY) {
        goodEndingMessage(player);
    }
}

// allows user to choose their character and starts the game
void GameSequence() {
    Player warrior{obtainPlayerName()};
    gameStartMessage(warrior);
    BattleGround(warrior);
}

// the complete monster hunter game
void MonsterHunterGame() {
    gameIntroduction();
    GameSequence();
    playAgain();
}

// prompts the user to replay or end the game
void playAgain() {
    std::cout << "I know battling those hordes of beasts was not easy, but we need you\n"
                 "on the front line. Have a break for now, but do let us know if you are\n"
                 "coming back warrior\n\n";
    std::cout << "If you are rejoining us on the battlefield, enter 'y'\n"
                 "If you still need a break from the war, enter 'n'\n\n";
    char input{};
    while (true) {
        std::cout << "You input is: ";
        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "\n";
        if (input == 'y') {
            GameSequence();
            playAgain();
            break;
        } else if (input == 'n') {
            break;
        }
        std::cout << "Invalid input. Please try again.\n\n";
    }
}