// Code made by Mateus Azor and Willian Almeida

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definitions of structs

struct _product { // The product itself
   int id;
   char name[50];
   float price;
   int stock;
   struct _product *next, *prev;
};
typedef struct _product Product;

typedef struct { // Stores both tips of our product list 
   Product *head;
   Product *tail;
} ProductKeys;

struct _cart { // The list of products that will be bought
   int id;
   int amount;
   struct _product *next, *prev;
};
typedef struct _cart Cart;

// Definitions of functions

int verifyMenuInput(int input){ // Verify if the user input is valid to navigate in main menu
    while(input > 5 || input < 0){ // Loop while the input is invalid
        printf("Input not valid, try again: ");
        scanf("%d", &input);
    }
    return input; // When valid return input
}

// Main program

int main(){

    int switcher = 1; // Variable to switch between menus

    printf("\n                                           _____ _____ \n     /\\                                   / ____/ ____|\n    /  \\   _ __ ___   __ _ _______  _ __ | |   | |     \n   / /\\ \\ | '_ ` _ \\ / _` |_  / _ \\| '_ \\| |   | |     \n  / ____ \\| | | | | | (_| |/ / (_) | | | | |___| |____ \n /_/    \\_\\_| |_| |_|\\__,_/___\\___/|_| |_|\\_____\\_____|\n\n"); // Print the logo

    while(switcher != 0){ // Main loop

        printf("\n1. Register Product\n2. List Products\n3. Search Product\n4. Delete Product\n5. Buy Products\n0. Exit System\n");
        printf("\nType a number between 1 and 5 to navigate or 0 to exit the program: ");
        scanf("%d", &switcher); // Get where the user wanna go
        switcher = verifyMenuInput(switcher);

        switch(switcher){ // Does something according to what the user typed

            case(0): // Exit System
                break; // Exit the main loop making the code end
            
            case(1): // Register Product
                printf("WIP");
                break;

            case(2): // List Products
                printf("WIP");
                break;

            case(3): // Search Product
                printf("WIP");
                break;

            case(4): // Delete Product
                printf("WIP");
                break;

            case(5): // Buy Products
                printf("WIP");
                break;

            default: // If somehow the user bypass the input verification and type a invalid number, end the program
                printf("ERROR - Invalid Main Menu Input");
                break;
        }
    }

    return 0;
}