//Code by Alberto Pickering

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int isPrime(int n) {
    if (n < 2)
        return 0;
    
    int i;
    for (i = 2; i*i <= n; ++i)
        if (n % i == 0)
            return 0;
    
    return 1;
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        printf("Argumentos incorrectos\n");
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    int max = (int)strlen(argv[1]) - 1;
    
    int i;
    for (i = 0; i <= max; ++i) {
        if (!isPrime(n)) {
            printf("No es primo circular\n");
            return EXIT_SUCCESS;
        }
        n = (n % 10) * (int)pow(10, max) + n / 10;
    }
    printf("Sí es primo circular\n");
    return EXIT_SUCCESS;
}
