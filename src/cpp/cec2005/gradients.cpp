#include "global.h"
#include "math.h"
#include <stdlib.h>
#include <stdio.h>
extern int nreal;


typedef void (*basic_func_grad_t)(double* z, double* grad_z);

// only for f1-f15, because there is only one transform.
// first caltulates gradient (on transformed coords),
// then from chain rule adds influence of the matrices
void evaluate_transformed_gradient(double* x, double* grad, 
                                   basic_func_grad_t basic_grad)
{
    int i, j, k;
    double* grad_z = (double*)malloc(nreal * sizeof(double));

    transform(x, 0);

    basic_grad(trans_x, grad_z); 

    for (i = 0; i < nreal; i++) {
        grad[i] = 0.0;
        for (j = 0; j < nreal; j++) {
            for (k = 0; k < nreal; k++) {
                grad[i] += (1.0 / lambda[0]) * g[i][k] * l[0][k][j] * grad_z[j];
            }
        }
    }

    free(grad_z);
}

// this doesn't need the wrapper
void cec2005_f1_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        double z = x[i] - o[0][i];
        gradient[i] = 2.0 * z;  // d/dz (z^2) is 2z
    }
}

void cec2005_f2_grad_inner(double* x, double* grad)
{
    double *S = (double *)malloc(nreal * sizeof(double));

    S[0] = x[0];
    for (int i = 1; i < nreal; i++) {
        S[i] = S[i - 1] + x[i];
    }

    for (int i = 0; i < nreal; i++) {
        grad[i] = 0.0;
        for (int j = i; j < nreal; j++) {
            grad[i] += 2.0 * S[j];
        }
    }

    free(S);
}

void cec2005_f2_grad(double* x, double* grad)
{
    evaluate_transformed_gradient(x,grad,cec2005_f2_grad_inner);
}

void cec2005_f3_grad_inner(double* x, double* gradient)
{
    for (int j = 0; j < nreal; ++j) {
        double z_j = 0.0;
        for (int k = 0; k < nreal; ++k) {
            z_j += (x[k] - o[0][k]) * g[k][j];
        }

        double lambda_j = pow(1e6, (double)j / (nreal - 1));
        double scaled = lambda_j * z_j;

        for (int i = 0; i < nreal; ++i) {
            gradient[i] += 2.0 * g[i][j] * scaled;
        }
    }
}

void cec2005_f3_grad(double* x, double* grad)
{
    for (int i = 0; i < nreal; ++i)
        grad[i] = 0.0;

    for (int j = 0; j < nreal; ++j) {
        double z_j = 0.0;
        for (int k = 0; k < nreal; ++k) {
            z_j += (x[k] - o[0][k]) * g[k][j];
        }

        double lambda_j = pow(1e6, (double)j / (nreal - 1));
        double coeff = 2.0 * lambda_j * z_j;

        for (int i = 0; i < nreal; ++i) {
            grad[i] += coeff * g[i][j];
        }
    }
}

void schwefel_grad_inner(double* z, double* grad_z)
{
    // Schwefel function: sum_{i=1}^n (sum_{j=1}^i z_j)^2
    for (int i = 0; i < nreal; ++i)
        grad_z[i] = 0.0;

    for (int i = 0; i < nreal; ++i) {
        double partial_sum = 0.0;
        for (int j = 0; j <= i; ++j)
            partial_sum += z[j];

        for (int j = 0; j <= i; ++j)
            grad_z[j] += 2.0 * partial_sum;
    }
}

extern double cached_noise_f4;

void cec2005_f4_grad(double* x, double* grad)
{

    //transform(x, 0); // recompute transform because noise is ouf of sync!!!

    double coeff = 1.0 + 0.4 * cached_noise_f4;
    
    printf("[gradient f4] cached_noise_f4 = %.10f\n", cached_noise_f4);

    evaluate_transformed_gradient(x, grad, schwefel_grad_inner);

    // Scale gradient by the noise coefficient
    for (int i = 0; i < nreal; ++i)
        grad[i] *= coeff;
}

extern double **A_f5;
extern double *B_f5;

void cec2005_f5_grad(double* x, double* grad)
{
    int i, j;
    double max_val = -INFINITY;
    int i_max = -1;

    // Find the index i_max where the maximum occurs
    for (i = 0; i < nreal; ++i) {
        double dot = 0.0;
        for (j = 0; j < nreal; ++j) {
            dot += A_f5[i][j] * x[j];
        }
        double val = fabs(dot - B_f5[i]);

        if (val > max_val) {
            max_val = val;
            i_max = i;
        }
    }

    // Compute the gradient w.r.t. x
    double sign = 0.0;
    double dot = 0.0;
    for (j = 0; j < nreal; ++j)
        dot += A_f5[i_max][j] * x[j];

    if (dot - B_f5[i_max] > 0)
        sign = 1.0;
    else if (dot - B_f5[i_max] < 0)
        sign = -1.0;
    else
        sign = 0.0;  // non-differentiable point — could return 0 or subgradient

    for (j = 0; j < nreal; ++j)
        grad[j] = sign * A_f5[i_max][j];
}


