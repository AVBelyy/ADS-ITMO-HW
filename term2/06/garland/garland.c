#include <stdio.h>
#include <math.h>

#define h(h1g, x) (h0 - h0 * (x) + (x) * ((h1g) + (x) - 1))

int main() {
    int n, i;
    double h0, h1 = 1e3;
    freopen("garland.in",  "r", stdin);
    freopen("garland.out", "w", stdout);
    scanf("%d%lf", &n, &h0);
    for (i = 10; i >= -20; i--) {
        double h1_guess = h1 - pow(2.0f, i);
        double min = (h0 - h1_guess + 1) / 2.0;
        double m1 = h(h1_guess, floor(min)), m2 = h(h1_guess, ceil(min));
        if ((m1 > 0 && m2 > 0) || ((min < 0 || min > n - 1) && h(h1_guess, 0) > 0 && h(h1_guess, n - 1) > 0)) {
            h1 = h1_guess;
        }
    }
    printf("%.2lf\n", h(h1, n - 1));
    return 0;
}
