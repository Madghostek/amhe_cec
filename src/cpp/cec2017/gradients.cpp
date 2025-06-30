extern int g_nx;

// from cec17_test_func.cpp, compiler will figure it out
extern double *OShift,*M,*y,*z,*x_bound;
extern int ini_flag,n_flag,func_flag,*SS;
extern int s_flag, r_flag;

double* Os = OShift;
double* Mr = M;

void cec2017_f1_grad(double* x, double* grad)
{
    int nx = g_nx;

    int i, j;
    static double z[1000], y[1000], gz[1000];

    // Step 1: Shift
    if (s_flag == 1) {
        for (i = 0; i < nx; i++)
            y[i] = x[i] - Os[i];
    } else {
        for (i = 0; i < nx; i++)
            y[i] = x[i];
    }

    // Step 2: Rotate if needed
    if (r_flag == 1) {
        for (i = 0; i < nx; i++) {
            z[i] = 0.0;
            for (j = 0; j < nx; j++) {
                z[i] += Mr[i * nx + j] * y[j];  // Mr is row-major
            }
        }
    } else {
        for (i = 0; i < nx; i++)
            z[i] = y[i];
    }

    // Step 3: Compute gradient in z-space
    gz[0] = 2.0 * z[0];
    for (i = 1; i < nx; i++) {
        gz[i] = 2.0e6 * z[i];
    }

    // Step 4: Transform gradient back to x-space: grad = M^T * gz
    if (r_flag == 1) {
        for (i = 0; i < nx; i++) {
            grad[i] = 0.0;
            for (j = 0; j < nx; j++) {
                grad[i] += Mr[j * nx + i] * gz[j];  // transpose of Mr
            }
        }
    } else {
        for (i = 0; i < nx; i++)
            grad[i] = gz[i];
    }
}