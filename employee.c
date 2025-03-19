#include <stdio.h>

#define MAX_EMPLOYEES 100

struct Employee {
    int employeeID;
    char name[50];
    float hourlyRate;
    float hoursWorked;
    float salary; // Calculated salary
};

int main() {
    struct Employee employees[MAX_EMPLOYEES];
    int numEmployees;

    // Input number of employees
    printf("Enter number of employees: ");
    scanf("%d", &numEmployees);

    // Input employee details
    for (int i = 0; i < numEmployees; i++) {
        printf("Enter details for Employee %d:\n", i+1);
        printf("Employee ID: ");
        scanf("%d", &employees[i].employeeID);
        printf("Name: ");
        scanf("%s", employees[i].name); // Assuming name input doesn't have spaces
        printf("Hourly Rate: ");
        scanf("%f", &employees[i].hourlyRate);
        printf("Hours Worked: ");
        scanf("%f", &employees[i].hoursWorked);

        // Calculate salary (example calculation)
        float grossPay = employees[i].hourlyRate * employees[i].hoursWorked;
        float taxes = grossPay * 0.1; // Example tax rate, adjust as needed
        employees[i].salary = grossPay - taxes;
    }

    // Display employee details with calculated salary
    printf("\nEmployee Details with Calculated Salary:\n");
    for (int i = 0; i < numEmployees; i++) {
        printf("Employee ID: %d\n", employees[i].employeeID);
        printf("Name: %s\n", employees[i].name);
        printf("Hourly Rate: %.2f\n", employees[i].hourlyRate);
        printf("Hours Worked: %.2f\n", employees[i].hoursWorked);
        printf("Salary: %.2f\n\n", employees[i].salary);
    }

    return 0;
}
