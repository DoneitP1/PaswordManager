#include <stdio.h>   // For input and output functions
#include <stdlib.h>  // For general utility functions
#include <string.h>  // For string handling functions

#define MAX_ACCOUNTS 100  // Maximum number of accounts that can be stored
#define MAX_USERNAME 50   // Maximum username length
#define MAX_PASSWORD 50   // Maximum password length
#define ENCRYPTION_KEY 0x5A  // Encryption key for XOR encryption
#define DATA_FILE "accounts.dat"  // File to save account data

// Structure to hold account details
typedef struct {
    char username[MAX_USERNAME]; // To store the username
    char encrypted_password[MAX_PASSWORD]; // To store the encrypted password
} Account;

// Global variables
static Account accounts[MAX_ACCOUNTS]; // Array to hold accounts
static int account_count = 0;       // Keeps track of the number of stored accounts

// Function prototypes
void load_accounts_from_file(void);    // Loads accounts from a file
void save_accounts_to_file(void);     // Saves accounts to a file
void encrypt_or_decrypt(const char *input, char *output); // Encrypts or decrypts strings
void display_menu(void);              // Displays the main menu
void add_new_account(void);           // Adds a new account
void retrieve_account_password(void); // Retrieves an account password
void list_all_accounts(void);         // Lists all account usernames

int main() {
    load_accounts_from_file(); // Load existing accounts from the file at startup

    while (1) { // Infinite loop to keep showing the menu
        display_menu(); // Display the options to the user

        int choice; // To hold the user's choice
        printf("Choose an option: "); // Prompt user for input
        if (scanf("%d", &choice) != 1) { // Check for valid input
            printf("Invalid input. Exiting.\n"); // Error message for invalid input
            break; // Exit the loop on invalid input
        }

        switch (choice) { // Handle user input
            case 1:
                add_new_account(); // Add a new account
                break;
            case 2:
                retrieve_account_password(); // Retrieve an account password
                break;
            case 3:
                list_all_accounts(); // List all account usernames
                break;
            case 4:
                save_accounts_to_file(); // Save accounts before exiting
                printf("Data saved. Goodbye!\n"); // Goodbye message
                return 0; // Exit the program
            default:
                printf("Invalid choice. Please try again.\n"); // Message for invalid choice
        }
    }

    return 0; // Return 0 to indicate successful execution (not typically reached)
}

// Load accounts from a file
void load_accounts_from_file(void) {
    FILE *file = fopen(DATA_FILE, "rb"); // Open the file in binary read mode
    if (file) { // Check if the file exists
        fread(&account_count, sizeof(int), 1, file); // Read the number of accounts
        fread(accounts, sizeof(Account), account_count, file); // Read the accounts
        fclose(file); // Close the file
        printf("Loaded %d accounts from file.\n", account_count); // Success message
    } else {
        printf("No data found. Starting fresh.\n"); // Message if file doesn't exist
    }
}

// Save accounts to a file
void save_accounts_to_file(void) {
    FILE *file = fopen(DATA_FILE, "wb"); // Open the file in binary write mode
    if (file) { // Check if the file opened successfully
        fwrite(&account_count, sizeof(int), 1, file); // Write the number of accounts
        fwrite(accounts, sizeof(Account), account_count, file); // Write the accounts
        fclose(file); // Close the file
        printf("Data saved successfully.\n"); // Success message
    } else {
        printf("Error saving data.\n"); // Error message
    }
}

// Encrypt or decrypt a string using XOR
void encrypt_or_decrypt(const char *input, char *output) {
    size_t len = strlen(input); // Get the length of the input string
    for (size_t i = 0; i < len; i++) { // Loop through each character
        output[i] = input[i] ^ ENCRYPTION_KEY; // XOR the character with the key
    }
    output[len] = '\0'; // Null-terminate the output string
}

// Display the main menu options
void display_menu(void) {
    printf("\n===== Password Manager =====\n"); // Menu header
    printf("1. Add a new account\n"); // Option to add a new account
    printf("2. Retrieve an account password\n"); // Option to retrieve a password
    printf("3. List all accounts\n"); // Option to list all accounts
    printf("4. Save and Exit\n"); // Option to save and exit
}

// Add a new account to the system
void add_new_account(void) {
    if (account_count >= MAX_ACCOUNTS) { // Check if storage is full
        printf("Cannot add more accounts. Storage full!\n"); // Notify user
        return; // Exit the function
    }

    Account new_account; // Create a new account
    char password[MAX_PASSWORD]; // Temporary storage for the password

    printf("Enter username: "); // Prompt user for username
    scanf("%s", new_account.username); // Read the username

    printf("Enter password: "); // Prompt user for password
    scanf("%s", password); // Read the password

    encrypt_or_decrypt(password, new_account.encrypted_password); // Encrypt the password

    accounts[account_count++] = new_account; // Store the new account and increment count
    printf("Account added successfully!\n"); // Success message
}

// Retrieve and display the password for a given account
void retrieve_account_password(void) {
    char username[MAX_USERNAME]; // Temporary storage for the username
    char decrypted_password[MAX_PASSWORD]; // To hold the decrypted password

    printf("Enter username to retrieve: "); // Prompt user for username
    scanf("%s", username); // Read the username

    for (int i = 0; i < account_count; i++) { // Loop through all accounts
        if (strcmp(accounts[i].username, username) == 0) { // Check for matching username
            encrypt_or_decrypt(accounts[i].encrypted_password, decrypted_password); // Decrypt the password
            printf("Password for %s: %s\n", username, decrypted_password); // Display the password
            return; // Exit the function after finding the account
        }
    }

    printf("Account not found!\n"); // Notify user if account wasn't found
}

// List all stored account usernames
void list_all_accounts(void) {
    if (account_count == 0) { // Check if there are no accounts
        printf("No accounts stored.\n"); // Notify user
        return; // Exit the function
    }

    printf("===== Stored Accounts =====\n"); // Header for the account list
    for (int i = 0; i < account_count; i++) { // Loop through all accounts
        printf("- %s\n", accounts[i].username); // Print each username
    }
}

