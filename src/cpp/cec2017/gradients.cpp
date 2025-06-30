#include <stdio.h>
#include <cmath>
extern int g_nx;

// from cec17_test_func.cpp, compiler will figure it out
extern double *OShift,*M,*y,*z,*x_bound;
extern int ini_flag,n_flag,func_flag,*SS;
extern int s_flag, r_flag;

// transformations gradient wrapper from chain rule
void transform_backprop_grad(
    double* x, double* grad,
    void (*raw_grad_func)(double*, double*, int)
) {
    int nx = g_nx;

    int i, j;
    static double z[1000], y[1000], gz[1000];

    // Shift
    if (s_flag == 1) {
        for (i = 0; i < nx; i++) y[i] = x[i] - OShift[i];
    } else {
        for (i = 0; i < nx; i++) y[i] = x[i];
    }

    // Rotate
    if (r_flag == 1) {
        for (i = 0; i < nx; i++) {
            z[i] = 0.0;
            for (j = 0; j < nx; j++) {
                z[i] += M[i * nx + j] * y[j];
            }
        }
    } else {
        for (i = 0; i < nx; i++) z[i] = y[i];
    }

    // Compute raw gradient
    raw_grad_func(z, gz, nx);

    // Transform gradient back
    if (r_flag == 1) {
        for (i = 0; i < nx; i++) {
            grad[i] = 0.0;
            for (j = 0; j < nx; j++) {
                grad[i] += M[j * nx + i] * gz[j];
            }
        }
    } else {
        for (i = 0; i < nx; i++) grad[i] = gz[i];
    }
}

void bent_cigar_raw_grad(double* z, double* gz, int nx)
{
    gz[0] = 2.0 * z[0];
    for (int i = 1; i < nx; i++) {
        gz[i] = 2.0e6 * z[i];
    }
}

void sum_diff_pow_raw_grad(double* z, double* gz, int nx)
{
    for (int i = 0; i < nx; i++) {
        double zi = z[i];
        if (zi == 0.0) {
            gz[i] = 0.0;
        } else {
            double abs_zi = fabs(zi);
            double sign = (zi > 0.0) ? 1.0 : -1.0;
            gz[i] = (i + 1) * sign * pow(abs_zi, i);
        }
    }
}

void cec2017_f1_grad(double* x, double* grad)
{
    transform_backprop_grad(x, grad, bent_cigar_raw_grad);
}

void cec2017_f2_grad(double* x, double* grad)
{
    transform_backprop_grad(x, grad, sum_diff_pow_raw_grad);
}