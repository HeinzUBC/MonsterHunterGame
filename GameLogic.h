//
// Created by Aihua on 2020-08-13.
//

#ifndef MONSTERHUNTERGAME_GAMELOGIC_H
#define MONSTERHUNTERGAME_GAMELOGIC_H

#include "iostream"
#include "Player.h"
#include "Monster.h"

enum class BattleOutcomes {
    ESCAPED,
    VICTORY,
    ONGOING,
    DEFEAT,
};

void gameIntroduction();

std::string obtainPlayerName();

// Welcomes the new player to the game, and sets the scene for battle
void gameStartMessage(const Player& player);

// Describes the monster that the player will be facing
void monsterEntryMessage(const Monster& monster);

// collects the player's decision on how to deal with the monster
char playerDecision();

// returns true if player successfully escaped from monster
bool isEscapeSuccessful();

// Determines the outcome of a single round when battling a monster
BattleOutcomes decisionOutcomes(Monster& monster, Player& player, char decision);

// models the entire battle sequence between a monster and a
// player
BattleOutcomes BattleEvents(Player& player, Monster& monster);

// computes the amount of health points a player could recover.
// ranges from 1 to 5.
int generateHealthPointGain();

// congratulates player on beating the monster, as well as letting
// them know about their rewards
void victoryMessage(Player& player, const Monster& monster);

// message for player if they managed to beat the odds and beat all monsters
void goodEndingMessage(const Player& player);

// message for player if they were unfortunately slain by monsters
void sadEndingMessage(const Player& player);

// models the battleground, with waves of monsters attacking the player
void BattleGround(Player& player);

// allows user to choose their character and starts the actual game
void GameSequence();

// the complete monster hunter game
void MonsterHunterGame();

// prompts the user to replay or end the game
void playAgain();

#endif //MONSTERHUNTERGAME_GAMELOGIC_H
