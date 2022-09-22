#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int to_number(char* str) {
    int i, digit, base, sign, result, digits, start;

    sign = 1;
    start = digit = base = result = 0;
    digits = strlen(str);

    if (str[0] == '-') {
        sign = -1;
        start = 1;

        if (digits == 1) {
            return -1;
        }
    }

    for (i = digits - 1; i >= start; i--) {
        digit = str[i] - '0';

        if (digit < 0 || digit > 9) {
            return -1;
        }

        result += digit * pow(10, base++);
    }

    return sign * result;
}

int prime_factors(int n, int* primes) {
    int i;
    int p = 2;
    int n_primes = 0;
    int* sieve = (int*) malloc(sizeof(int) * n);

    if (sieve == NULL) {
        return -1;
    }

    sieve[0] = 0;
    sieve[1] = 0;

    for (i = 2; i < n; i++) {
        sieve[i] = 1;
    }

    while (p <= n) {
        primes[n_primes++] = p;

        for (i = p; i < n; i += p) {
            sieve[i] = 0;
        }

        do {
            p++;
        } while (sieve[p] != 1 && p <= n);
    }

    free(sieve);
    return n_primes;
}

int main(int argc, char** argv) {
    int i, n, n_primes;
    FILE* pFile = fopen("primes.txt", "w");
    int* primes;

    if (argc <= 1) {
        fprintf(stderr, "Fatal error: Missing required argument n\n");
        fprintf(stderr, "USAGE: PRIMES [n]\n");
        return 1;
    }

    n = to_number(argv[1]);

    if (n <= 1) {
        fprintf(stderr, "Fatal error: Integer n must be positive, greater than 1\n");
        fprintf(stderr, "USAGE: PRIMES [n]\n");
        return 1;
    }

    primes = (int*) malloc(sizeof(int) * n);

    if (pFile == NULL) {
        fprintf(stderr, "Fatal error: Could not open primes.txt");
        return 1;
    }

    if (primes == NULL) {
        fprintf(stderr, "Fatal error: Failed to allocate enough memory for %ld integers", n);
        return 1;
    }

    printf("Searching for primes from 1..%d\n", n);
    n_primes = prime_factors(n, primes);
    printf("Done, %d primes found\n", n_primes);
    printf("Stored results in primes.txt\n");

    if (n_primes > 0) {
        for (i = 0; i < n_primes; i++) {
            fprintf(pFile, "%d\n", primes[i]);
        }
    }

    fclose(pFile);
    free(primes);
    return 0;
}
