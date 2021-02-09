#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <time.h>
#include "location.hpp"
#include "story.hpp"

#define SIZE 64
#define MAX 1000000000

using namespace std;

double world[SIZE][SIZE];

double interpolate(double a0, double a1, double w) {
    if (0.0 > w) return a0;
    if (1.0 < w) return a1;
    //return (a1 - a0) * w + a0;
    return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
    //return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
}

// Create random direction vector
pair<double, double> randomGradient(int ix, int iy) {
    // Random double. No precomputed gradients mean this works for any number of grid coordinates
    double random = 2920.f * sin(ix * 21942.f + iy * 171324.f + 8912.f) * cos(ix * 23157.f * iy * 217832.f + 9758.f);
    return make_pair (cos(random), sin(random));
}

// Computes the dot product of the distance and gradient vectors.
double dotGridGradient(int ix, int iy, double x, double y) {
    // Get gradient from integer coordinates
    pair<double, double> gradient = randomGradient(ix, iy);

    // Compute the distance vector
    double dx = x - double(ix);
    double dy = y - double(iy);

    // Compute the dot-product
    return (dx*gradient.first + dy*gradient.second);
}

// Compute Perlin noise at coordinates x, y
double perlin(double x, double y) {
    // Determine grid cell coordinates
    int x0 = int(x);
    int x1 = x0 + 1;
    int y0 = int(y);
    int y1 = y0 + 1;

    // Determine interpolation weights
    // Could also use higher order polynomial/s-curve here
    double sx = x - double(x0);
    double sy = y - double(y0);

    // Interpolate between grid point gradients
    double n0, n1, ix0, ix1, value;

    n0 = dotGridGradient(x0, y0, x, y);
    n1 = dotGridGradient(x1, y0, x, y);
    ix0 = interpolate(n0, n1, sx);

    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    ix1 = interpolate(n0, n1, sx);

    value = interpolate(ix0, ix1, sy);
    return value;
}

double random_double(double a, double b) {
    double random = ((double) rand()) / (double) RAND_MAX;
    double diff = b - a;
    double r = random * diff;
    return a + r;
}

#define LOW 0.005
#define LOW_H 0.125
#define HI 0
#define HI_H 10000000




void gen()
{
    double w1=random_double(LOW, LOW_H), w2=w1, w3=random_double(LOW, LOW_H), w4=random_double(LOW, LOW_H), w5=random_double(LOW, LOW_H), w6=random_double(LOW, LOW_H), w7=random_double(LOW, LOW_H), w8=w7, s1=random_double(HI,HI_H),s2=random_double(HI,HI_H),s3=random_double(HI,HI_H),s4=random_double(HI,HI_H),s5=random_double(HI,HI_H),s6=random_double(HI,HI_H);
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            world[i][j]=perlin(w1*i+w7*perlin(w3*i+s3, w4*j+s4)+s1, w2*j+w8*perlin(w5*j+s5, w6*j+s6)+s2);
}

void print_world()
{
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
            {
                if(world[i][j] < -0.5)
                    cout << "🟪";
                else if(world[i][j] < random_double(-0.25,0) || j<rand()%SIZE/8+2 || j>SIZE-rand()%SIZE/8-2 || i<rand()%SIZE/8+2 || i>SIZE-rand()%SIZE/8-2)
                    cout << "🟦";
                else if(world[i][j] < 0.25)
                    cout << "🟩";
                else if(world[i][j] < 0.75)
                    cout << "🟫";
                else if(world[i][j] < 0.9)
                    cout << "⬛️";
                else
                    cout << world[i][j];
            }
        cout <<'\n';
    }
    for(int j = 0; j < SIZE; j++)
        cout << "⬛️";
    cout << '\n';
}

int main()
{
    srand (time(NULL));
    gen();
    print_world();
    return 0;
}
