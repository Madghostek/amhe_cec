#pragma once
#ifndef CEC2017_H
#define CEC2017_H
#include "../common.h"

void cec17_test_func(double *x, double *f, int nx, int mx, int func_num);

double calc_benchmark_func_f1_2017(double*);
double calc_benchmark_func_f2_2017(double*);
double calc_benchmark_func_f3_2017(double*);
double calc_benchmark_func_f4_2017(double*);
double calc_benchmark_func_f5_2017(double*);
double calc_benchmark_func_f6_2017(double*);
double calc_benchmark_func_f7_2017(double*);
double calc_benchmark_func_f8_2017(double*);
double calc_benchmark_func_f9_2017(double*);
double calc_benchmark_func_f10_2017(double*);

extern void cec2017_f1_grad(double*, double*);
extern void cec2017_f2_grad(double*, double*);
void cec2017_f3_grad(double*, double*);
void cec2017_f4_grad(double*, double*);
void cec2017_f5_grad(double*, double*);
void cec2017_f6_grad(double*, double*);
void cec2017_f7_grad(double*, double*);
void cec2017_f8_grad(double*, double*);
void cec2017_f9_grad(double*, double*);
void cec2017_f10_grad(double*, double*);
#endif