#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include <random>

#include "global.h"
#include "rand.h"

std::random_device rd{};
std::mt19937 gen{rd()};

// Values near the mean are the most likely. Standard deviation
// affects the dispersion of generated values from the mean.
std::normal_distribution d{0.0, 1.0};

int randenabled = 1;

void disablerand()
{
    randenabled = 0;
}

void enablerand()
{
    randenabled = 1;
}

/* Fetch a single random number between 0.0 and 1.0 */
double randomperc()
{
    if (randenabled)
        return ((double) rand() / (RAND_MAX));
    return 0;
}

/* Compute the noise */
double randomnormaldeviate()
{
    double res = 0;

    if (randenabled) {
        res = d(gen);
    }

    return res;
}