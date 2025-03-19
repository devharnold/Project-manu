#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_BOOKS 100
#define MAX_USERS 50

typedef struct {
    char title[100];
    char author[50];
    char ISBN[20];
    int availability;
} Book;

typedef struct {
    int userID;
    char name[50];
    int numBooksBorrowed;
    char borrowedBooks[MAX_BOOKS][20];
} User;

Book library[MAX_BOOKS];
User users[MAX_USERS];
int numBooks = 0;
int numUsers = 0;

void addBook() {
    if (numBooks < MAX_BOOKS) {
        Book newBook;
        printf("Enter book title: ");
        scanf(" %[^\n]s", newBook.title);
        printf("Enter author: ");
        scanf(" %[^\n]s", newBook.author);
        printf("Enter ISBN: ");
        scanf(" %s", newBook.ISBN);
        newBook.availability = 1;
        library[numBooks++] = newBook;
        printf("Book added successfully.\n");
    } else {
        printf("Maximum number of books reached. Cannot add more books.\n");
    }
}

void addUser() {
    if (numUsers < MAX_USERS) {
        User newUser;
        printf("Enter user ID: ");
        scanf("%d", &newUser.userID);
        printf("Enter user name: ");
        scanf(" %[^\n]s", newUser.name);
        newUser.numBooksBorrowed = 0;
        users[numUsers++] = newUser;
        printf("User added successfully.\n");
    } else {
        printf("Maximum number of users reached. Cannot add more users.\n");
    }
}

void borrowBook() {
    int userID, foundUser = 0;
    char ISBN[20];
    printf("Enter user ID: ");
    scanf("%d", &userID);
    printf("Enter ISBN of the book to borrow: ");
    scanf(" %s", ISBN);

    for (int i = 0; i < numUsers; i++) {
        if (users[i].userID == userID) {
            foundUser = 1;
            for (int j = 0; j < numBooks; j++) {
                if (strcmp(library[j].ISBN, ISBN) == 0) {
                    if (library[j].availability == 1) {
                        if (users[i].numBooksBorrowed < MAX_BOOKS) {
                            strcpy(users[i].borrowedBooks[users[i].numBooksBorrowed++], ISBN);
                            library[j].availability = 0;
                            printf("Book borrowed successfully.\n");
                        } else {
                            printf("Maximum number of books borrowed reached for this user.\n");
                        }
                    } else {
                        printf("Book is not available for borrowing.\n");
                    }
                    return;
                }
            }
            printf("Book not found in the library.\n");
            return;
        }
    }
    printf("User not found. Please enter a valid user ID.\n");
}

void returnBook() {
    int userID, foundUser = 0;
    char ISBN[20];
    printf("Enter user ID: ");
    scanf("%d", &userID);
    printf("Enter ISBN of the book to return: ");
    scanf(" %s", ISBN);

    for (int i = 0; i < numUsers; i++) {
        if (users[i].userID == userID) {
            foundUser = 1;
            for (int j = 0; j < users[i].numBooksBorrowed; j++) {
                if (strcmp(users[i].borrowedBooks[j], ISBN) == 0) {
                    for (int k = 0; k < numBooks; k++) {
                        if (strcmp(library[k].ISBN, ISBN) == 0) {
                            library[k].availability = 1;
                            break;
                        }
                    }
                    for (int l = j; l < users[i].numBooksBorrowed - 1; l++) {
                        strcpy(users[i].borrowedBooks[l], users[i].borrowedBooks[l + 1]);
                    }
                    users[i].numBooksBorrowed--;
                    printf("Book returned successfully.\n");
                    return;
                }
            }
            printf("User has not borrowed this book.\n");
            return;
        }
    }
    printf("User not found. Please enter a valid user ID.\n");
}

void listBooks() {
    printf("\nList of Books in the Library:\n");
    printf("--------------------------------------------------\n");
    printf("%-20s | %-20s | %-20s | %s\n", "Title", "Author", "ISBN", "Availability");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < numBooks; i++) {
        printf("%-20s | %-20s | %-20s | %s\n", library[i].title, library[i].author, library[i].ISBN,
               (library[i].availability == 1 ? "Available" : "Not Available"));
    }

    printf("--------------------------------------------------\n");
}

int main() {
    int choice;
    
    do {
        printf("\nLibrary Management System Menu:\n");
        printf("1. Add a book\n");
        printf("2. Add a user\n");
        printf("3. Borrow a book\n");
        printf("4. Return a book\n");
        printf("5. List all books\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                addUser();
                break;
            case 3:
                borrowBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                listBooks();
                break;
            case 6:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
    } while (choice != 6);

    return 0;
}
