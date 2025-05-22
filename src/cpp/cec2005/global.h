/* Global variable and function definitions */

#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <float.h>

/* Global Constants */
#define INF DBL_MAX
#define EPS 1.0e-10
#define E 2.7182818284590452353602874713526625
#ifdef PI
#undef PI
#endif
#define PI 3.1415926535897932384626433832795029

/* Global variables that you are required to initialize */
extern int nreal; /* number of real variables */
extern int nfunc; /* number of basic functions */
extern double bound; /* required for plotting the function profiles for nreal=2 */
extern int density; /* density of grid points for plotting for nreal=2 */

/* Global variables being used in evaluation of various functions */
extern double C;
extern double global_bias;
extern double *trans_x;
extern double *basic_f;
extern double *temp_x1;
extern double *temp_x2;
extern double *temp_x3;
extern double *temp_x4;
extern double *weight;
extern double *sigma;
extern double *lambda;
extern double *bias;
extern double *norm_x;
extern double *norm_f;
extern double **o;
extern double **g;
extern double ***l;

/* Auxilary function declarations */
double maximum(double, double);
double minimum(double, double);
double modulus(double*, int);
double dot(double*, double*, int);
double mean(double*, int);

/* Basic funcion declarations */
double calc_ackley(double*);
double calc_rastrigin(double*);
double calc_weierstrass(double*);
double calc_griewank(double*);
double calc_sphere(double*);
double calc_schwefel(double*);
double calc_rosenbrock(double *x);
double nc_schaffer(double, double);
double nc_rastrigin(double*);

/* Utility function declarations */
void transform(double*, int);
void transform_norm(int);
void calc_weight(double*);
void free_memory();

/* Benchmark function declaration */
void calc_benchmark_norm_f15();
void calc_benchmark_norm_f16();
void calc_benchmark_norm_f17();
void calc_benchmark_norm_f18();
void calc_benchmark_norm_f19();
void calc_benchmark_norm_f20();
void calc_benchmark_norm_f21();
void calc_benchmark_norm_f22();
void calc_benchmark_norm_f23();
void calc_benchmark_norm_f24_f25();

#endif