void rosenbrock_grad_inner(double* x, double* grad)
{
    for (int i = 0; i < nreal; ++i)
        grad[i] = 0.0;

    for (int i = 0; i < nreal - 1; ++i) {
        double xi = x[i];
        double xi1 = x[i + 1];
        grad[i] += -400.0 * (xi1 - xi * xi) * xi + 2.0 * (xi - 1.0);
        grad[i + 1] += 200.0 * (xi1 - xi * xi);
    }
}

void cec2005_f6_grad(double* x, double* grad)
{
    evaluate_transformed_gradient(x, grad, rosenbrock_grad_inner);
}


void griewank_grad_inner(double* x, double* grad)
{
    int i;
    double sum = 0.0;
    double prod = 1.0;

    for (i = 0; i < nreal; ++i) {
        sum += x[i] * x[i];
        prod *= cos(x[i] / sqrt(i + 1));  // i + 1 to match 1-based index
    }

    for (i = 0; i < nreal; ++i) {
        double xi = x[i];
        double sqrt_i = sqrt(i + 1);  // 1-based
        double cos_term = cos(xi / sqrt_i);
        double sin_term = sin(xi / sqrt_i);

        grad[i] = (2.0 * xi) / 4000.0 + prod * sin_term / (sqrt_i * cos_term);
    }
}

void cec2005_f7_grad(double* x, double* grad)
{
    evaluate_transformed_gradient(x, grad, griewank_grad_inner);
}


void ackley_grad_inner(double* x, double* grad)
{
    double sum_sq = 0.0;
    double sum_cos = 0.0;
    const double pi2 = 2.0 * M_PI;

    for (int i = 0; i < nreal; ++i) {
        sum_sq += x[i] * x[i];
        sum_cos += cos(pi2 * x[i]);
    }

    double inv_n = 1.0 / nreal;
    double sqrt_sum_sq = sqrt(sum_sq * inv_n);
    double exp1 = exp(-0.2 * sqrt_sum_sq);
    double exp2 = exp(sum_cos * inv_n);

    for (int i = 0; i < nreal; ++i) {
        double term1 = 0.0;
        if (sqrt_sum_sq > 1e-10) {
            term1 = 4.0 * x[i] * exp1 / (nreal * sqrt_sum_sq);
        }

        double term2 = (2.0 * M_PI / nreal) * sin(pi2 * x[i]) * exp2;

        grad[i] = term1 + term2;
    }
}

void cec2005_f8_grad(double* x, double* grad)
{
    evaluate_transformed_gradient(x, grad, ackley_grad_inner);
}

void rastrigin_grad_inner(double* x, double* grad)
{
    const double pi2 = 2.0 * M_PI;

    for (int i = 0; i < nreal; ++i) {
        double xi = x[i];
        grad[i] = 2.0 * xi + 20.0 * M_PI * sin(pi2 * xi);
    }
}

void cec2005_f9_grad(double* x, double* grad)
{
    evaluate_transformed_gradient(x, grad, rastrigin_grad_inner);
}


// same as f9?
void cec2005_f10_grad(double* x, double* grad)
{
    evaluate_transformed_gradient(x, grad, rastrigin_grad_inner);
}

void weierstrass_grad_inner(double* x, double* grad)
{
    const double a = 0.5;
    const double b = 3.0;
    const int k_max = 20;

    for (int i = 0; i < nreal; ++i) {
        double sum = 0.0;
        for (int j = 0; j <= k_max; ++j) {
            double ak = pow(a, j);
            double bk = pow(b, j);
            double angle = 2.0 * PI * bk * (x[i] + 0.5);
            sum += -2.0 * PI * ak * bk * sin(angle);
        }
        grad[i] = sum;
    }
}

void cec2005_f11_grad(double* x, double* grad)
{
    evaluate_transformed_gradient(x, grad, weierstrass_grad_inner);
}


void cec2005_f12_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        gradient[i]=0;
    }
}
void cec2005_f13_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        gradient[i]=0;
    }
}
void cec2005_f14_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        gradient[i]=0;
    }
}
void cec2005_f15_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        gradient[i]=0;
    }
}
void cec2005_f16_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        gradient[i]=0;
    }
}
void cec2005_f17_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        gradient[i]=0;
    }
}
void cec2005_f18_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        gradient[i]=0;
    }
}
void cec2005_f19_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        gradient[i]=0;
    }
}
void cec2005_f20_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        gradient[i]=0;
    }
}
void cec2005_f21_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        gradient[i]=0;
    }
}
void cec2005_f22_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        gradient[i]=0;
    }
}
void cec2005_f23_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        gradient[i]=0;
    }
}
void cec2005_f24_f25_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        gradient[i]=0;
    }
}