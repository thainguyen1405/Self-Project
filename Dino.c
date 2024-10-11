#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>


void displayMenu();  //Game menu

void Dino(int dinoY, int frame);  //Draw Dino and movement

void Obstacle();  //Draw the obsttacle 

void FinishLine(int LineX);  //Finish the game

void drawBackground(int offset);  //Draw the ground line

void drawClouds(int cloudOffset);  // Add clouds for visual

void gameplay();  //Display the game

void checkCollision();  //Check the collision between Dino & Obstacle

void scoreboard();  //Display player score

void resetGame();  //Game Over



//Global declartion for full access
int score = 0;        // Initialize score
int isJumping = 0;    // Flag for jump status
int frameCounter = 0; // Counter for frame-based animations


//Draw xy coordinate
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


int main() {
    system("chcp 437 > nul");  // Sets code page to 437 (OEM US)
    
    //Random generator
    srand(time(0)); 

    //Display the game
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

        int key = _getch();  //Capture the key press
        if (key == 224) {    //Idicate the special key being press
            key = _getch();
            switch (key) {
                case 72:  //Up arrow key
                    choice = choice - 1;
                    if (choice < 0) choice = 2;
                    break;
                case 80:  //Down arrow key
                    choice = choice + 1;
                    if (choice > 2) choice = 0;
                    break;
            }
        } else if (key == 13) {  //Enter Key press
            if (choice == 0) {  //New Game
                printf("Welcome to the Game...\n");
                score = 0;   //Reset score
                gameplay();  //Get to the game
            } else if (choice == 1) {  //About
                printf("This game is inspired by the Google Dinosaur Game. It was developed over 16 days, from September 26 to October 11, and includes a finish line feature. Enjoy playing!\n");
            } else if (choice == 2) {  //Exit
                printf("Exiting...\n");
                break;
            }
            _getch();  //Pause before returning to menu
        }
        system("cls");  //Clear screen after each key press to update menu
    }
}

//These variable for gameplay
int gameSpeed = 30;     //Default game speed
int jumpHeight = 6;     //Dino's jump height
int jumpCounter = -10;  //Control jump duration
int obstacleType = 0;   //Indicate random obstacle

//These variables for collision
int currentDinoYPosition = 0;
int obstacleY = 0;

//Draw the dinosaur at a given Y position and frame
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

    // Dino running leg
    if (frame % 2 == 0) {
        gotoxy(2, dinoY + 10);
        printf("  ####   ###  \n");
        gotoxy(2, dinoY + 11);
        printf("  ####   ###  \n");
        gotoxy(2, dinoY + 12);
        printf("  #####  ####\n");
    } else {
        gotoxy(2, dinoY + 11);
        printf(" ####   ###  \n");
        gotoxy(2, dinoY + 12);
        printf(" ####   ###  \n");
        gotoxy(2, dinoY + 13);
        printf(" #####  ####\n");
    }
}


//Draw and random the obstacle
void Obstacle(int obsX, int type) {
    switch(type) {
        case 0:
          gotoxy(obsX, 26);  //Set the default position
          printf("     ###   \n");
          gotoxy(obsX, 27);  
          printf("   #######   \n");
          gotoxy(obsX, 28);
          printf("    #   #   \n");
          break;
        case 1:
          gotoxy(obsX, 26); 
          printf("   # #   \n");
          gotoxy(obsX, 27); 
          printf(" #######   \n");
          gotoxy(obsX, 28);  
          printf("   ###   \n");
          gotoxy(obsX, 29);
          printf("   # #     \n");
          break;
        case 2:
          gotoxy(obsX, 26);
          printf("    #    \n");
          gotoxy(obsX, 27); 
          printf("   ###   \n");
          gotoxy(obsX, 28);  
          printf("   ###   \n");
          gotoxy(obsX, 29);
          printf("    #    \n");
          break;
    }
}

void FinishLine(int LineX) {
    int finishY = 27;  // Align the finish line on the ground
    gotoxy(LineX, finishY - 3); 
    printf(" #*#*#*#*#*   \n");
    gotoxy(LineX, finishY - 2); 
    printf(" *#*#*#*#*#   \n");
    gotoxy(LineX, finishY - 1); 
    printf(" #*#*#*#*#*   \n");
    gotoxy(LineX, finishY);  
    printf(" ##           \n");
    gotoxy(LineX, finishY + 1);
    printf(" ##           \n");
}


