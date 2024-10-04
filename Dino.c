#include <conio.h> 
#include <stdio.h> 
#include <time.h> 
#include <windows.h> 


void displayMenu();
void Dino();
void move();


int main(){

    //Code page 437 supports ASCII characters.
    system("chcp 437 > nul");  //Sets code page to 437 (OEM US)


    displayMenu();




    return 0;

   
}

void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void displayMenu(){
    system("cls");  //Clear the screen

    int choice = 0;   //0 = New Game, 1 = About, 2 = Exit
    while(1){
        // Display the menu options
        printf(choice == 0 ? ">>New Game\n" : "  New Game\n");
        printf(choice == 1 ? ">>About\n" : "  About\n");
        printf(choice == 2 ? ">>Exit\n" : "  Exit\n");

        // Key press
        int key = _getch();  // _getch() to capture key input
        if(key == 224){      // Special key detected
            key = _getch();  // Get actual key code (arrow keys)
            switch(key){
                case 72:  // Up arrow key
                    choice = choice - 1;
                    if(choice < 0){
                        choice = 2;  // Wrap around to last item
                    }
                    break;  // Break to prevent fall-through
                case 80:  // Down arrow key
                    choice = choice + 1;
                    if(choice > 2){
                        choice = 0;  // Wrap around to first item
                    }
                    break;  // Break to prevent fall-through
            }
        }
        else if(key == 13){    // Enter Key
            // Perform the action
            if(choice == 0){
                printf("Welcome to the Game...\n");
                move();
            }
            else if(choice == 1){
                printf("This game is created by Thai studio...\n");
            }
            else if(choice == 2){
                printf("Exiting...\n");
                break;
            }
            _getch();  // Pause before returning to menu
        }

        system("cls");  // Clear screen after each key press to update menu
    }
}


void Dino(){

    //Draw the dinosaur
    printf("              ");
    printf("       ▀▀▀▀▀▀▀▀");
    printf("      ▀▀▀▀  ▀▀▀▀▀");
    printf("      ▀▀▀▀▀▀▀▀▀▀▀▀");
    printf("      ▀▀▀▀▀▀▀▀▀▀▀▀");
    printf("      ▀▀▀▀▀▀ ");
    printf("      ▀▀▀▀▀▀ ");
    printf("    ▀▀▀▀▀▀▀▀ ");
    printf("   ▀▀▀▀▀▀▀▀▀ ");
    printf(" ▀▀▀▀▀▀▀▀▀▀▀ ");
    printf("▀▀▀▀▀▀▀▀▀▀▀▀▀");
    printf("  ▀▀▀▀   ▀▀▀  ");
    printf("  ▀▀▀▀   ▀▀▀  ");
    printf("  ▀▀▀▀▀  ▀▀▀▀▀");
}

void move(){
    for(int x = 0; x < 50; x++){
        system("cls");
        gotoxy(x,10);
        Dino();
        Sleep(100);
    }
}