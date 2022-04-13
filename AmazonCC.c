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

int verifyId(int id, ProductKeys *listReference){ 

    int alreadyExist, loop = 1; // Declaration of extra variables

    if(listReference->head->next == NULL){ // If there is no elements in the list
        return id; // Stop the function now
    }

    Product *helper; // Create an extra pointer
    helper = malloc(sizeof(Product)); 

    while(loop == 1){ // Main loop

        helper = listReference->head->next; // Set it to point to the first element of the list

        while(helper->next != NULL){ // Loop to verify all products of the list
            if(helper->id == id){
                alreadyExist = 1;
                break;
            }
            helper = helper->next;
        }

        if(alreadyExist == 1){ // If id already exists
            printf("ID already exist, please type another: ");
            scanf("%d", &id); // Get another
        }else{
            loop = 0; // Break the main loop
        }

        alreadyExist = 0;
    }

    helper = NULL; // Free the alocated memory of the extra pointer
    free(helper);
    
    return id;
}

void registerProduct(ProductKeys *listReference){
    
    Product *placeholder; // Create the product
    placeholder = malloc(sizeof(Product));
    printf("\nType the ID of the Product: "); // Scan and storage values on new product
    scanf("%d", &placeholder->id);
    placeholder->id = verifyId(placeholder->id, listReference); // Verify if the id is valid
    printf("\nType the NAME of the Product: ");
    scanf("%s", placeholder->name);
    printf("\nType the PRICE of the Product: ");
    scanf("%f", &placeholder->price);
    printf("\nType the STOCK of the Product: ");
    scanf("%d", &placeholder->stock);
    placeholder->next = NULL; // Set the pointers to NULL
    placeholder->prev = NULL;

    if(listReference->head->next == NULL){ // If the list is empty

        listReference->head->next = placeholder; // Make head and tail point to the new element
        listReference->tail->prev = placeholder;
        placeholder->prev = listReference->head; // Make the new element point to head and tail
        placeholder->next = listReference->tail;
    }

    Product *helper; // Create an extra pointer
    helper = malloc(sizeof(Product));
    helper = listReference->tail->prev; // Set the extra pointer to the last element of the list

    helper->next = placeholder; // Make the tail and the last element point to the new
    listReference->tail->prev = placeholder; // (if the list is empty, the "last element" will be the head)
    placeholder->prev = helper; // And the new element point to both
    placeholder->next = listReference->tail;
 
    helper = NULL; // Free the alocated memory of the extra pointer
    free(helper);
}

void listProducts(ProductKeys *listReference){

    Product *helper; // Create an extra pointer
    helper = malloc(sizeof(Product));
    helper = listReference->head->next; // Set the extra pointer to the first element of the list

    while(helper->next != NULL){
        printf("\nId: %d\nName: %s\nPrice: %.2f\nStock: %d\n", helper->id, helper->name, helper->price, helper->stock);
        helper = helper->next;
    }

    helper = NULL; // Free the alocated memory of the extra pointer
    free(helper);
}

// Main program

int main(){

    int switcher = 1; // Variable to switch between menus

    ProductKeys *listReference; // Create the struct that stores the head and tail of the products list
    listReference = malloc(sizeof(ProductKeys));
    listReference->head = malloc(sizeof(Product));
    listReference->head->next = NULL; // Configure head
    listReference->head->prev = NULL;
    listReference->tail = malloc(sizeof(Product));
    listReference->tail->next = NULL; // Configure tail
    listReference->tail->prev = NULL;

    printf("\n                                           _____ _____ \n     /\\                                   / ____/ ____|\n    /  \\   _ __ ___   __ _ _______  _ __ | |   | |     \n   / /\\ \\ | '_ ` _ \\ / _` |_  / _ \\| '_ \\| |   | |     \n  / ____ \\| | | | | | (_| |/ / (_) | | | | |___| |____ \n /_/    \\_\\_| |_| |_|\\__,_/___\\___/|_| |_|\\_____\\_____|\n\n"); // Print the logo

    while(switcher != 0){ // Main loop

        printf("\n1. Register Product\n2. List Products\n3. Search Product\n4. Delete Product\n5. Buy Products\n0. Exit System\n");
        printf("\nType a number between 1 and 5 to navigate or 0 to exit the program: ");
        scanf("%d", &switcher); // Get where the user wanna go
        switcher = verifyMenuInput(switcher);

        switch(switcher){ // Does something according to what the user typed

            case(0): ; // Exit System

                printf("\nExiting...\n\n");
                exit(0); // Exit the code
            
            case(1): ; // Register Product

                registerProduct(listReference);
                break;

            case(2): ; // List Products
                
                listProducts(listReference);
                break;

            case(3): ; // Search Product
                printf("WIP");
                break;

            case(4): ; // Delete Product
                printf("WIP");
                break;

            case(5): ; // Buy Products
                printf("WIP");
                break;

            default: ; // If somehow the user bypass the input verification and type a invalid number, end the program
                printf("ERROR - Invalid Main Menu Input");
                break;
        }
    }

    printf("\nExiting...\n\n");

    return 0;
}