void gameplay() {
    int dinoYPosition = 15;   // Dino Y position
    int obstacleX = 150;      // Obstacle X position
    obstacleY = 26;           // Obstacle Y position
    int backgroundOffset = 0; // Background scrolling offset
    int cloudOffset = 0;      // Cloud scrolling offset
    int finishLineX = 100;    // Position for the finish line
    currentDinoYPosition = dinoYPosition; // Set Dino current to Y position

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
            currentDinoYPosition = dinoYPosition;  // Regular dinosaur position
        }

        // Update Y position & frame counter for leg animation 
        Dino(currentDinoYPosition, frameCounter);

        // Move and draw the obstacle or the finish line based on game speed
        if (gameSpeed > 3) {  // Continue displaying obstacles if game speed > 9
            Obstacle(obstacleX, obstacleType);
            obstacleX -= 2;

            if (obstacleX < 0) {
                obstacleX = (rand() % 30) + 70;  // Randomize the range to 100
                score++;  // Increment score when the obstacle passes

                obstacleType = rand() % 3;  // Randomize 3 types of Obstacle

                // Increase Difficulty 
                if (score % 3 == 0) {  // Every 3 points, speed up
                    gameSpeed -= 5;  // Increase the speed by decreasing the sleep time
                }
            }
        } else {  // Display the finish flag when game speed <= 3
            FinishLine(finishLineX);
            finishLineX -= 2;  // Move the finish line toward the dinosaur

            // Check if the dinosaur has reached the finish line
            if (finishLineX <= 10) {
                Sleep(2000);  // Pause for 2 seconds to show the finish line
                system("cls");

                //Display the congratulation message
                int screenWidth = 240;  // Set screen width
                int screenHeight = 40;  // Set screen height
                
                //Positions for horizontal and vertical centering
                int centerX = (screenWidth - strlen("Congratulation you won!")) / 2;
                int centerY = screenHeight / 2 - 1;  // Slightly above the middle
                
                // Position the first line
                gotoxy(centerX, centerY); 
                printf("Congratulation you won!");
                
                // Position the second line
                centerX = (screenWidth - strlen("This game is created by Thai studio...")) / 2;
                gotoxy(centerX, centerY + 1); 
                printf("This game is created by Thai studio...");
                Sleep(3000);
                resetGame();  //Reset the game: restart/exit
                break;
            }
        }

        // Move the background (scroll effect)
        drawBackground(backgroundOffset);
        backgroundOffset = (backgroundOffset + 1) % 6;  // Scroll the background

        // Move the clouds (scroll effect)
        drawClouds(cloudOffset);
        cloudOffset = (cloudOffset + 1) % 60;  // Scroll clouds

        // Update the scoreboard
        scoreboard();

        Sleep(gameSpeed);  // Control the game speed

        // Condition "space" key for jumping
        if (_kbhit()) {
            int key = _getch();
            if (key == 32 && !isJumping) {  // If space is pressed and not already jumping
                isJumping = 1;  // Start jumping
            }
        }

        // Check for collision between dinosaur and obstacle
        checkCollision(currentDinoYPosition, obstacleX, obstacleY);

        // Increment the frame counter for leg animation
        frameCounter++;
    }
}



    
void drawBackground(int offset) {
    gotoxy(0, 29);
    for (int i = 0; i < 200; i++) {
        if ((i + offset) % 1 == 0) {
            printf("_");  // Draw the ground
        } else {
            printf(" ");
        }
    }
    printf("\n");
}

void drawClouds(int offset) {
    //Default the cloud position
    int cloudYPosition = 5;

    // Loop through the horizontal space for clouds
    for (int i = 0; i < 200; i++) {
        if ((i + offset) % 60 == 0) {  // Clouds spaced every 60 characters
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
            // Display the GAME OVER message
                Sleep(1000);
                system("cls");
                int screenWidth = 240;  // Set screen width
                int screenHeight = 40;  // Set screen height
                
                // Set positions for horizontal and vertical centering
                int centerX = (screenWidth - strlen("G A M E    O V E R")) / 2;
                int centerY = screenHeight / 2 - 1;  // Slightly above the middle

                gotoxy(centerX, centerY); 
                printf("G A M E    O V E R");
                
                Sleep(2000);
                resetGame();
        }
    }
}


void scoreboard() {
    gotoxy(0, 0);
    printf("Score: %d", score);  //Display player's score
    gotoxy(0, 1);
    printf("Dino Y: %d", currentDinoYPosition);
    gotoxy(0,2);
    printf("ObstacleY: %d", obstacleY);
}

void resetGame() {
    system("cls");
    printf("Press Space to restart or E to exit.\n");
    char choice = _getch();
    if (choice == 32) {
        score = 0;  // Reset score
        gameSpeed = 30;  // Reset speed
        gameplay();
    } else if (choice == 'e' || choice == 'E') {
        exit(0);
    }
}
