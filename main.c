#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define ENCRYPTION_KEY 0x5A // Basit XOR anahtarı

typedef struct {
    char username[MAX_USERNAME];
    char encrypted_password[MAX_PASSWORD];
} Account;

Account accounts[MAX_ACCOUNTS];
int account_count = 0;

// XOR şifreleme fonksiyonu
void encrypt_decrypt(const char *input, char *output) {
    for (int i = 0; i < strlen(input); i++) {
        output[i] = input[i] ^ ENCRYPTION_KEY; // XOR işlemi
    }
    output[strlen(input)] = '\0'; // Null sonlandırıcı
}

void add_account() {
    if (account_count >= MAX_ACCOUNTS) {
        printf("Account storage is full!\n");
        return;
    }

    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char encrypted_password[MAX_PASSWORD];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    // Şifreleme işlemi
    encrypt_decrypt(password, encrypted_password);

    // Hesap bilgilerini kaydet
    strcpy(accounts[account_count].username, username);
    strcpy(accounts[account_count].encrypted_password, encrypted_password);

    account_count++;
    printf("Account added successfully!\n");
}

void retrieve_account() {
    char username[MAX_USERNAME];
    char decrypted_password[MAX_PASSWORD];
    int found = 0;

    printf("Enter username to retrieve: ");
    scanf("%s", username);

    for (int i = 0; i < account_count; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            encrypt_decrypt(accounts[i].encrypted_password, decrypted_password);
            printf("Decrypted password: %s\n", decrypted_password);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Account not found!\n");
    }
}

void list_accounts() {
    if (account_count == 0) {
        printf("No accounts stored.\n");
        return;
    }

    printf("Stored accounts:\n");
    for (int i = 0; i < account_count; i++) {
        printf("- %s\n", accounts[i].username);
    }
}

int main() {
    while (1) {
        int choice;
        printf("\nPassword Manager\n");
        printf("1. Add account\n");
        printf("2. Retrieve account\n");
        printf("3. List accounts\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_account();
                break;
            case 2:
                retrieve_account();
                break;
            case 3:
                list_accounts();
                break;
            case 4:
                printf("Exiting. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
