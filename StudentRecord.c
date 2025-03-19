#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_UNITS 10

// Structure to hold student details
typedef struct {
    char name[50];
    char reg_no[20];
    char course[50];
    char department[50];
    int num_units_done;
    float scores[MAX_UNITS];
    float average_score;
    char grade;
} StudentRecord;

// Function prototypes
void insert_record(StudentRecord students[], int *num_students);
void display_record(StudentRecord students[], int num_students, char reg_no[]);
void delete_record(StudentRecord students[], int *num_students, char reg_no[]);
void update_record(StudentRecord students[], int num_students, char reg_no[]);
void search_record(StudentRecord students[], int num_students, char keyword[]);
void sort_records(StudentRecord students[], int num_students);
char calculate_grade(float average_score);

int main() {
    StudentRecord students[MAX_STUDENTS];
    int num_students = 0;
    int choice;
    
    while (1) {
        printf("\nStudent Record Management System\n");
        printf("1. Insert New Record\n");
        printf("2. Display Record\n");
        printf("3. Delete Record\n");
        printf("4. Update Record\n");
        printf("5. Search Record\n");
        printf("6. Sort Records by Name\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline
        
        switch (choice) {
            case 1:
                insert_record(students, &num_students);
                break;
            case 2: {
                char reg_no[20];
                printf("Enter registration number to display record: ");
                fgets(reg_no, sizeof(reg_no), stdin);
                reg_no[strcspn(reg_no, "\n")] = '\0'; // Remove newline character
                display_record(students, num_students, reg_no);
                break;
            }
            case 3: {
                char reg_no[20];
                printf("Enter registration number to delete record: ");
                fgets(reg_no, sizeof(reg_no), stdin);
                reg_no[strcspn(reg_no, "\n")] = '\0'; // Remove newline character
                delete_record(students, &num_students, reg_no);
                break;
            }
            case 4: {
                char reg_no[20];
                printf("Enter registration number to update record: ");
                fgets(reg_no, sizeof(reg_no), stdin);
                reg_no[strcspn(reg_no, "\n")] = '\0'; // Remove newline character
                update_record(students, num_students, reg_no);
                break;
            }
            case 5: {
                char keyword[50];
                printf("Enter search keyword (name, registration number, course, or department): ");
                fgets(keyword, sizeof(keyword), stdin);
                keyword[strcspn(keyword, "\n")] = '\0'; // Remove newline character
                search_record(students, num_students, keyword);
                break;
            }
            case 6:
                sort_records(students, num_students);
                break;
            case 7:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a number from 1 to 7.\n");
                break;
        }
    }
    
    return 0;
}

// Function to insert a new student record
void insert_record(StudentRecord students[], int *num_students) {
    if (*num_students >= MAX_STUDENTS) {
        printf("Error: Maximum number of students reached.\n");
        return;
    }
    
    printf("Enter name: ");
    fgets(students[*num_students].name, sizeof(students[*num_students].name), stdin);
    students[*num_students].name[strcspn(students[*num_students].name, "\n")] = '\0'; // Remove newline character
    
    printf("Enter registration number: ");
    fgets(students[*num_students].reg_no, sizeof(students[*num_students].reg_no), stdin);
    students[*num_students].reg_no[strcspn(students[*num_students].reg_no, "\n")] = '\0'; // Remove newline character
    
    printf("Enter course: ");
    fgets(students[*num_students].course, sizeof(students[*num_students].course), stdin);
    students[*num_students].course[strcspn(students[*num_students].course, "\n")] = '\0'; // Remove newline character
    
    printf("Enter department: ");
    fgets(students[*num_students].department, sizeof(students[*num_students].department), stdin);
    students[*num_students].department[strcspn(students[*num_students].department, "\n")] = '\0'; // Remove newline character
    
    printf("Enter number of units done: ");
    scanf("%d", &students[*num_students].num_units_done);
    getchar(); // Consume newline
    
    printf("Enter scores for each unit:\n");
    for (int i = 0; i < students[*num_students].num_units_done; ++i) {
        printf("Score for unit %d: ", i + 1);
        scanf("%f", &students[*num_students].scores[i]);
    }
    
    // Calculate average score
    float total_score = 0.0;
    for (int i = 0; i < students[*num_students].num_units_done; ++i) {
        total_score += students[*num_students].scores[i];
    }
    students[*num_students].average_score = total_score / students[*num_students].num_units_done;
    
    // Calculate grade
    students[*num_students].grade = calculate_grade(students[*num_students].average_score);
    
    printf("Record for %s (%s) inserted successfully.\n", students[*num_students].name, students[*num_students].reg_no);
    
    (*num_students)++;
}

// Function to display a student record given a registration number
void display_record(StudentRecord students[], int num_students, char reg_no[]) {
    int found = 0;
    for (int i = 0; i < num_students; ++i) {
        if (strcmp(students[i].reg_no, reg_no) == 0) {
            printf("\nStudent Details:\n");
            printf("Name: %s\n", students[i].name);
            printf("Registration Number: %s\n", students[i].reg_no);
            printf("Course: %s\n", students[i].course);
            printf("Department: %s\n", students[i].department);
            printf("Average Score: %.2f\n", students[i].average_score);
            printf("Grade: %c\n", students[i].grade);
            printf("Scores for each unit:\n");
            for (int j = 0; j < students[i].num_units_done; ++j) {
                printf("Unit %d: %.2f\n", j + 1, students[i].scores[j]);
            }
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Error: Student with registration number %s not found.\n", reg_no);
    }
}

// Function to delete a student record given a registration number
void delete_record(StudentRecord students[], int *num_students, char reg_no[]) {
    int found = 0;
    for (int i = 0; i < *num_students; ++i) {
        if (strcmp(students[i].reg_no, reg_no) == 0) {
            for (int j = i; j < *num_students - 1; ++j) {
                students[j] = students[j + 1];
            }
            (*num_students)--;
            printf("Record for registration number %s deleted successfully.\n", reg_no);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Error: Student with registration number %s not found.\n", reg_no);
    }
}

// Function to update a student record given a registration number
void update_record(StudentRecord students[], int num_students, char reg_no[]) {
    int found = 0;
    for (int i = 0; i < num_students; ++i) {
        if (strcmp(students[i].reg_no, reg_no) == 0) {
            printf("Enter new name (leave blank to keep current): ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0'; // Remove newline character
            
            printf("Enter new course (leave blank to keep current): ");
            fgets(students[i].course, sizeof(students[i].course), stdin);
            students[i].course[strcspn(students[i].course, "\n")] = '\0'; // Remove newline character
            
            printf("Enter new department (leave blank to keep current): ");
            fgets(students[i].department, sizeof(students[i].department), stdin);
            students[i].department[strcspn(students[i].department, "\n")] = '\0'; // Remove newline character
            
            printf("Enter number of units done (leave blank to keep current): ");
            int new_num_units;
            scanf("%d", &new_num_units);
            getchar(); // Consume newline
            
            if (new_num_units > 0) {
                students[i].num_units_done = new_num_units;
                
                printf("Enter new scores
