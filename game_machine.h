#ifndef GAME_MACHINE_H
#define GAME_MACHINE_H

#include <stdio.h>

// Function to play sound for winning or losing
void playSound(int frequency, int duration);

// Function to draw a card
int drawCard();

// Function to determine the winner of the Blackjack game
int declareWinner(int playerTotal, int dealerTotal);

// Function to simulate the slot machine
int spinSlotMachine();

// Function to update the transaction log
void updateTransactionLog(FILE *logFile, const char *gameName, int startBalance, int bet, int result, int endBalance);

#endif
