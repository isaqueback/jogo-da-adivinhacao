#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Function to clear the input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to get a valid difficulty level from the user
int getDifficultyLevel() {
    int level;
    while (1) {
        printf("Choose the difficulty level\n");
        printf("1 (Easy) 2 (Medium) 3 (Hard): ");
        if (scanf("%d", &level) == 1 && (level >= 1 && level <= 3)) {
            clearInputBuffer(); // Clear the buffer after a valid input
            return level;
        } else {
            printf("Invalid input. Please enter 1, 2, or 3.\n\n");
            clearInputBuffer(); // Clear the buffer on invalid input
        }
    }
}

// Function to get the number of attempts based on the difficulty level
int getNumberOfAttempts(int level) {
    switch (level) {
        case 1:
            printf("You chose the easy level. You have 15 attempts.\n\n");
            return 15;
        case 2:
            printf("You chose the medium level. You have 10 attempts.\n\n");
            return 10;
        case 3:
            printf("You chose the hard level. You have 5 attempts.\n\n");
            return 5;
        default:
            return 5; // Default case should not be reached
    }
}

int main() {
    printf("********************************\n");
    printf("* WELCOME TO OUR GUESSING GAME *\n");
    printf("********************************\n\n");

    // Seed the random number generator
    srand(time(0));
    int secretNumber = rand() % 100; // Secret number between 0 and 99

    int guess;
    int isCorrectGuess;
    double score = 1000;
    double lostPoints;
    int level = getDifficultyLevel();
    int attempts = getNumberOfAttempts(level);

	int attempt;
    for (attempt = 1; attempt <= attempts; attempt++) {
        printf("Attempt number %d\n", attempt);
        printf("Enter your guess: ");

        // Validate the user input
        if (scanf("%d", &guess) != 1) {
            printf("Your guess is not a valid integer. Try again.\n\n");
            clearInputBuffer(); // Clear the buffer on invalid input
            attempt--; // Decrement the attempt counter to retry this attempt
            continue;
        }

        isCorrectGuess = (guess == secretNumber);
        lostPoints = fabs((secretNumber - guess) / 2.0);
        score -= lostPoints;
        if (score < 0) score = 0;

        if (isCorrectGuess) {
            printf("Congratulations! You guessed the right number in attempt %d :)\n", attempt);
            printf("Your score is %.2f\n", score);
            break;
        } else {
            if (guess > secretNumber) {
                printf("You guessed wrong. Your guess was BIGGER than the secret number.\n\n");
            } else {
                printf("You guessed wrong. Your guess was LOWER than the secret number.\n\n");
            }

            if (attempt == attempts) {
                printf("Unfortunately, you exhausted your attempts. The secret number was %d.\n", secretNumber);
            }
        }
    }

    return 0;
}
