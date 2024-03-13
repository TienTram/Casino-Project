#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Function to play sound for winning or losing
void playSound(int frequency, int duration) {
    Beep(frequency, duration);
    Sleep(100);  // Sleep for 100 milliseconds to allow the sound to finish
}

// Function to draw a card
int drawCard() {
    return rand() % 10 + 1;  // Drawing a card between 1 and 10
}

// Function to determine the winner of the Blackjack game
int declareWinner(int playerTotal, int dealerTotal) {
    if (playerTotal > 21 || (dealerTotal <= 21 && dealerTotal >= playerTotal)) {
        return -1;  // Player loses
    } else {
        return 1;   // Player wins
    }
}

// Function to simulate the slot machine
int spinSlotMachine() {
    return rand() % 3;  // Returns 0, 1, or 2
}

// Function to update the transaction log
void updateTransactionLog(FILE *logFile, const char *gameName, int startBalance, int bet, int result, int endBalance) {
    fprintf(logFile, "%s: Started with $%d, Bet $%d, ", gameName, startBalance, bet);

    if (result == 0) {
        fprintf(logFile, "Lost $%d, ", bet);
    } else if (result == 1) {
        fprintf(logFile, "Broke even, ");
    } else {
        fprintf(logFile, "Won $%d, ", 2 * bet);
    }

    fprintf(logFile, "End Balance: $%d\n", endBalance);
}

int main() {
    srand(time(NULL));

    int money = 500;
    char choice;
    FILE *logFile = fopen("money_log.txt", "w");  // Open log file for writing

    if (logFile == NULL) {
        printf("Error opening log file.\n");
        return 1;
    }

    fprintf(logFile, "Game Log:\n");

    do {
        system("cls");  // Clear the console

        printf("Welcome to the Text-Based Game Machine\n");
        printf("Current Money: $%d\n", money);
        printf("Choose a game:\n");
        printf("A) Blackjack\n");
        printf("B) Slot Machine\n");
        printf("Q) Quit\n");

        scanf(" %c", &choice);

        switch (choice) {
            case 'A':
            case 'a': {
                // Blackjack code
                int decks, bet;
                int startBalance = money;
                int result;
                int playerTotal = 0, dealerTotal = 0;

                printf("Enter the number of decks (1-8): ");
                scanf("%d", &decks);

                printf("Enter your bet: $");
                scanf("%d", &bet);

                // Draw initial cards
                playerTotal += drawCard() + drawCard();
                dealerTotal += drawCard() + drawCard();

                // Game loop
                char hit;
                do {
                    printf("Your total: %d\n", playerTotal);
                    printf("Do you want to hit? (Y/N): ");
                    scanf(" %c", &hit);

                    if ((hit == 'Y' || hit == 'y') && playerTotal <= 21) {
                        playerTotal += drawCard();
                    }

                } while ((hit == 'Y' || hit == 'y') && playerTotal <= 21);

                // Dealer's turn
                while (dealerTotal < 17) {
                    dealerTotal += drawCard();
                }

                // Declare the winner and update money
                result = declareWinner(playerTotal, dealerTotal);
                if (result == 1) {
                    playSound(523, 500);  // Play winning sound
                    printf("You win! +%d\n", bet);
                    money += bet;
                } else {
                    playSound(349, 500);  // Play losing sound
                    printf("You lose! -%d\n", bet);
                    money -= bet;
                }

                // Prompt for repetition
                printf("Do you want to play again? (Y/N): ");
                scanf(" %c", &choice);

                // Update the transaction log
                updateTransactionLog(logFile, "Blackjack", startBalance, bet, result, money);
                break;
            }
            case 'B':
            case 'b': {
                // Slot machine code
                int bet;
                int startBalance = money;
                int result;

                printf("Enter your bet: $");
                scanf("%d", &bet);

                // Spin the slot machine
                int slot1 = spinSlotMachine();
                int slot2 = spinSlotMachine();
                int slot3 = spinSlotMachine();

                // Display the slot results
                printf("Slot Machine: %d %d %d\n", slot1, slot2, slot3);

                // Determine the result
                if (slot1 == slot2 && slot2 == slot3) {
                    playSound(523, 500);  // Play winning sound
                    result = 2;  // x2 of the bet for all three numbers matching
                    money += 2 * bet;
                } else if (slot1 == slot2 || slot2 == slot3 || slot1 == slot3) {
                    playSound(349, 500);  // Play winning sound
                    result = 1;  // x1 of the bet for the first two numbers matching
                    money += bet;
                } else {
                    playSound(261, 500);  // Play losing sound
                    result = 0;  // Lost the bet
                    money -= bet;
                }

                // Prompt for repetition
                printf("Do you want to play again? (Y/N): ");
                scanf(" %c", &choice);

                // Update the transaction log
                updateTransactionLog(logFile, "Slot Machine", startBalance, bet, result, money);
                break;
            }
            case 'Q':
            case 'q':
                printf("Thanks for playing!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 'Q' && choice != 'q' && money > 0);

    fclose(logFile);  // Close the log file

    return 0;
}
