/*
A simple program to ADD two numbers
the program should ask user to enter the first number
then the second number
compute the sum and display the sum on the console
*/

//including the pre-processor directives
#include <stdio.h>

// main function where program execution begins
int main() {
    // declare variables
    int firstnumber, secondnumber, sum;

    // ask user to enter the first number
    printf("Enter the first number: ");

    // get the first number through the keyboard
    scanf("%d", &firstnumber);

    // ask user to enter the second number
    printf("Enter the second number: ");

    // get the second number through the keyboard
    scanf("%d", &secondnumber);

    // compute the sum of the two numbers
    sum = firstnumber + secondnumber;

    // display the sum of the two numbers on console
    printf("Sum of two numbers is: %d\n", sum);

    // return 0 to indicate successful completion of program
    return 0;
}
