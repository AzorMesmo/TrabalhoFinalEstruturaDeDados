// Code made by Mateus Azor and Willian Dal Pont

#include <stdio.h>
#include <stdlib.h>

// Definitions of structs

struct _product {
   int id;
   char name[30];
   float price;
   int stock;
   struct _product *next, *prev;
};
typedef struct _product Product;
 
typedef struct {
   Product *head;
   Product *tail;
} ProductKeys;

struct _cart {
   int id;
   int amount;
   struct _product *next, *prev;
};
typedef struct _cart Cart;

typedef struct { // Stores both tips of our cart list 
   Cart *head;
   Cart *tail;
} CartKeys;

// Definitions of main functions

int verifyMenuInput(int input){ // Verify if the user input is valid to navigate in main menu

    while(input > 5 || input < 0){ // Loop while the input is invalid
        printf("Input not valid, try again: ");
        scanf("%d", &input);
    }

    return input; // When valid return input
}

int verifyId(int id, ProductKeys *productsReference){ 

    int alreadyExist, loop = 1; // Declaration of extra variables

    if(productsReference->head->next == productsReference->tail){ // If there is no elements in the list
        return id; // Stop the function now
    }

    Product *helper; // Create an extra pointer
    helper = malloc(sizeof(Product)); 

    while(loop == 1){ // Main loop

        helper = productsReference->head->next; // Set it to point to the first element of the list

        while(helper->next != NULL){ // Loop to verify all products of the list
            if(helper->id == id){
                alreadyExist = 1;
                break;
            }
            helper = helper->next;
        }

        if(alreadyExist == 1 || id < 0){ // If id already exists
            printf("ID already exist ou it's a negative number, please type another: ");
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

ProductKeys clearProducts(ProductKeys *productsReference){

    Product *helper; // Create an extra pointer
    helper = malloc(sizeof(Product));
    helper = productsReference->head; // Set the extra pointer to the first element of the list of products

    Product *eraser; // Create an extra pointer to free values

    while(helper != NULL){ // Main loop

        eraser = helper;
        helper = helper->next; // Helper aways point to the next value to be erased

        free(eraser); // Free the alocated memory on eraser
    }

    free(helper);

    return *productsReference;
}

void registerProduct(ProductKeys *productsReference){
    
    Product *placeholder; // Create the product
    placeholder = malloc(sizeof(Product));
    printf("\nType the ID of the Product: "); // Scan and storage values on new product
    scanf("%d", &placeholder->id);
    placeholder->id = verifyId(placeholder->id, productsReference); // Verify if the id is valid
    printf("\nType the NAME of the Product: ");
    scanf("%s", placeholder->name);
    printf("\nType the PRICE of the Product: ");
    scanf("%f", &placeholder->price);
    printf("\nType the STOCK of the Product: ");
    scanf("%d", &placeholder->stock);
    placeholder->next = NULL; // Set the pointers to NULL
    placeholder->prev = NULL;

    Product *helper; // Create an extra pointer
    helper = malloc(sizeof(Product));
    helper = productsReference->tail->prev; // Set the extra pointer to the last element of the list of products

    helper->next = placeholder; // Make the tail and the last element point to the new
    productsReference->tail->prev = placeholder; // (if the list is empty, the "last element" will be the head)
    placeholder->prev = helper; // And the new element point to both
    placeholder->next = productsReference->tail;
 
    helper = NULL; // Free the alocated memory of the placeholder and helper
    placeholder = NULL;
    free(helper);
    free(placeholder);
}

void listProducts(ProductKeys *productsReference){

    Product *helper; // Create an extra pointer
    helper = malloc(sizeof(Product));
    helper = productsReference->head->next; // Set the extra pointer to the first element of the list of products

    if(productsReference->head->next == productsReference->tail){ // If the list is empty
        printf("\nNo products have been added!\n");
        return;
    }

    while(helper->next != NULL){ // Print loop
        printf("\nId: %d\nName: %s\nPrice: $%.2f\nStock: %d\n", helper->id, helper->name, helper->price, helper->stock);
        helper = helper->next;
    }

    helper = NULL; // Free the alocated memory of the extra pointer
    free(helper);
}

Product searchProduct(ProductKeys *productsReference){

    Product *helper; // Create a extra pointer
    helper = malloc(sizeof(Product));
    helper = productsReference->head->next; // Set the extra pointer to the first element of the list of products

    if(productsReference->head->next == productsReference->tail){ // Checks if the list has at least one product
        printf("\nNo products have been added.\n");
        return *helper;
    }

    int productId;

    printf("\nType the product id: ");
    scanf("%d", &productId);
    
    while(helper != NULL){ // Seach loop

        if (productId == helper->id){ // Verify if the value of the id entered is equal to the id in the list
            printf("\nProduct found.\n"); // Print the product and exit the loop
            printf("\nName: %s\nPrice: $%.2f\nAmount: %d\n", helper->name, helper->price, helper->stock);
            return *helper;
        }

        helper = helper->next; // Go to the next element
    }

    printf("\nProduct not found.\n");
    helper = productsReference->head->next;
    return *helper;
}

ProductKeys deleteProduct(ProductKeys *productsReference){

    if(productsReference->head->next == productsReference->tail){
        printf("\nNo products have been added!\n");
        return *productsReference;
    }

    int productId, founded = 0;

    printf("\nType the product id: "); // Get te id to be deleted
    scanf("%d", &productId);

    Product *helper; // Create an extra pointer
    helper = malloc(sizeof(Product));
    helper = productsReference->head->next; // Set the extra pointer to the first element of the list of products

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

    return *productsReference;
}

ProductKeys updateProducts(ProductKeys *productsReference, Product *head, Product *helper){

    while(head != NULL){ // Main loop

        helper = productsReference->head->next; // Set the extra pointer to the first element of the old list of products

        while(helper->next != NULL){ // Secundary loop

            if(helper->id == head->id){ // Compare the products, if it's the same
                helper->stock = head->stock; // Update stock
                break;
            }

            helper = helper->next; // Else, go to the next

        }

        head = head->next; // Go to the next updated product
    }

    return *productsReference;

}

// Definitions of cart functions

int verifyCartInput(int input){ // Verify if the user input is valid to navigate in cart menu

    while(input > 4 || input < 0){ // Loop while the input is invalid
        printf("Input not valid, try again: ");
        scanf("%d", &input);
    }

    return input; // When valid return input
}

void chooseProducts(CartKeys *cartReference, ProductKeys *productsReference){

    int amount, loop = 0;

    Product *product; // Create an extra pointer to store the function return below
    product = malloc(sizeof(Product));

    *product = searchProduct(productsReference);

    if(product->id == -1){ // If the product is not found, "break" this function
        return;
    }

    printf("\nType the amount of the product that you wanna buy: ");
    scanf("%d", &amount);

    while(loop == 0){
        if(amount > product->stock){
            printf("This amount is bigger that our stock, please type another value: ");
            scanf("%d", &amount);
        }else{
            break;
        }
    }
    
    Cart *placeholder; // Create a placeholder cart and allocate values in it
    placeholder = malloc(sizeof(Cart));
    placeholder->id = product->id;
    placeholder->amount = amount;

    Cart *helper; // Create an extra pointer 
    helper = malloc(sizeof(Cart));
    helper = cartReference->tail->prev; // Set the extra pointer to the last element of the cart list

    helper->next = placeholder; // Make the tail and the last element point to the new
    cartReference->tail->prev = placeholder; // (if the list is empty, the "last element" will be the head)
    placeholder->prev = helper; // And the new element point to both
    placeholder->next = cartReference->tail;
 
    helper = NULL; // Free the alocated memory of the placeholder, helper and product
    placeholder = NULL;
    product = NULL;
    free(helper);
    free(placeholder);
    free(product);

}

Product searchProductById(ProductKeys *productsReference, int id, int print){ // If print equals to 1, print, else, don't print

    Product *helper; // Create a extra pointer
    helper = malloc(sizeof(Product));
    helper = productsReference->head->next; // Set the extra pointer to the first element of the list of products
    
    while(helper != NULL){ // Seach loop

        if (id == helper->id){ // Verify if the value of the id entered is equal to the id in the list
            if(print == 1){
                printf("\nProduct found.\n"); // Print the product and exit the loop
                printf("\nName: %s\nPrice: $%.2f\nAmount: %d\n", helper->name, helper->price, helper->stock);
            }
            return *helper;
        }

        helper = helper->next; // Go to the next element
    }

    printf("\nProduct not found.\n");
    helper = productsReference->head->next;
    helper->id = -1;
    return *helper;
}

void calculateTotalPrice(CartKeys *cartReference, ProductKeys *productsReference){
    
    float total = 0;

    Cart *helper; // Create an extra pointer
    helper = malloc(sizeof(Cart));
    helper = cartReference->head->next; // Set the extra pointer to the first element of the cart list

    Product *product; // Create an extra product
    product = malloc(sizeof(Product));

    while(helper->next != NULL){ // Main loop

        *product = searchProductById(productsReference, helper->id, 1); // Stores the product
        total = total + (product->price * helper->amount); // Calculate total
        
        helper = helper->next;
    }

    printf("\nThe cart total price it's $%.2f\n", total);

    helper = NULL; // Free the alocated memory of the extra pointer
    free(helper);

}

void checkCart(CartKeys *cartReference){

    Cart *helper; // Create an extra pointer
    helper = malloc(sizeof(Cart));
    helper = cartReference->head->next; // Set the extra pointer to the first element of the cart list

    if(cartReference->head->next == cartReference->tail){ // If the list is empty
        printf("\nNo products have been added on cart!\n");
        return;
    }

    while(helper->next != NULL){ // Print loop
        printf("\nId: %d\nAmount: %d\n", helper->id, helper->amount);
        helper = helper->next;
    }

    helper = NULL; // Free the alocated memory of the extra pointer
    free(helper);

}

CartKeys clearCart(CartKeys *cartReference){

    Cart *helper; // Create an extra pointer
    helper = malloc(sizeof(Cart));
    helper = cartReference->head; // Set the extra pointer to the first element of the list of products

    Cart *eraser; // Create an extra pointer to free values

    while(helper != NULL){ // Main loop

        eraser = helper;
        helper = helper->next; // Helper aways point to the next value to be erased

        free(eraser); // Free the alocated memory on eraser
    }

    free(helper);

    return *cartReference;
}

CartKeys removeCartProduct(CartKeys *cartReference){

    if(cartReference->head->next == cartReference->tail){
        printf("\nNo products have been added on your cart!\n");
        return *cartReference;
    }

    int productId, founded = 0;

    printf("\nType the product id: "); // Get te id to be deleted
    scanf("%d", &productId);

    Cart *helper; // Create an extra pointer
    helper = malloc(sizeof(Cart));
    helper = cartReference->head->next; // Set the extra pointer to the first element of the list of products

    while(helper->next != NULL){ // Main loop

        if(helper->id == productId){ // If the product is found

            Cart *helperPrev; // Create another extra pointer
            helperPrev = malloc(sizeof(Cart));
            helperPrev = helper->prev; // Set the extra pointer to the previous element of helper

            Cart *helperNext; // Create another extra pointer
            helperNext = malloc(sizeof(Cart));
            helperNext = helper->next; // Set the extra pointer to the next element of helper

            helperPrev->next = helperNext; // Make the previous element point to next and vice versa
            helperNext->prev = helperPrev;

            free(helper); // Free the alocated memory on helper

            printf("\nThe product has been removed.\n");

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

    return *cartReference;

}

Product checkout(CartKeys *cartReference, ProductKeys *productsReference){

    int first = 1;

    Cart *cartHelper; // Create an extra cart pointer
    cartHelper = malloc(sizeof(Cart));
    cartHelper = cartReference->head->next; // Set the extra pointer to the first element of the cart list

    Product *productHelper; // Create an extra product pointer
    productHelper = malloc(sizeof(Product));
    productHelper = productsReference->head;

    Product *productPlaceholder; // Create another extra product pointer
    productPlaceholder = malloc(sizeof(Product));

    Product *productHead; // Create another extra product pointer to store the "head" of the list
    productHead = malloc(sizeof(Product));

    while(cartHelper->next != NULL){ // Main loop

        *productHelper = searchProductById(productsReference, cartHelper->id, 0); // Search the product
        productHelper->stock = productHelper->stock - cartHelper->amount; // Reduce the stock

        productPlaceholder = productHelper; // Stores the new product informations in placeholder

        if(first == 1){ // If is the first element
            productHead = productPlaceholder; // Make the start of a pile
            productPlaceholder->next = NULL;
            first = 0;
        }else{
            productPlaceholder->next = productHead; // Continue the pile
            productHead = productPlaceholder;
        }
        
        cartHelper = cartHelper->next; // Go to the next
    }

    return *productHead; // Return the pile
    
}

Product goToCart(ProductKeys *productsReference){ // Main cart function

    int switcher = 1; // Variable to switch between menus

    CartKeys *cartReference; // Create the struct that stores the head and tail of the products list
    cartReference = malloc(sizeof(CartKeys));
    cartReference->head = malloc(sizeof(Cart));
    cartReference->tail = malloc(sizeof(Cart));
    cartReference->head->prev = NULL; // Configure head
    cartReference->head->next = cartReference->tail;
    cartReference->tail->next = NULL; // Configure tail
    cartReference->tail->prev = cartReference->head;

    printf("\n\n  /$$$$$$                        /$$    \n /$$__  $$                      | $$    \n| $$  \\__/  /$$$$$$   /$$$$$$  /$$$$$$  \n| $$       |____  $$ /$$__  $$|_  $$_/  \n| $$        /$$$$$$$| $$  \\__/  | $$    \n| $$    $$ /$$__  $$| $$        | $$ /$$\n|  $$$$$$/|  $$$$$$$| $$        |  $$$$/\n \\______/  \\_______/|__/         \\___/  \n\n");

    while(switcher != 0){ // Main loop

        printf("\n1. Choose Products\n2. Check Cart\n3. Remove Product\n4. Checkout\n0. Cancel Purchase\n");
        printf("\nType a number between 1 and 4 to navigate or 0 to cancel purchase: ");
        scanf("%d", &switcher); // Get user selection
        switcher = verifyCartInput(switcher);

        switch(switcher){ // Go to user chosen option

            case(0): ; // Cancel Purchase

                printf("\nPurchase Being Canceled...\n");
                
                *cartReference = clearCart(cartReference); // Free the products list
                free(cartReference);

                return;
            
            case(1): ; // Choose Products

                chooseProducts(cartReference, productsReference);
                calculateTotalPrice(cartReference, productsReference);
                
                break;

            case(2): ; // Check Cart
                
                checkCart(cartReference);
                
                break;

            case(3): ; // Remove Product
                
                *cartReference = removeCartProduct(cartReference);
                
                break;

            case(4): ; // Checkout

                Product *head; // Create a extra product pointer
                head = malloc(sizeof(Product));
                
                calculateTotalPrice(cartReference, productsReference); // Show the price
                *head = checkout(cartReference, productsReference); // Store the updated product pile
                
                return *head;

            default: ; // If somehow the user bypass the input verification and type a invalid number, end the program

                printf("ERROR - Invalid Main Menu Input");
                
                return;
        }
    }
}

// Main program

int main(){

    int switcher = 1; // Variable to switch between menus

    ProductKeys *productsReference; // Create the struct that stores the head and tail of the products list
    productsReference = malloc(sizeof(ProductKeys));
    productsReference->head = malloc(sizeof(Product));
    productsReference->tail = malloc(sizeof(Product));
    productsReference->head->prev = NULL; // Configure head
    productsReference->head->next = productsReference->tail;
    productsReference->tail->next = NULL; // Configure tail
    productsReference->tail->prev = productsReference->head;

    printf("\n                                           _____ _____ \n     /\\                                   / ____/ ____|\n    /  \\   _ __ ___   __ _ _______  _ __ | |   | |     \n   / /\\ \\ | '_ ` _ \\ / _` |_  / _ \\| '_ \\| |   | |     \n  / ____ \\| | | | | | (_| |/ / (_) | | | | |___| |____ \n /_/    \\_\\_| |_| |_|\\__,_/___\\___/|_| |_|\\_____\\_____|\n\n"); // Print the logo

    while(switcher != 0){ // Main loop

        printf("\n1. Register Product\n2. List Products\n3. Search Product\n4. Delete Product\n5. Buy Products\n0. Exit System\n");
        printf("\nType a number between 1 and 5 to navigate or 0 to exit the program: ");
        scanf("%d", &switcher); // Get user selection
        switcher = verifyMenuInput(switcher);

        switch(switcher){ // Go to user chosen option

            case(0): ; // Exit System

                printf("\nExiting...\n\n");
                
                *productsReference = clearProducts(productsReference); // Free the products list
                free(productsReference);

                exit(0); // Exit the code
            
            case(1): ; // Register Product

                registerProduct(productsReference);
                break;

            case(2): ; // List Products
                
                listProducts(productsReference);
                break;

            case(3): ; // Search Product

                searchProduct(productsReference);
                break;

            case(4): ; // Delete Product

                *productsReference = deleteProduct(productsReference);
                break;

            case(5): ; // Buy Products

                Product *head; // Create an extra product pointer to store the pile of updated products
                head = malloc(sizeof(Product));

                Product *helper; // Create an extra product pointer to store the old products
                helper = malloc(sizeof(Product));

                *head = goToCart(productsReference);

                *productsReference = updateProducts(productsReference, head, helper); // Update the products

                break;

            default: ; // If somehow the user bypass the input verification and type a invalid number, end the program

                printf("ERROR - Invalid Main Menu Input");
                break;
        }
    }

    printf("\nExiting...\n\n");

    return 0;
}