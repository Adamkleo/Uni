
int x = 3;
int y = 6;
int g = 9;



main() {
    while (x < y) {
        while (y < g) {
            y = y + 1;
        }
    }
    x = x + 1;

    printf("%d %d %d\n", x, y, g);

    if (x == y && x == g && y == g) {
        puts("Son iguales");
    } else {
        puts("No son iguales");
    }
}