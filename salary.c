#include <stdio.h>

// Function to calculate salary after deducting taxes
double calculateSalary(double hourly_rate, double hours_worked) {
    const double tax_rate = 0.15; // Assume a 15% tax rate
    double salary = hours_worked * hourly_rate;
    double taxes = salary * tax_rate;
    return salary - taxes;
}

int main() {
    int employee_id;
    char employee_name[100];
    double hourly_rate, hours_worked;

    // Input employee details
    printf("Enter employee ID: ");
    scanf("%d", &employee_id);
    printf("Enter employee name: ");
    scanf("%s", employee_name);
    printf("Enter hourly rate: ");
    scanf("%lf", &hourly_rate);
    printf("Enter hours worked: ");
    scanf("%lf", &hours_worked);

    // Calculate salary
    double salary = calculateSalary(hourly_rate, hours_worked);

    // Display employee details
    printf("\nEmployee ID: %d\n", employee_id);
    printf("Employee Name: %s\n", employee_name);
    printf("Calculated Salary: $%.2lf\n", salary);

    return 0;
}
