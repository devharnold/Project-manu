#include <stdio.h>

int main() {
    // Create an array to store scores
    int scores[5] = {0}; // Initialize all elements to 0

    // Insert values at specific indices
    scores[1] = 99;
    scores[2] = 63;
    scores[3] = 71;
    scores[4] = 83;

    // Display all elements separated by tabs
    for (int i = 0; i < 5; ++i) {
        printf("%d\t", scores[i]);
    }

    return 0;
}
