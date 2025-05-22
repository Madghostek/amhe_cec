#include "global.h"
#include "math.h"
#include <stdlib.h>
extern int nreal;

void cec2005_f1_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
        double z = x[i] - o[0][i];
        gradient[i] = 2.0 * z;  // d/dz (z^2) is 2z
    }
}

void cec2005_f2_grad(double* x, double* gradient)
{
    for (int k = 0; k < nreal; ++k) {
        double ksum = 0;
        for (int i = k; i<nreal; ++i){
            for (int j=0;j<i;++j){
                ksum+=x[j];
            }
        }
        gradient[k] = 2*ksum;
    }
}

void cec2005_f3_grad(double* x, double* gradient)
{
    // Initialize gradient to zero
    for (int i = 0; i < nreal; ++i) {
        gradient[i] = 0.0;
    }

    for (int j = 0; j < nreal; ++j) {
        // Compute z_j = sum_k (x[k] - o[k]) * M[k][j]
        double z_j = 0.0;
        for (int k = 0; k < nreal; ++k) {
            z_j += (x[k] - o[0][k]) * g[k][j];
        }

        // Apply Lambda scaling: lambda_j = (10^6)^((j)/(D-1))
        double lambda_j = pow(1e6, (double)j / (nreal - 1));
        double scaled = lambda_j * z_j;

        // Accumulate into gradient: gradient[i] += 2 * M[i][j] * scaled
        for (int i = 0; i < nreal; ++i) {
            gradient[i] += 2.0 * g[i][j] * scaled;
        }
    }
}

void cec2005_f4_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
    }
}
void cec2005_f5_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
    }
}
void cec2005_f6_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
    }
}
void cec2005_f7_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
    }
}
void cec2005_f8_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
    }
}
void cec2005_f9_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
    }
}
void cec2005_f10_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
    }
}
void cec2005_f11_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
    }
}
void cec2005_f12_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
    }
}
void cec2005_f13_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
    }
}
void cec2005_f14_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
    }
}
void cec2005_f15_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
    }
}
void cec2005_f16_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
    }
}
void cec2005_f17_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
    }
}
void cec2005_f18_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
    }
}
void cec2005_f19_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
    }
}
void cec2005_f20_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
    }
}
void cec2005_f21_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
    }
}
void cec2005_f22_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
    }
}
void cec2005_f23_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
    }
}
void cec2005_f24_f25_grad(double* x, double* gradient)
{
    for (int i = 0; i < nreal; ++i) {
    }
}