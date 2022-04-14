// Code made by Mateus Azor and Willian Dal Pont

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definitions of structs

typedef struct _product { // The product itself
   int id;
   char name[50];
   float price;
   int stock;
   char unity[30];
   struct _product *next, *prev;
} Product;

typedef struct { // Stores both tips of our product list 
   Product *head;
   Product *tail;
} ProductKeys;

typedef struct _cart { // The list of products that will be bought
   int id;
   int amount;
   struct _product *next, *prev;
} Cart;

// Definitions of basic functions

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

ProductKeys clearProducts(ProductKeys *listReference){

    Product *helper; // Create an extra pointer
    helper = malloc(sizeof(Product));
    helper = listReference->head; // Set the extra pointer to the first element of the list

    Product *eraser; // Create an extra pointer to free values

    while(helper != NULL){ // Main loop

        eraser = helper;
        helper = helper->next; // Helper aways point to the next value to be erased

        free(eraser); // Free the alocated memory on eraser
    }

    free(helper);

    return *listReference;
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
    printf("\nType the product's UNITY of Measure: ");
    scanf("%s", placeholder->unity);
    placeholder->next = NULL; // Set the pointers to NULL
    placeholder->prev = NULL;

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

    if(listReference->head->next == listReference->tail){ // If the list is empty
        printf("\nNo products have been added!\n");
        return;
    }

    while(helper->next != NULL){ // Print loop
        printf("\nId: %d\nName: %s\nPrice: $%.2f\nStock: %d\nUnity: %s\n", helper->id, helper->name, helper->price, helper->stock, helper->unity);
        helper = helper->next;
    }

    helper = NULL; // Free the alocated memory of the extra pointer
    free(helper);
}

void searchProduct(ProductKeys *listReference)
{
    if (listReference->head->next == listReference->tail) // Checks if the list has at least one product
    {
        printf("\nNo products have been added.\n");
        return;
    }

    Product *aux; // Create a extra pointer
    aux = malloc(sizeof(Product));
    aux = listReference->head->next; // Set the extra pointer to the first element of the list

    int valueID, founded = 0;

    printf("\nType the product id: ");
    scanf("%d", &valueID);
    
    while(aux != NULL) // Seach loop
    {
        if (valueID == aux->id) // Compares if the value of the id entered is equal to the id in the list
        {
            printf("\nProduct found.\n\n");
            printf("Name: %s\nPrice: $%.2f\nAmount: %d %s\n", aux->name, aux->price, aux->stock, aux->unity);
            founded = 1;
            break;
        }

        aux = aux->next;
    }

    if(founded == 0){
        printf("\nProduct not found.\n");
    }

    aux = NULL; // Free the alocated memory of the extra pointer (aux)
    free(aux);
}

ProductKeys deleteProduct(ProductKeys *listReference){

    if(listReference->head->next == listReference->tail){
        printf("\nNo products have been added!\n");
        return *listReference;
    }

    int productId, founded = 0;

    printf("\nType the product id: "); // Get te id to be deleted
    scanf("%d", &productId);

    Product *helper; // Create an extra pointer
    helper = malloc(sizeof(Product));
    helper = listReference->head->next; // Set the extra pointer to the first element of the list

    while(helper->next != NULL){ // Main loop

        if(helper->id == productId){ // If the product is found

            Product *helperPrev; // Create another extra pointer
            helperPrev = malloc(sizeof(Product));
            helperPrev = helper->prev; // Set the extra pointer to the previous element of helper

            Product *helperNext; // Create another extra pointer
            helperNext = malloc(sizeof(Product));
            helperNext = helper->next; // Set the extra pointer to the next element of helper

            helperPrev->next = helperNext; // Make the previous element point to next and vice versa
            helperNext->prev = helperPrev;

            free(helper); // Free the alocated memory on helper

            printf("\nThe product has been deleted.\n");

            helperPrev = NULL; // Free alocated memory on rthe extra pointers
            helperNext = NULL;
            free(helperPrev);
            free(helperNext);

            founded = 1;
            break;
        }

        helper = helper->next;
    }

    if(founded == 0){
        printf("\nProduct not found.\n");
    }

    return *listReference;
}

// Definitions of cart functions

