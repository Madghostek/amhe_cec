#pragma once

void allocate_memory(int);

constexpr double INF = std::numeric_limits<double>::max();
# define EPS 1.0e-10
# define E  2.7182818284590452353602874713526625
# define PI 3.1415926535897932384626433832795029

void transform (const long double *x, int count);

extern long double C;
extern long double global_bias;
extern long double *trans_x;
extern long double *basic_f;
extern long double *temp_x1;
extern long double *temp_x2;
extern long double *temp_x3;
extern long double *temp_x4;
extern long double *weight;
extern long double *sigma;
extern long double *lambda;
extern long double *bias;
extern long double *norm_x;
extern long double *norm_f;
extern long double **o;
extern long double **g;
extern long double ***l;