/*
 * Author: Luis Augusto Espindola Caldas
*/

// Imports
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utils.h"

// Global constants
#define MAX_NUM_GUESS 6
#define LIMIT_GAMES 1000
// Global variables
int GAMES_PLAYED = 0;
int GAMES_WON = 0;
int HISTOGRAM_ARRAY[MAX_NUM_GUESS + 1][LIMIT_GAMES];

// Getting input from user using easy mode conditions
char *easy_get_user_input() {
    // Creating string that will be returned
    char *finalString;
    finalString = (char *) malloc(WORD_SIZE * sizeof(char) + 1);

    // Getting using input
    while (1) {
        char input = 0;
        char inputString[100];
        int stringSize = 0;
        printf("Enter a 5 letter word  >> ");
        while (input != '\n') {
            input = (char) getchar();
            if (input != '\n')
                inputString[stringSize] = input;
            stringSize++;
        }
        stringSize--;

        // Checking if input is valid
        if (stringSize == WORD_SIZE) {
            int validLetterCounter = 0;
            for (int i = 0; i < WORD_SIZE; ++i) {
                // Turning upper case to lower case
                if (inputString[i] >= 'A' && inputString[i] <= 'Z') {
                    inputString[i] = (char) ((int) inputString[i] + (int) ('z' - 'Z'));
                }
                // Checking if input is a letter
                if (inputString[i] >= 'a' && inputString[i] <= 'z') {
                    validLetterCounter++;
                }
            }
            // If string correct return it
            if (validLetterCounter == WORD_SIZE) {
                strcpy(finalString, inputString);
                return finalString;
            } else
                printf("Invalid Input\n");
        } else
            printf("Invalid input\n");
    }
}

// Getting input from user using hard mode conditions
char *hard_get_user_input(const char rightLetters[WORD_SIZE + 1]) {
    // Creating string that will be returned
    char *finalString;
    finalString = (char *) malloc(WORD_SIZE * sizeof(char) + 1);

    // Getting using input
    while (1) {
        char input = 0;
        char inputString[100];
        int stringSize = 0;
        printf("Enter a 5 letter word  >> ");
        while (input != '\n') {
            input = (char) getchar();
            if (input != '\n')
                inputString[stringSize] = input;
            stringSize++;
        }
        stringSize--;

        // Checking if input is valid
        if (stringSize == WORD_SIZE) {
            int validLetterCounter = 0;
            for (int i = 0; i < WORD_SIZE; ++i) {
                // Turning upper case to lower case
                if (inputString[i] >= 'A' && inputString[i] <= 'Z') {
                    inputString[i] = (char) ((int) inputString[i] + (int) ('z' - 'Z'));
                }
                // Checking if conditions match (letter and position of correct past letters)
                if (inputString[i] >= 'a' && inputString[i] <= 'z') {
                    if (rightLetters[i] != '-') {
                        if (rightLetters[i] == inputString[i]) {
                            validLetterCounter++;
                        }
                    } else {
                        validLetterCounter++;
                    }
                }
            }
            // Return string if correct
            if (validLetterCounter == WORD_SIZE) {
                strcpy(finalString, inputString);
                return finalString;
            } else
                printf("Invalid Input\n");
        } else
            printf("Invalid input\n");
    }
}

// Run guess game
void guess_game() {
    // Setting game mode
    int isHard;
    int input;
    printf("1. Hard Mode\n0. Easy mode\n>> ");
    input = getchar();
    getchar();
    if (input == '1')
        isHard = 1;
    else
        isHard = 0;

    // Loading file to 2d array
    char wordArray[DICT_SIZE][WORD_SIZE + 1];
    load_word_list(wordArray);

    // Selecting random word from 2d array
    srand(clock());
    int selectLine = rand() % DICT_SIZE;
    char randomWord[WORD_SIZE + 1];
    for (int i = 0; i < WORD_SIZE + 1; ++i) {
        randomWord[i] = wordArray[selectLine][i];
    }

    // Create strings
    char correctLetterArray[WORD_SIZE + 1];
    char printWord[WORD_SIZE + 1] = {'-', '-', '-', '-', '-'};
    char *userGuess;

    // Create variables
    int tries;
    int correctLetterCounter = 0;

    // Loop to compare user input to random word
    for (int guess = 0; guess < MAX_NUM_GUESS; ++guess) {

        // Take user input and save to array
        if (isHard)
            userGuess = hard_get_user_input(printWord);
        else
            userGuess = easy_get_user_input();

        // Compare each char from user input to random word
        for (int letterGuess = 0; letterGuess < WORD_SIZE; ++letterGuess) {
            for (int letterWord = 0; letterWord < WORD_SIZE; ++letterWord) {
                if (userGuess[letterGuess] == randomWord[letterWord]) {
                    // If letter in word insert into array
                    correctLetterArray[correctLetterCounter] = randomWord[letterWord];
                    correctLetterCounter++;
                }
                if (userGuess[letterWord] == randomWord[letterWord]) {
                    // If letter in correct position insert into array
                    printWord[letterWord] = randomWord[letterWord];
                }
            }
        }

        // Check if user won the game
        if (!(strcmp(userGuess, randomWord))) {
            printf("Congratulations! You got the word %s right.\n", randomWord);
            GAMES_WON++;
            break;
        }

        // Counting tries
        tries = guess;

        // Printing feedback to user
        printf("\nYou have %d tries left\n", MAX_NUM_GUESS - guess - 1);
        printf("You got %d letters right >> ", correctLetterCounter);
        for (int i = 0; i < correctLetterCounter; ++i) {
            printf("%c ", correctLetterArray[i]);
        }
        printf("\n");
        printf("%s\n", printWord);

        // Resetting variables
        if (!isHard) {
            for (int resetIndex = 0; resetIndex < WORD_SIZE; ++resetIndex) {
                printWord[resetIndex] = '-';
            }
        }
        correctLetterCounter = 0;
    }

    // Printing if user did not get the word right
    if (strcmp(userGuess, randomWord) != 0) {
        printf("Unfortunately you did not get the right word.\n");
        printf("The correct word was >> %s\n", randomWord);
    }

    // Free allocated memory
    free(userGuess);

    // Create histogram
    for (int i = 0; i < WORD_SIZE; ++i) {
        HISTOGRAM_ARRAY[GAMES_PLAYED][i] = ' ';
    }
    for (int numGuess = 0; numGuess < tries; ++numGuess) {
        HISTOGRAM_ARRAY[GAMES_PLAYED][numGuess] = '*';
    }

    GAMES_PLAYED++;
}

// Print status of games played so far
void printStats() {
    if (GAMES_PLAYED > 0) {
        // Percentage of games won
        printf("Percentage of games won >> %d%c\n", (GAMES_WON / GAMES_PLAYED) * 100, '%');

        // Histogram of each game
        printf("Histogram of each game:\n");
        for (int i = 0; i < GAMES_PLAYED; ++i) {
            printf("Game %d >> ", i + 1);
            for (int j = 0; j < MAX_NUM_GUESS; ++j) {
                printf("%c", HISTOGRAM_ARRAY[i][j]);
            }
            printf("\n");
        }
    } else
        printf("No games played yet\n");
}

int main() {
    // Interactive menu
    int input;
    while (1) {
        printf("1. Play Game\n2. Games Stats\n0. Quit\n>> ");
        input = getchar();
        getchar();
        switch (input) {
            case '0':
                return 0;

            case '1':
                guess_game();
                break;

            case '2':
                printStats();
                break;

            default:
                break;
        }
    }
}