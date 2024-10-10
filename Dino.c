#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

void displayMenu();
void Dino(int dinoY, int frame);  // Updated to accept frame for leg animation
void move();
void obstacle();
void displayObstacle();
void checkCollision();
void scoreboard();
void gameOver();
void drawBackground(int offset);
void drawClouds(int cloudOffset);  // Function to draw clouds

int score = 0;        // Initialize score
int isJumping = 0;    // Flag for jump status
int frameCounter = 0; // Counter for frame-based animations

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
    int choice = 0; // 0 = New Game, 1 = About, 2 = Exit
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
                move();
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

int gameSpeed = 50;   // Speed adjustment for the background
int jumpHeight = 6;  // Control jump height
int jumpCounter = -10; // Control jump duration

// Draw the dinosaur at a given Y position and frame
void Dino(int dinoY, int frame) {
    gotoxy(2, dinoY);
    printf("      ########\n");

    gotoxy(2, dinoY + 1);
    printf("      ####  #####\n");

    gotoxy(2, dinoY + 2);
    printf("      ############\n");

    gotoxy(2, dinoY + 3);
    printf("      ############\n");

    gotoxy(2, dinoY + 4);
    printf("      ###### \n");

    gotoxy(2, dinoY + 5);
    printf("      ###### \n");

    gotoxy(2, dinoY + 6);
    printf("    ######## \n");

    gotoxy(2, dinoY + 7);
    printf("   ######### \n");

    gotoxy(2, dinoY + 8);
    printf(" ########### \n");

    gotoxy(2, dinoY + 9);
    printf("############\n");

    // Alternate leg positions based on frame
    if (frame % 2 == 0) {
        gotoxy(2, dinoY + 10);
        printf("  ####   ###  \n");
        gotoxy(2, dinoY + 11);
        printf("  ####   ###  \n");
        gotoxy(2, dinoY + 12);
        printf("  #####  ####\n");
    } else {
        gotoxy(2, dinoY + 10);
        printf(" ####   ###  \n");
        gotoxy(2, dinoY + 11);
        printf(" ####   ###  \n");
        gotoxy(2, dinoY + 12);
        printf(" #####  ####\n");
    }
}
int currentDinoYPosition = 0;
int obstacleY = 0;

void move() {
    int dinoYPosition = 15;   // Base Y position of the dinosaur (ground level)
    int obstacleX = 50;       // Initial position of the obstacle
    obstacleY = 26;       // Fixed Y position for the obstacle
    int backgroundOffset = 0; // Background scrolling offset
    int cloudOffset = 0;      // Cloud scrolling offset
    currentDinoYPosition = dinoYPosition; // Variable to track current Dino Y position during jump

    while (1) {
        system("cls");  // Clear screen each frame

        // Handle dinosaur jump
        if (isJumping) {
            if (jumpCounter < 3) {  // Control jump duration
                currentDinoYPosition = dinoYPosition - jumpHeight;  // Move the dinosaur up
                jumpCounter++;  // Increment jump duration
            } else {
                currentDinoYPosition = dinoYPosition;  // Move the dinosaur back down
                isJumping = 0;  // End the jump
                jumpCounter = -10;  // Reset jump counter
            }
        } else {
            currentDinoYPosition = dinoYPosition;  // Regular dinosaur position if not jumping
        }


        // Display the dinosaur with updated Y position
        Dino(currentDinoYPosition, frameCounter);  // Update frameCounter for leg animation

        // Move and draw the obstacle
        displayObstacle(obstacleX);
        obstacleX -= 2;

        if (obstacleX < 0) {
            obstacleX = 50;  // Reset obstacle position
            score++;         // Increment score when the obstacle passes

            // Increase difficulty as score increases
            if (score % 5 == 0 && gameSpeed > 10) {  // Every 5 points, speed up (until a minimum speed)
                gameSpeed -= 5;  // Increase the speed by decreasing the sleep time
            }
        }

        // Move the background (scroll effect)
        drawBackground(backgroundOffset);
        backgroundOffset = (backgroundOffset + 1) % 6;  // Scroll the background

        // Move the background (scroll effect)
        drawClouds(cloudOffset);
        cloudOffset = (cloudOffset + 1) % 60;  // Scroll clouds

        // Update the scoreboard
        scoreboard();

        Sleep(gameSpeed);  // Control the game speed

        // Check if the player pressed the space key for jump
        if (_kbhit()) {
            int key = _getch();
            if (key == 32 && !isJumping) {  // If space is pressed and not already jumping
                isJumping = 1;  // Start jumping
            }
        }

        // Check for collision between dinosaur and obstacle
        checkCollision(currentDinoYPosition, obstacleX, obstacleY);  // Pass obstacleY as well

        // Increment the frame counter for leg animation
        frameCounter++;
    }
}


void displayObstacle(int obsX) {
    gotoxy(obsX, 26);  // Set position for the obstacle
    printf("   ###   \n");
    gotoxy(obsX, 27);  
    printf("   ###   \n");
}

void drawBackground(int offset) {
    gotoxy(0, 29);
    for (int i = 0; i < 500; i++) {
        if ((i + offset) % 5 == 0) {
            printf("_");  // Draw ground segment
        } else {
            printf(" ");
        }
    }
    printf("\n");
}

void drawClouds(int offset) {
    // Fix the Y position to stay constant (for example, at row 2)
    int cloudYPosition = 5;

    // Loop through the horizontal space for clouds (e.g., draw a cloud every 10 characters)
    for (int i = 0; i < 500; i++) {
        if ((i + offset) % 40 == 0) {  // Clouds spaced every 20 characters
            gotoxy(i+5, cloudYPosition);  // Set cloud's X position, keeping Y constant
            printf("  @@@@");
            gotoxy(i+5, cloudYPosition + 1);
            printf(" @@@@@@");
        }
    }
}



void checkCollision(int currentDinoYPosition, int obstacleX, int obstacleY) {
    // Check if the obstacle is close to the dinosaur horizontally
    if ((obstacleX >= 5 && obstacleX <= 10) || (obstacleX >= 1 && obstacleX <= 4)) {  // Assuming the dinosaur occupies X range 5 to 15
        // Check if the dinosaur's Y position equals the obstacle's Y position
        if (currentDinoYPosition + 11 >= obstacleY && currentDinoYPosition + 12 <= obstacleY + 1) {
            printf("G A M E   O V E R\n");
            gameOver();
        }
    }
}



void scoreboard() {
    gotoxy(0, 0);
    printf("Score: %d", score);
    gotoxy(0, 1);
    printf("Dino Y: %d", currentDinoYPosition);
    gotoxy(0,2);
    printf("ObstacleY: %d", obstacleY);
}

void gameOver() {
    system("cls");
    printf("Game Over! Press Space to restart or E to exit.\n");
    char choice = _getch();
    if (choice == 32) {
        score = 0;  // Reset score
        gameSpeed = 80;  // Reset speed
        move();
    } else if (choice == 'e' || choice == 'E') {
        exit(0);
    }
}
