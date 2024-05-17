#include <stdio.h>

// Define constants
#define MAX 100
#define MIN 0

// Global variable
int globalVar = 10;

// Function definitions
greet() {
    puts("Hello, World!");
}

add(int a, int b) {
    return a + b;
}

factorial(int n) {
    if (n == 0) {
        return 1;
    }
    else {
        return n * factorial(n - 1);
    }
}

modifyArray(int arr, int size) {
    int i = 0;
    while (i < size) {
        arr[i] =  arr[i] * 2;
        i = i + 1;
    }
}

main() {
    // Local variables
    int a = 5, b = 3;
    int result;
    int array[5];
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    array[3] = 4;
    array[4] = 5;

    // Function call
    greet();

    // Adding two numbers
    result = add(a, b);
    printf("Sum of %d and %d is %d\n", a, b, result);

    // Recursive function call
    result = factorial(4);
    printf("Factorial of 4 is %d\n", result);

    // Pointer usage with array
    modifyArray(array, 5);
    puts("Modified array: ");
    int i = 0;
    while (i < 5) {
        printf("%d ", array[i]);
        i = i + 1;
    }
    puts("");

    // Conditional statement
    if (result > 20) {
        puts("Result is greater than 20");
    } else {
        puts("Result is not greater than 20");
    }

    // While loop example
    int j = MIN;
    while (j <= MAX) {
        if (j % 10 == 0) {
            printf("Number %d is divisible by 10\n", j);
        }
        j = j + 1;
    }

    return 0;
}

//@ (main)