ProductKeys cart(ProductKeys *listReference){

    int switcher = 1; // Variable to switch between menus

    printf("\n\n  /$$$$$$                        /$$    \n /$$__  $$                      | $$    \n| $$  \\__/  /$$$$$$   /$$$$$$  /$$$$$$  \n| $$       |____  $$ /$$__  $$|_  $$_/  \n| $$        /$$$$$$$| $$  \\__/  | $$    \n| $$    $$ /$$__  $$| $$        | $$ /$$\n|  $$$$$$/|  $$$$$$$| $$        |  $$$$/\n \\______/  \\_______/|__/         \\___/  \n\n");

    while(switcher != 0){ // Main loop

        printf("\n1. Choose Products\n2. Check Cart\n3. Remove Product\n4. Checkout\n0. Cancel Purchase\n");
        printf("\nType a number between 1 and 4 to navigate or 0 to cancel purchase: ");
        scanf("%d", &switcher); // Get where the user wanna go
        switcher = verifyCartInput(switcher);

        switch(switcher){ // Does something according to what the user typed

            case(0): ; // Cancel Purchase

                printf("\nPurchase Being Canceled...\n");

                // free();

                return *listReference;
            
            case(1): ; // Choose Products

                printf("WIP");
                break;

            case(2): ; // Check Cart
                
                printf("WIP");
                break;

            case(3): ; // Remove Product
                
                printf("WIP");
                break;

            case(4): ; // Checkout
                
                printf("WIP");
                break;

            default: ; // If somehow the user bypass the input verification and type a invalid number, end the program
                printf("ERROR - Invalid Main Menu Input");
                break;
        }
    }
}

int verifyCartInput(int input){ // Verify if the user input is valid to navigate in cart menu

    while(input > 4 || input < 0){ // Loop while the input is invalid
        printf("Input not valid, try again: ");
        scanf("%d", &input);
    }

    return input; // When valid return input
}

// Main program

int main(){

    int switcher = 1; // Variable to switch between menus

    ProductKeys *listReference; // Create the struct that stores the head and tail of the products list
    listReference = malloc(sizeof(ProductKeys));
    listReference->head = malloc(sizeof(Product));
    listReference->tail = malloc(sizeof(Product));
    listReference->head->prev = NULL; // Configure head
    listReference->head->next = listReference->tail;
    listReference->tail->next = NULL; // Configure tail
    listReference->tail->prev = listReference->head;

    printf("\n                                           _____ _____ \n     /\\                                   / ____/ ____|\n    /  \\   _ __ ___   __ _ _______  _ __ | |   | |     \n   / /\\ \\ | '_ ` _ \\ / _` |_  / _ \\| '_ \\| |   | |     \n  / ____ \\| | | | | | (_| |/ / (_) | | | | |___| |____ \n /_/    \\_\\_| |_| |_|\\__,_/___\\___/|_| |_|\\_____\\_____|\n\n"); // Print the logo

    while(switcher != 0){ // Main loop

        printf("\n1. Register Product\n2. List Products\n3. Search Product\n4. Delete Product\n5. Buy Products\n0. Exit System\n");
        printf("\nType a number between 1 and 5 to navigate or 0 to exit the program: ");
        scanf("%d", &switcher); // Get where the user wanna go
        switcher = verifyMenuInput(switcher);

        switch(switcher){ // Does something according to what the user typed

            case(0): ; // Exit System

                printf("\nExiting...\n\n");
                
                *listReference = clearProducts(listReference); // Free the products list
                free(listReference->head);
                free(listReference->tail);
                free(listReference);

                exit(0); // Exit the code
            
            case(1): ; // Register Product

                registerProduct(listReference);
                break;

            case(2): ; // List Products
                
                listProducts(listReference);
                break;

            case(3): ; // Search Product

                searchProduct(listReference);
                break;

            case(4): ; // Delete Product

                *listReference = deleteProduct(listReference);
                break;

            case(5): ; // Buy Products

                *listReference = cart(listReference);
                break;

            default: ; // If somehow the user bypass the input verification and type a invalid number, end the program

                printf("ERROR - Invalid Main Menu Input");
                break;
        }
    }

    printf("\nExiting...\n\n");

    return 0;
}