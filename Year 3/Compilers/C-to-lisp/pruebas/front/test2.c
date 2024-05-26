#include <stdio.h>

// Function definitions
processArray() {
    int array[9];
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    array[3] = 4;
    array[4] = 5;
    array[5] = 6;
    array[6] = 7;
    array[7] = 8;
    array[8] = 9;
    
    int i = 0;
    while (i < 9) {
        array[i] = array[i] * 2;
        i = i + 1;
    }
}

checkPrime(int num) {
    if (num <= 1) { return 0; }
    int i = 2;
    while (i * i <= num) {
        if (num % i == 0) { return 0; }
        i = i+1;
    }
    return 1;
}

nestedConditionals(int a, int b) {
    if (a > b) {
        if (checkPrime(a)) {
            puts("A is greater and prime");
        } else {
            puts("A is greater but not prime");
        }
    }  
    
    if (a < b) {
            if (checkPrime(b)) {
                puts("B is greater and prime");
            } else {
            puts("B is greater but not prime");
            }
    } else {
        puts("A and B are equal");
    }
}

main() {
    // Array processing
    processArray();

    // Nested conditional checks
    nestedConditionals(17, 29);
    nestedConditionals(15, 15);
    nestedConditionals(8, 2);

    // Double nested loop with conditional
    int outer = 1, inner;
    while (outer <= 5) {
        inner = 1;
        while (inner <= outer) {
            if (checkPrime(inner)) {
                printf("%d is prime\n", inner);
            }
            inner = inner + 1;
        }
        outer = outer + 1;
    }
}

// @(main)