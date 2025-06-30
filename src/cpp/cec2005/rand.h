/* Declaration for random number related variables and routines */

#ifndef _RAND_H
#define _RAND_H

#include "global.h"

/* Function declarations for the random number generator */
void disablerand();
void enablerand();
double randomperc();
double randomnormaldeviate();

#endif