#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv) {
    double a, b, c, o, s, S,
           alfa, beta, gama,
           alfa_s, beta_s, gama_s,
           alfa_m, beta_m, gama_m,
           alfa_sec, beta_sec, gama_sec,
           rns,
           r_veps, r_ops,
           va, vb, vc,
           pi2;
    
    pi2 = M_PI / 2.0;
    
    printf("Zadejte velikost stran a b c:\n");
    
    if ( scanf("%lf %lf %lf", &a, &b, &c) != 3 ||
         a <= 0 || b <= 0 || c <= 0) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    /*
     
     
     A:Zadejte velikost stran a b c:
81.041695 188.228562 109.135126
Trojuhelnik neni ani rovnostranny ani rovnoramenny.
Trojuhelnik je tupouhly.
Uhel alfa: 0.1233 rad = 7 s 03'55.60''
Uhel beta: 2.8519 rad = 163 s 24'00.00''
Uhel gama: 0.1664 rad = 9 s 32'04.40''
Obvod: 378.4054
Obsah: 1263.3848
Polomer kruznice vepsane: 6.6774
Polomer kruznice opsane: 329.4298
Vyska va: 31.1786
Vyska vb: 13.4239
Vyska vc: 23.1527
     
     
     2.4175 0.6769 2.3208 ?
To se mi líbí ·  · Sledovat příspěvek · úterý v 14:54

Radek Chromík Trojuhelnik neni ani rovnostranny ani rovnoramenny.
Trojuhelnik je pravouhly.
Uhel alfa: 1.5708 rad = 90 s 00'00.00''
Uhel beta: 0.2838 rad = 16 s 15'36.74''
Uhel gama: 1.2870 rad = 73 s 44'23.26''
Obvod: 5.4152 
Obsah: 0.7855
Polomer kruznice vepsane: 0.2901
Polomer kruznice opsane: 1.2087
Vyska va: 0.6498
Vyska vb: 2.3208
Vyska vc: 0.6769
     
     */
    
    
    if ( ((a+b) <= c) ||
         ((a+c) <= b) ||
         ((b+c) <= a)) {
        printf("Trojuhelnik neexistuje.\n");
        return 1;
    }
        
    alfa = acos( ((a*a)-(b*b)-(c*c)) / (-2.0*b*c) );
    beta = acos( ((b*b)-(a*a)-(c*c)) / (-2.0*a*c) );
    gama = acos( ((c*c)-(b*b)-(a*a)) / (-2.0*a*b) );
        
    rns = 180.0 / M_PI;
    
    alfa_s = alfa * rns;
    alfa_m = ( alfa_s - floor(alfa_s)) * 60;
    alfa_sec = ( alfa_m - floor(alfa_m) ) * 60;
    
    if ( alfa_sec > 59.99 ) {
        alfa_sec = 0;
        alfa_m++;
    }
        
    if ( alfa_m > 59.99 ) {
        alfa_m = 0;
        alfa_s++;
    }
    
    beta_s = beta * rns;
    beta_m = ( beta_s - floor(beta_s)) * 60;
    beta_sec = ( beta_m - floor(beta_m) ) * 60;
 
    if ( beta_sec > 59.99 ) {
        beta_sec = 0;
        beta_m++;
    }
        
    if ( beta_m > 59.99 ) {
        beta_m = 0;
        beta_s++;
    }
    
    gama_s = gama * rns;
    gama_m = ( gama_s - floor(gama_s)) * 60;
    gama_sec = ( gama_m - floor(gama_m) ) * 60;
    
    if ( gama_sec > 59.99 ) {
        gama_sec = 0;
        gama_m++;
    }
        
    if ( gama_m > 59.99 ) {
        gama_m = 0;
        gama_s++;
    }
    
    o = a + b + c;
    s = o / 2.0;
    S = sqrt(s*(s-a)*(s-b)*(s-c));
    
    r_veps = S / s;
    r_ops = a / (2 * sin(alfa));
    
    va = b * sin(gama);
    vb = a * sin(gama);
    vc = a * sin(beta);
    
    
    if ( alfa == beta && beta == gama && gama == alfa ) {
        printf("Trojuhelnik je rovnostranny.\n");        
    } else if ( alfa != beta && beta != gama && gama != alfa ) {
        printf("Trojuhelnik neni ani rovnostranny ani rovnoramenny.\n");
    } else {
        printf("Trojuhelnik je rovnoramenny.\n");
    }
        
    if ( ((alfa > (pi2 - 0.0000001)) && (alfa < (pi2 + 0.0000001))) ||
         ((beta > (pi2 - 0.0000001)) && (beta < (pi2 + 0.0000001))) ||
         ((gama > (pi2 - 0.0000001)) && (gama < (pi2 + 0.0000001))) ) {
        printf("Trojuhelnik je pravouhly.\n");
    } else if ( (alfa > 0 && alfa < pi2) &&
                (beta > 0 && beta < pi2) &&
                (gama > 0 && gama < pi2) ) {
        printf("Trojuhelnik je ostrouhly.\n");
    } else {
        printf("Trojuhelnik je tupouhly.\n");
    }
    
    printf("Uhel alfa: %.4f rad = %g s %02g'%05.2f''\n", alfa, floor(alfa_s), floor(alfa_m), alfa_sec);
    printf("Uhel beta: %.4f rad = %g s %02g'%05.2f''\n", beta, floor(beta_s), floor(beta_m), beta_sec);
    printf("Uhel gama: %.4f rad = %g s %02g'%05.2f''\n", gama, floor(gama_s), floor(gama_m), gama_sec);
    printf("Obvod: %.4f\n", o);
    printf("Obsah: %.4f\n", S);
    printf("Polomer kruznice vepsane: %.4f\n", r_veps);
    printf("Polomer kruznice opsane: %.4f\n", r_ops);
    printf("Vyska va: %.4f\n", va);
    printf("Vyska vb: %.4f\n", vb);
    printf("Vyska vc: %.4f\n", vc);
    
    return 0;
}

