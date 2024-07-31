#ifndef GUESSING_GAME_H
#define GUESSING_GAME_H

#include <iostream>
#include <cstdlib>
#include <ctime>

class GuessingGame {
private:
    int numberToGuess;
    int numberOfAttempts;

public:
    GuessingGame() : numberOfAttempts(0) {
        // Seed the random number generator
        std::srand(std::time(nullptr));
        // Generate a random number between 1 and 100
        numberToGuess = std::rand() % 100 + 1;
    }

    void play() {
        int userGuess = 0;
        std::cout << "Welcome to the Guessing Game!" << std::endl;
        std::cout << "I have selected a random number between 1 and 100." << std::endl;
        std::cout << "Can you guess what it is?" << std::endl;

        while (userGuess != numberToGuess) {
            std::cout << "Enter your guess: ";
            std::cin >> userGuess;
            numberOfAttempts++;

            if (userGuess > numberToGuess) {
                std::cout << "Too high! Try again." << std::endl;
            } else if (userGuess < numberToGuess) {
                std::cout << "Too low! Try again." << std::endl;
            } else {
                std::cout << "Congratulations! You guessed the number in " << numberOfAttempts << " attempts." << std::endl;
            }
        }
    }
};
#endif // GUESSING_GAME_H
