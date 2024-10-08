#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

void displayMenu();
void Dino();
void move();
void obstacle();
void checkCollision();
void scoreboard();
void gameOver();

int score = 0;       // Initialize score
int isJumping = 0;   // Flag for jump status

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
    system("chcp 437 > nul");  // Sets code page to 437 (OEM US)
    displayMenu();
    return 0;
}

void displayMenu() {
    system("cls");  // Clear the screen
    int choice = 0;   // 0 = New Game, 1 = About, 2 = Exit
    while (1) {
        printf(choice == 0 ? ">>New Game\n" : "  New Game\n");
        printf(choice == 1 ? ">>About\n" : "  About\n");
        printf(choice == 2 ? ">>Exit\n" : "  Exit\n");

        int key = _getch();
        if (key == 224) {    // Special key detected
            key = _getch();
            switch (key) {
                case 72:  // Up arrow key
                    choice = choice - 1;
                    if (choice < 0) choice = 2;
                    break;
                case 80:  // Down arrow key
                    choice = choice + 1;
                    if (choice > 2) choice = 0;
                    break;
            }
        } else if (key == 13) {  // Enter Key
            if (choice == 0) {
                printf("Welcome to the Game...\n");
                score = 0;  // Reset score
                move();      // Start the game loop
            } else if (choice == 1) {
                printf("This game is created by Thai studio...\n");
            } else if (choice == 2) {
                printf("Exiting...\n");
                break;
            }
            _getch();  // Pause before returning to menu
        }
        system("cls");  // Clear screen after each key press to update menu
    }
}

void Dino(int yPosition) {
    // Draw the dinosaur at a specific y position
    gotoxy(10, yPosition);
    printf("      ########\n");
    gotoxy(10, yPosition + 1);
    printf("      ####  #####\n");
    gotoxy(10, yPosition + 2);
    printf("      ############\n");
    gotoxy(10, yPosition + 3);
    printf("      ############\n");
    gotoxy(10, yPosition + 4);
    printf("      ###### \n");
    gotoxy(10, yPosition + 5);
    printf("      ###### \n");
    gotoxy(10, yPosition + 6);
    printf("    ######## \n");
    gotoxy(10, yPosition + 7);
    printf("   ######### \n");
    gotoxy(10, yPosition + 8);
    printf(" ########### \n");
    gotoxy(10, yPosition + 9);
    printf("############\n");
    gotoxy(10, yPosition + 10);
    printf("  ####   ###  \n");
    gotoxy(10, yPosition + 11);
    printf("  ####   ###  \n");
    gotoxy(10, yPosition + 12);
    printf("  #####  ####\n");
}

void obstacle(int xPosition) {
    // Draw obstacle at a specific x position
    gotoxy(xPosition, 20);  // Lower row for obstacle
    printf("    #   \n");
    gotoxy(xPosition, 21);
    printf("   ###   \n");
    gotoxy(xPosition, 21);
    printf("    #   \n");
}

void move() {
    int dinoYPosition = 10;  // Y position of the dinosaur
    int obstacleX = 50;      // Initial position of the obstacle
    int jumpHeight = 8;      // Height to jump (reduce for faster jump)
    int jumpCounter = -2;     // To control jump duration
    isJumping = 0;           // Initialize as not jumping
    int gameSpeed = 60;      // Increase the speed (lower Sleep time means faster)

    while (1) {
        system("cls");  // Clear screen each frame

        // Check if jumping
        if (isJumping) {
            if (jumpCounter < 5) {  // Reduce jump duration for faster jumping
                Dino(dinoYPosition - jumpHeight);  // Move the dinosaur up
                jumpCounter++;  // Increment jump duration
            } else {
                Dino(dinoYPosition);  // Move the dinosaur back down
                isJumping = 0;        // End the jump
                jumpCounter = 0;      // Reset jump counter
            }
        } else {
            Dino(dinoYPosition);  // Regular dinosaur position if not jumping
        }

        // Move and draw the obstacle
        obstacle(obstacleX);
        obstacleX--;

        if (obstacleX < 0) {
            obstacleX = 50;  // Reset obstacle position when it moves off the screen
            score++;         // Increment score when the obstacle passes
        }

        // Update the scoreboard
        scoreboard();

        Sleep(gameSpeed);  // Control the game speed (lower value means faster)

        // Check if the player pressed the space key for jump
        if (_kbhit()) {
            int key = _getch();
            if (key == 32 && !isJumping) {  // If space is pressed and not already jumping
                isJumping = 1;  // Start jumping
            }
        }

        // Check for collision between dinosaur and obstacle
        checkCollision(dinoYPosition, obstacleX);
    }
}

void checkCollision(int dinoY, int obsX) {
    if (obsX == 10 && dinoY >= 10 && dinoY <= 20) {
        printf("G A M E   O V E R");
        gameOver();
    }
}

void scoreboard() {
    gotoxy(0, 0);
    printf("Score: %d", score);
}

void gameOver() {
    system("cls");
    printf("Game Over! Press Space to restart or E to exit.\n");
    char choice = _getch();
    if (choice == 32) {
        score = 0;  // Reset score
        move();     // Restart the game
    } else if (choice == 'e' || choice == 'E') {
        exit(0);
    }
}
