#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

typedef struct {
    int x; /* souradnice x */
    int y; /* souradnice y */
} SOURADNICE;

typedef struct {
    char typ; /* bud R nebo C */
    int r; /* polomer kruhu */
    SOURADNICE s; /* stred */
    SOURADNICE rs[2]; /* rohy lh a pd */
} TVAR;

int main(int argc, char** argv) {
    TVAR tvar[2];
    TVAR *r, *c; /* pointery na r a c pri pruniku r a c */
    SOURADNICE tmp[2]; /* docasne ulozeni dvou bodu pri zadavani ctverce */
    int i, j;
    double cdx, cdy, rw2, rh2, cds;

    for (i = 0; i < 2; i++) {
        printf("Tvar %d (R=rectangle, C=circle):\n", i + 1);

        if (scanf("%c", &tvar[i].typ) != 1 || (tvar[i].typ != 'R' && tvar[i].typ != 'C')) {
            printf("Nespravny vstup.\n");
            return 1;
        }

        while (getchar() != '\n');

        if (tvar[i].typ == 'R') {
            for (j = 0; j < 2; j++) {
                printf("%s bod:\n", (j == 0) ? "Prvni" : "Druhy");
                if (scanf("%d %d", &tmp[j].x, &tmp[j].y) != 2) {
                    printf("Nespravny vstup.\n");
                    return 1;
                }

                while (getchar() != '\n');
            }

            /* upraveni protilehlych rohu */
            tvar[i].rs[0].x = min(tmp[0].x, tmp[1].x);
            tvar[i].rs[0].y = min(tmp[0].y, tmp[1].y);
            tvar[i].rs[1].x = max(tmp[0].x, tmp[1].x);
            tvar[i].rs[1].y = max(tmp[0].y, tmp[1].y);

            if (tvar[i].rs[0].x == tvar[i].rs[1].x ||
                    tvar[i].rs[0].y == tvar[i].rs[1].y) {
                printf("Nespravny vstup.\n");
                return 1;
            }

        } else if (tvar[i].typ == 'C') {
            printf("Stred:\n");
            if (scanf("%i %i", &tvar[i].s.x, &tvar[i].s.y) != 2) {
                printf("Nespravny vstup.\n");
                return 1;
            }

            while (getchar() != '\n');

            printf("Polomer:\n");
            if ((scanf("%i", &tvar[i].r) != 1) || tvar[i].r <= 0) {
                printf("Nespravny vstup.\n");
                return 1;
            }

            while (getchar() != '\n');

        } else {
            printf("Nespravny vstup.\n");
            return 1;
        }
    }

    if (tvar[0].typ == tvar[1].typ) {
        if (tvar[0].typ == 'R') { /* prunik R a R */

            if (
                    tvar[0].rs[1].x >= tvar[1].rs[0].x &&
                    tvar[1].rs[1].x >= tvar[0].rs[0].x &&
                    tvar[0].rs[1].y >= tvar[1].rs[0].y &&
                    tvar[1].rs[1].y >= tvar[0].rs[0].y
                    ) {
                printf("Prunik je neprazdny.\n");
                return 0;
            }
        } else { /* prunik C a C */
            if (((double) sqrt((tvar[0].s.x - tvar[1].s.x)*(tvar[0].s.x - tvar[1].s.x) + (tvar[0].s.y - tvar[1].s.y)*(tvar[0].s.y - tvar[1].s.y))) <= (tvar[0].r + tvar[1].r)) {
                printf("Prunik je neprazdny.\n");
                return 0;
            }
        }
    } else { /* prunik R a C */
        if (tvar[0].typ == 'R') {
            r = &tvar[0];
            c = &tvar[1];
        } else {
            r = &tvar[1];
            c = &tvar[0];
        }

        rw2 = (double) ((r->rs[1].x - r->rs[0].x) / 2);
        rh2 = (double) ((r->rs[1].y - r->rs[0].y) / 2);
        cdx = (double) (abs(c->s.x - r->rs[0].x - rw2));
        cdy = (double) (abs(c->s.y - r->rs[0].y - rh2));


        if (cdx > (rw2 + c->r)) {
            printf("Prunik je prazdny.\n");
            return 0;
        }

        if (cdy > (rh2 + c->r)) {
            printf("Prunik je prazdny.\n");
            return 0;
        }

        if (cdx <= rw2 + 1) {
            printf("Prunik je neprazdny.\n");
            return 0;
        }

        if (cdy <= rh2 + 1) {
            printf("Prunik je neprazdny.\n");
            return 0;
        }

        cds = (double) ((cdx - rw2)*(cdx - rw2)+(cdy - rh2)*(cdy - rh2));

        if (cds <= (c->r * c->r)) {
            printf("Prunik je neprazdny.\n");
            return 0;
        }
    }

    printf("Prunik je prazdny.\n");
    return 0;
}


/*
        if (
                ((r->rs[0].x - c->r) <= c->s.x) &&
                ((r->rs[0].y - c->r) <= c->s.y) &&
                ((r->rs[1].x + c->r) >= c->s.x) &&
                ((r->rs[1].y + c->r) >= c->s.y)
                ) {
            printf("Prunik je neprazdny.\n");
            return 0;
        }
 */

/*nelezi kruh uvnitr obdelniku?*/
/*
        if (
                r->rs[0].x >= c->s.x &&
                r->rs[0].y >= c->s.y &&
                r->rs[1].x <= c->s.x &&
                r->rs[1].y <= c->s.y) {
            printf("Prunik je neprazdny.\n");
            return 0;
        }
 */