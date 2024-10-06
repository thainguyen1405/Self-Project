#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>


void displayMenu();
void Dino();
void move();
void obstacle();
void checkCollision(int dinoX, int dinoY, int obsX, int obsY);
void jump();
void scoreboard();
void gameOver();
void background();
void Difficulty();




void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
    // Code page 437 supports ASCII characters.
    system("chcp 437 > nul");  // Sets code page to 437 (OEM US)



    displayMenu();

    return 0;
}


void displayMenu() {
    system("cls");  // Clear the screen

    int choice = 0;   // 0 = New Game, 1 = About, 2 = Exit
    while (1) {
        // Display the menu options
        printf(choice == 0 ? ">>New Game\n" : "  New Game\n");
        printf(choice == 1 ? ">>About\n" : "  About\n");
        printf(choice == 2 ? ">>Exit\n" : "  Exit\n");

        // Key press
        int key = _getch();  // _getch() to capture key input
        if (key == 224) {    // Special key detected
            key = _getch();  // Get actual key code (arrow keys)
            switch (key) {
                case 72:  // Up arrow key
                    choice = choice - 1;
                    if (choice < 0) {
                        choice = 2;  // Wrap around to last item
                    }
                    break;  // Break to prevent fall-through
                case 80:  // Down arrow key
                    choice = choice + 1;
                    if (choice > 2) {
                        choice = 0;  // Wrap around to first item
                    }
                    break;  // Break to prevent fall-through
            }
        } else if (key == 13) {  // Enter Key
            // Perform the action
            if (choice == 0) {
                printf("Welcome to the Game...\n");
                move();
            } else if (choice == 1) {
                printf("This game is created by Thai studio...\n");
            } else if (choice == 2) {
                printf("Exiting...\n");
                break;
            }
            _getch();  // Pause before returning to menu
        } else if (key == 32) {  // Space key for jump
            jump();
        }

        system("cls");  // Clear screen after each key press to update menu
    }
}

void Dino() {
    // Draw the dinosaur
    printf("              \n");
    printf("      ########\n");
    printf("      ####  #####\n");
    printf("      ############\n");
    printf("      ############\n");
    printf("      ###### \n");
    printf("      ###### \n");
    printf("    ######## \n");
    printf("   ######### \n");
    printf(" ########### \n");
    printf("############\n");
    printf("  ####   ###  \n");
    printf("  ####   ###  \n");
    printf("  #####  ####\n");
}

void obstacle() {
    // Draw the obstacle (e.g., cactus)
    printf("   ##    \n");
    printf("   ##    \n");
    printf(" ######  \n");
    printf("  ####  \n");
    printf("   ##    \n");
    printf("   ##    \n");
}

void move(){
    for(int x = 50; x >= 0; x--){
        system("cls");
        gotoxy(10,10);
        Dino();
        gotoxy(x,10);
        obstacle();
        scoreboard();
        checkCollision(10,10,x,10);
        Sleep(100);
    }
}

void jump() {
    // Simulate a jump by moving the dinosaur up and down
    gotoxy(5, 5);  // Move up (jump)
    Dino();
    Sleep(300);    // Hold the jump position for a while
    gotoxy(5, 10);  // Move back down
    Dino();
}


//Check if there's collision 
void checkCollision(int dinoX, int dinoY, int obsX, int obsY){
    if(dinoX == obsX && dinoY == obsY){
        printf("G A M E   O V E R");
        gameOver();
    }
}

int score = 0; 

void scoreboard(){
    score++;
    gotoxy(0,0);
    printf("Score: %d", score);
    Difficulty();
}

void gameOver(){
    system("cls");
    printf("Space to continue or E to exit.\n");
    char choice = _getch();
    if(choice == 32){
        //Restart the game 
        score = 0;
        main();
    }
    else if(choice == 'e' || choice == 'E'){
        exit(0);
    }
}

void background(){
    gotoxy(0,15);
    printf("____________________");
}

void Difficulty(){
    if(score > 20){
        Sleep(20);
    }
}

