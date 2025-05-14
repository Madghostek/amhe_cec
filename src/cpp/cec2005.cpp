#include <cmath>
#include <iostream>
#include <vector>
#include "cec2005.h"
#include "global.h"

long double calc_sphere(const long double* x, int n) {
    long double res = 0;
    for (int i=0; i<n; i++)
    {
        res += x[i]*x[i];
    }
    return (res);
}

long double cec2005_f1_eval(const long double* x, int n) {
    long double res;
    transform (x, 0);
    basic_f[0] = calc_sphere(trans_x, n);
    res = basic_f[0] + bias[0];
    return (res);
}


void cec2005_f1_grad(const long double* x, long double* gradient, int n)
{
    for (int i = 0; i < n; ++i) {
        long double value = 0;
        long double z = x[i] - o[0][i];
        value += z * z;
        gradient[i] = 2.0 * z;  // d/dz (z^2) is 2z
    }
}

void cec2005_f1_init(int dim)
{
    allocate_memory(dim);
    int i, j;
    FILE *fpt;
    fpt = fopen("input_data/sphere_func_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file for reading \n");
        exit(0);
    }
    for (i=0; i<1; i++)
    {
        for (j=0; j<dim; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
            printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
    }
    fclose(fpt);
    bias[0] = -450.0L;

};
// CEC definitions end