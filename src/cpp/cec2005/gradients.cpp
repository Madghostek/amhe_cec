#include "global.h"
#include "math.h"
#include <stdlib.h>
extern int nreal;


// gradient wrapper
typedef void (*basic_func_grad_t)(double* z, double* grad_z);

// Generic wrapper
void evaluate_transformed_gradient(double* x, double* grad, int count, 
                                   basic_func_grad_t basic_grad)
{
    int i, j, k;
    double* grad_z = (double*)malloc(nreal * sizeof(double));

    // Step 1: Apply transform → trans_x
    transform(x, count);  // trans_x now holds z = l^T * g^T * (x - o) / lambda

    // Step 2: Compute gradient in transformed space
    basic_grad(trans_x, grad_z);  // ∇f(z)

    // Step 3: Apply chain rule: grad = J * grad_z = (1/λ) * g * l * grad_z
    for (i = 0; i < nreal; i++) {
        grad[i] = 0.0;
        for (j = 0; j < nreal; j++) {
            for (k = 0; k < nreal; k++) {
                grad[i] += (1.0 / lambda[count]) * g[i][k] * l[count][k][j] * grad_z[j];
            }
        }
    }

    free(grad_z);
}

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

    // Compute cumulative sums S[i] = sum_{j=0}^{i} x[j]
    S[0] = x[0];
    for (int i = 1; i < nreal; i++) {
        S[i] = S[i - 1] + x[i];
    }

    // Compute gradient
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
    evaluate_transformed_gradient(x,grad,0,cec2005_f2_grad_inner);
}



void cec2005_f3_grad(double* x, double* gradient)
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

void cec2005_f4_grad(double* x, double* gradient)
{
    for (int k = 0; k < nreal; ++k) {
        double ksum = 0;
        for (int i = k; i<nreal; ++i){
            for (int j=0;j<i;++j){
                ksum+=x[j] - o[0][i];
            }
        }
        gradient[k] = 2*ksum;
    }
}
void cec2005_f5_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        gradient[i]=0;
    }
}
void cec2005_f6_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        gradient[i]=0;
    }
}
void cec2005_f7_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        gradient[i]=0;
    }
}
void cec2005_f8_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        gradient[i]=0;
    }
}
void cec2005_f9_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        gradient[i]=0;
    }
}
void cec2005_f10_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        gradient[i]=0;
    }
}
void cec2005_f11_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        gradient[i]=0;
    }
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