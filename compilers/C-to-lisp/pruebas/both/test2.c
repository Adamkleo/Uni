
int x = 3;

test() { puts("We are inside function test!"); }

main() {
    if (x == 3) {
        while (x > 0) {
            printf("%d", x);
            if (x % 2 == 0) {
                puts(" es par ");
            } else {
                puts(" es impar ");
            }
            x = x - 1;
        }
    }

    if (x == 0) {
        printf("x is %d!", x);
    }


}