#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long int limit, i, j;
char *erat;
int *primelist, *dic, sb, us, primelist_size;

int sofp(long int number) {
    int n, sum, p, j, i;

    for (p = primelist[0], i = 0, sum = 1, n = number; p * p <= n && n > 1 && i < primelist_size; i++) {
        p = primelist[i];

        if (n % p == 0) {
            j = p * p;
            n = n / p;
            while (n % p == 0) {
                j = j * p;
                n = n / p;
            }
            sum = sum * (j - 1) / (p - 1);
        }
    }

    if (n > 1) {
        sum *= n + 1;
    }

    return (sum - number);
}

int main(int argc, char** argv) {
    printf("Zadejte limit:\n");

    if (scanf("%li", &limit) != 1 || limit <= 0) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    /* naplneni primelistu */
    sb = (int) ((limit - 1) / 2);
    us = (((int) sqrt(limit) - 1) / 2);

    if ((erat = (char *) malloc((sb + 1) * sizeof (char))) == NULL) {
        printf("Malo pameti pro pole erat.\n");
        return 1;
    };

    for (i = 0; i < sb; i++) {
        erat[i] = 0;
    }

    for (i = 1; i < us; i++) {
        if (!erat[i]) {
            for (j = i * 2 * (i + 1); j <= sb; j += 2 * i + 1) {
                erat[j] = 1;
            }
        }
    }

    primelist_size = (int) (limit / (log(limit) - 1.08366));

    if ((primelist = (int *) malloc((primelist_size + 1) * sizeof (int))) == NULL) {
        printf("Malo pameti pro pole primelist.\n");
        return 1;
    };

    primelist[0] = 2;
    for (i = 1, j = 0; i < sb; i++) {
        if (!erat[i]) {
            primelist[++j] = 2 * i + 1;
        }
    }

    free(erat);

    if ((dic = (int *) malloc((limit + 2) * sizeof (int))) == NULL) {
        printf("Malo pameti pro pole dic.\n");
        return 1;
    };

    for (i = 0; i < limit + 1; i++) {
        dic[i] = 0;
    }

    for (i = 2; i <= limit; i++) {
        j = sofp(i);

        if (j > i) {
            dic[i] = j;
        } else {
            if (i == dic[j] && j <= limit) {
                printf("%ld, %ld\n", j, i);
            }
        }
    }

    free(primelist);

    free(dic);

    return (EXIT_SUCCESS);
}