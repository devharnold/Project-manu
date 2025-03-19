// /loops
/*
tasks: rewrite the programs to print all
the even integers from 20 to 7 in descending order in
    a. while loop
    b. do while loop
    */
    
        
    #include <stdio.h>

void print_even_numbers_while() {
    int i = 20;
    while (i >= 7) {
        if (i % 2 == 0) {
            printf("%d\n", i);
        }
        i--;
    }
}

int main() {
    printf("Using while loop:\n");
    print_even_numbers_while();
    return 0;
}



#include <stdio.h>

void print_even_numbers_do_while() {
    int i = 20;
    do {
        if (i % 2 == 0) {
            printf("%d\n", i);
        }
        i--;
    } while (i >= 7);
}

int main() {
    printf("Using do-while emulation:\n");
    print_even_numbers_do_while();
    return 0;
}

