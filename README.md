# Password Manager

A simple and secure Password Manager implemented in C that allows users to store, retrieve, and manage account credentials with basic encryption. This project is suitable for learning file handling, encryption, and menu-driven programming in C.

## Features

- **Add New Accounts**  
  Save usernames and encrypted passwords securely.

- **Retrieve Account Passwords**  
  Decrypt and display the password for a specific account.

- **List All Accounts**  
  View all stored usernames.

- **Save and Load Accounts**  
  Persist account information in a binary file (`accounts.dat`) and reload it upon restarting the program.

- **Encryption**  
  Uses XOR encryption with a predefined key for secure password storage.

## How It Works

1. User interacts with a menu-driven interface.
2. Credentials are encrypted using XOR encryption before being stored.
3. All account data is saved to a file and reloaded automatically at startup.
4. Passwords can be retrieved by specifying the corresponding username.

## Installation and Usage

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/password-manager.git
   cd password-manager
