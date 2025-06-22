#include "cec2017.h"

extern int nreal;

double calc_benchmark_func_f1_2017(double *x)
{
 
    double f = 0;
    cec17_test_func(x, &f, nreal, 1, 1);
    return f;
}