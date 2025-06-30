#include <stdio.h>
#include <cmath>
extern int g_nx;

// from cec17_test_func.cpp, compiler will figure it out
extern double *OShift,*M,*y,*z,*x_bound;
extern int ini_flag,n_flag,func_flag,*SS;
extern int s_flag, r_flag;

#define PI 3.1415926535897932384626433832795029


// transformations gradient wrapper from chain rule
void transform_backprop_grad(
    double* x, double* grad,
    void (*raw_grad_func)(double*, double*, int),
    double scale  // <-- new argument
) {
    int nx = g_nx;

    int i, j;
    static double z[1000], y[1000], gz[1000];

    // Apply shift and scale
    if (s_flag == 1) {
        for (i = 0; i < nx; i++) y[i] = (x[i] - OShift[i]) * scale;
    } else {
        for (i = 0; i < nx; i++) y[i] = x[i] * scale;
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

    // Compute raw gradient in z-space
    raw_grad_func(z, gz, nx);

    // Backprop through rotation
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

    // Backprop through scale
    for (i = 0; i < nx; i++) grad[i] *= scale;
}

// raw gradients
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

void zakharov_raw_grad(double* z, double* gz, int nx)
{
    double s = 0.0;
    for (int i = 0; i < nx; i++) {
        s += 0.5 * (i + 1) * z[i];
    }

    double s2 = s * s;
    double s3 = s2 * s;

    for (int i = 0; i < nx; i++) {
        double zi = z[i];
        double coeff = (i + 1);
        gz[i] = 2.0 * zi + coeff * s + 2.0 * coeff * s3;
    }
}

void rosenbrock_raw_grad(double* z, double* gz, int nx)
{
    double zi, zip1, zim1, ti, tiprev;

    // Shift z to origin
    double zs[1000];
    for (int i = 0; i < nx; i++) {
        zs[i] = z[i] + 1.0;
    }

    for (int i = 0; i < nx; i++) {
        if (i == 0) {
            zi = zs[i];
            zip1 = zs[i + 1];
            ti = zi * zi - zip1;
            gz[i] = 400.0 * ti * zi + 2.0 * (zi - 1.0);
        }
        else if (i < nx - 1) {
            zi = zs[i];
            zip1 = zs[i + 1];
            zim1 = zs[i - 1];
            ti = zi * zi - zip1;
            tiprev = zim1 * zim1 - zi;
            gz[i] = 400.0 * ti * zi + 2.0 * (zi - 1.0) - 200.0 * tiprev;
        }
        else { // i == nx - 1
            zim1 = zs[i - 1];
            tiprev = zim1 * zim1 - zs[i];
            gz[i] = -200.0 * tiprev;
        }
    }
}

void rastrigin_raw_grad(double* z, double* gz, int nx)
{
    for (int i = 0; i < nx; i++) {
        gz[i] = 2.0 * z[i] + 20.0 * M_PI * sin(2.0 * M_PI * z[i]);
    }
}

void schaffer_f6_raw_grad(double* y, double* grad, int nx)
{
    double dzdy[1000] = {0};  // stores ∂z/∂y_i
    double sum_z = 0.0;

    // Compute partials from each z_i = sqrt(s_i) * (1 + sin²(50 * s_i^0.1))
    for (int i = 0; i < nx - 1; i++) {
        double xi = y[i];
        double xi1 = y[i + 1];

        double si = xi * xi + xi1 * xi1;
        if (si == 0.0) si = 1e-20;  // avoid div by zero

        double sqrt_si = sqrt(si);
        double si_pow01 = pow(si, 0.1);
        double sin_term = sin(50.0 * si_pow01);
        double cos_term = cos(50.0 * si_pow01);

        double zi = sqrt_si * (1.0 + sin_term * sin_term);
        sum_z += zi;

        // Derivative dz_i/ds_i
        double dzi_dsi = (1.0 + sin_term * sin_term) * 0.5 / sqrt_si
                       + sqrt_si * 10.0 * sin_term * cos_term / pow(si, 0.9);

        // Chain rule: ∂z_i/∂x_j = dz/ds * ds/dx
        dzdy[i]     += dzi_dsi * 2.0 * xi;
        dzdy[i + 1] += dzi_dsi * 2.0 * xi1;
    }

    // f(y) = (sum_z)^2 / (n-1)^2
    // ∇f = 2 * sum_z / (n-1)^2 * ∇sum_z
    double fscale = 2.0 * sum_z / ((nx - 1) * (nx - 1));
    for (int i = 0; i < nx; i++) {
        grad[i] = fscale * dzdy[i];
    }
}

extern void rotatefunc (double *x, double *xrot, int nx,double *Mr);

void f7_func_grad(double* x, double* grad, int nx)
{
    double mu0 = 2.5, d = 1.0;
    double s = 1.0 - 1.0 / (2.0 * sqrt(nx + 20.0) - 8.2);
    double mu1 = -sqrt((mu0 * mu0 - d) / s);

    double tmpx[1000], z[1000], y[1000], rotated[1000];
    double tmp1 = 0.0, tmp2 = 0.0, penalty_sum = 0.0;
    double dtmp1[1000] = {0}, dtmp2[1000] = {0}, dpenalty[1000] = {0};
    double fx;

    // Step 1: shift
    for (int i = 0; i < nx; ++i)
        y[i] = (x[i] - OShift[i]) * 0.1;

    // Step 2: tmpx (scaling, flipping)
    for (int i = 0; i < nx; ++i) {
        tmpx[i] = 2.0 * y[i];
        if (OShift[i] < 0.0) tmpx[i] *= -1.0;
        z[i] = tmpx[i];  // save pre-rotation z
        tmpx[i] += mu0;
    }

    // Step 3: distances
    for (int i = 0; i < nx; ++i) {
        double d1 = tmpx[i] - mu0;
        double d2 = tmpx[i] - mu1;
        tmp1 += d1 * d1;
        tmp2 += d2 * d2;
    }
    tmp2 = tmp2 * s + d * nx;

    // Step 4: penalty term using rotated z
    rotatefunc(z, rotated, nx, M);
    for (int i = 0; i < nx; ++i)
        penalty_sum += cos(2.0 * PI * rotated[i]);

    fx = ((tmp1 < tmp2) ? tmp1 : tmp2) + 10.0 * (nx - penalty_sum);

    // === Now compute gradient ===

    // Partial derivatives w.r.t. tmpx
    for (int i = 0; i < nx; ++i) {
        double sign = (OShift[i] < 0.0) ? -1.0 : 1.0;
        double chain = 2.0 * sign * 2.0 * 0.1;  // d(tmpx)/dx

        double dval;
        if (tmp1 < tmp2) {
            dval = 2.0 * (tmpx[i] - mu0) * chain;
        } else {
            dval = 2.0 * (tmpx[i] - mu1) * s * chain;
        }
        grad[i] = dval;
    }

    // Now add penalty gradient: 10 * d/dx[ -sum cos(2pi * rotated_i) ]
    // drotated/dx = M * d(tmpx)/dx, where tmpx = ±2 * 0.1 * (x - OShift)

    for (int i = 0; i < nx; ++i) {
        double dsum = 0.0;
        for (int j = 0; j < nx; ++j) {
            double sign = (OShift[j] < 0.0) ? -1.0 : 1.0;
            double dtmpx_dxj = 2.0 * 0.1 * sign;
            double drot_dxij = M[i * nx + j] * dtmpx_dxj;

            dsum += 10.0 * 2.0 * PI * sin(2.0 * PI * rotated[i]) * drot_dxij;
        }
        grad[i] += dsum;
    }
}
extern double fast_pow(double x, int p);

void levy_raw_grad(double* z, double* grad, int nx)
{
    double w[1000];
    for (int i = 0; i < nx; i++) {
        w[i] = 1.0 + (z[i] - 1.0) / 4.0;
    }

    for (int i = 0; i < nx; i++) grad[i] = 0.0;

    // Term 1: sin^2(pi * w[0])
    {
        double wi = w[0];
        double dwi_dzi = 1.0 / 4.0;

        double sin_pi_wi = sin(PI * wi);
        double dterm = 2.0 * PI * sin_pi_wi * cos(PI * wi);  // d/dw sin^2(pi * w)
        grad[0] += dterm * dwi_dzi;
    }

    // Sum over intermediate terms
    for (int i = 0; i < nx - 1; i++) {
        double wi = w[i];
        double dwi_dzi = 1.0 / 4.0;
        double sin_term = sin(PI * wi + 1.0);
        double sin_sq = sin_term * sin_term;
        double d_sin_sq = 2.0 * PI * sin_term * cos(PI * wi + 1.0);

        double outer = 2.0 * (wi - 1.0) * (1.0 + 10.0 * sin_sq)
                     + fast_pow((wi - 1.0), 2) * 10.0 * d_sin_sq;

        grad[i] += outer * dwi_dzi;
    }

    // Final term: (w[n-1] - 1)^2 * (1 + sin^2(2π * w[n-1]))
    {
        int i = nx - 1;
        double wi = w[i];
        double dwi_dzi = 1.0 / 4.0;

        double sin2 = sin(2.0 * PI * wi);
        double sin_sq = sin2 * sin2;
        double d_sin_sq = 4.0 * PI * sin2 * cos(2.0 * PI * wi);

        double outer = 2.0 * (wi - 1.0) * (1.0 + sin_sq)
                     + fast_pow((wi - 1.0), 2) * d_sin_sq;

        grad[i] += outer * dwi_dzi;
    }
}

// increased precision due to very high conditioning 
void schwefel_raw_grad(double* z, double* grad, int nx)
{
    for (int i = 0; i < nx; i++)
    {
        long double zi = z[i] + 420.9687462275036;

        if (zi > 500.0 || zi < -500.0)
        {
            grad[i] = 0.0; // out of reasonable bounds, fallback to 0
            continue;
        }

        long double abs_zi = fabs(zi);
        long double sqrt_abs_zi = sqrt(abs_zi);
        long double sin_term = sin(sqrt_abs_zi);
        long double cos_term = cos(sqrt_abs_zi);

        long double dfdzi = -sin_term - (zi * cos_term) / (2.0 * sqrt_abs_zi);
        grad[i] = (double)dfdzi;
    }
}


void not_implemented(double* z, double* gz, int nx)
{
    return;
}


// higher level handlers
void cec2017_f1_grad(double* x, double* grad)
{
    transform_backprop_grad(x, grad, bent_cigar_raw_grad, 1.0);
}

void cec2017_f2_grad(double* x, double* grad)
{
    transform_backprop_grad(x, grad, sum_diff_pow_raw_grad, 1.0);
}

void cec2017_f3_grad(double* x, double* grad)
{
    transform_backprop_grad(x, grad, zakharov_raw_grad, 1.0);
}

// non-default scaling factors here
void cec2017_f4_grad(double* x, double* grad)
{
    transform_backprop_grad(x, grad, rosenbrock_raw_grad, 2.048 / 100.0);
}

void cec2017_f5_grad(double* x, double* grad)
{
    transform_backprop_grad(x, grad, rastrigin_raw_grad, 5.12 / 100.0);
}

// for some reason this is called f7 in code, beawre!!
// also, the original function seems to have a bug.
// The gradient is incorrect
void cec2017_f6_grad(double* x, double* grad)
{
    transform_backprop_grad(x, grad, schaffer_f6_raw_grad, 1.0);
}

void cec2017_f7_grad(double* x, double* grad)
{
    f7_func_grad(x, grad, g_nx);  // no wrapper because it's too crazy
}

void cec2017_f8_grad(double* x, double* grad)
{
    transform_backprop_grad(x, grad, rastrigin_raw_grad, 5.12/100.0);
}

void cec2017_f9_grad(double* x, double* grad)
{
    transform_backprop_grad(x, grad, levy_raw_grad, 1.0);
}

void cec2017_f10_grad(double* x, double* grad)
{
    transform_backprop_grad(x, grad, schwefel_raw_grad, 10.0);
}

#undef PI