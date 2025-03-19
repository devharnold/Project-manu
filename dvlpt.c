#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_USERS 50

// Structures
typedef struct {
    char title[100];
    char author[50];
    char ISBN[20];
    int availability; // 1 for available, 0 for not available
} Book;

typedef struct {
    int userID;
    char name[50];
    int numBooksBorrowed;
    char borrowedBooks[MAX_BOOKS][20]; // ISBNs of borrowed books
} User;

// Global variables
Book library[MAX_BOOKS];
User users[MAX_USERS];
int numBooks = 0;
int numUsers = 0;

// Function prototypes
void addBook();
void addUser();
void borrowBook();
void returnBook();
void listBooks();

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

void addBook() {
    if (numBooks < MAX_BOOKS) {
        Book newBook;
        
        printf("Enter book title: ");
        scanf(" %[^\n]s", newBook.title);
        printf("Enter author: ");
        scanf(" %[^\n]s", newBook.author);
        printf("Enter ISBN: ");
        scanf(" %s", newBook.ISBN);
        newBook.availability = 1; // Book is initially available
        
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
        newUser.numBooksBorrowed = 0; // Initially no books borrowed
        
        users[numUsers++] = newUser;
        
        printf("User added successfully.\n");
    } else {
        printf("Maximum number of users reached. Cannot add more users.\n");
    }
}

void borrowBook() {
    int userID, foundUser = 0;
    char ISBN[20];
    int i, j;
    
    printf("Enter user ID: ");
    scanf("%d", &userID);
    printf("Enter ISBN of the book to borrow: ");
    scanf(" %s", ISBN);
    
    // Find the user
    for (i = 0; i < numUsers; i++) {
        if (users[i].userID == userID) {
            foundUser = 1;
            break;
        }
    }
    
    if (!foundUser) {
        printf("User not found. Please enter a valid user ID.\n");
        return;
    }
    
    // Check if book is available and borrow if possible
    for (j = 0; j < numBooks; j++) {
        if (strcmp(library[j].ISBN, ISBN) == 0) {
            if (library[j].availability == 1) {
                // Book is available
                if (users[i].numBooksBorrowed < MAX_BOOKS) {
                    // Borrow the book
                    strcpy(users[i].borrowedBooks[users[i].numBooksBorrowed++], ISBN);
                    library[j].availability = 0; // Book is now borrowed
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
}

void returnBook() {
    int userID, foundUser = 0;
    char ISBN[20];
    int i, j, k;
    
    printf("Enter user ID: ");
    scanf("%d", &userID);
    printf("Enter ISBN of the book to return: ");
    scanf(" %s", ISBN);
    
    // Find the user
    for (i = 0; i < numUsers; i++) {
        if (users[i].userID == userID) {
            foundUser = 1;
            break;
        }
    }
    
    if (!foundUser) {
        printf("User not found. Please enter a valid user ID.\n");
        return;
    }
    
    // Find the book in user's borrowed books
    for (j = 0; j < users[i].numBooksBorrowed; j++) {
        if (strcmp(users[i].borrowedBooks[j], ISBN) == 0) {
            // Book found, now return it
            for (k = 0; k < numBooks; k++) {
                if (strcmp(library[k].ISBN, ISBN) == 0) {
                    library[k].availability = 1; // Book is now available
                    break;
                }
            }
            
            // Remove the returned book from user's borrowed list
            for (; j < users[i].numBooksBorrowed - 1; j++) {
                strcpy(users[i].borrowedBooks[j], users[i].borrowedBooks[j + 1]);
            }
            users[i].numBooksBorrowed--;
            
            printf("Book returned successfully.\n");
            return;
        }
    }
    
    printf("User has not borrowed this book.\n");
}

void listBooks() {
    int i;
    
    printf("\nList of Books in the Library:\n");
    printf("--------------------------------------------------\n");
    printf("%-20s | %-20s | %-20s | %s\n", "Title", "Author", "ISBN", "Availability");
    printf("--------------------------------------------------\n");
    
    for (i = 0; i < numBooks; i++) {
        printf("%-20s | %-20s | %-20s | %s\n", library[i].title, library[i].author, library[i].ISBN,
               (library[i].availability == 1 ? "Available" : "Not Available"));
    }
    
    printf("--------------------------------------------------\n");
}
