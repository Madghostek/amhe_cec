#pragma once
#ifndef CEC2017_H
#define CEC2017_H
#include "../common.h"

void cec17_test_func(double *x, double *f, int nx, int mx, int func_num);

double calc_benchmark_func_f1_2017(double*);
extern EvalFunc calc_benchmark_func_f2_2017;
extern EvalFunc calc_benchmark_func_f3_2017;
extern EvalFunc calc_benchmark_func_f4_2017;
extern EvalFunc calc_benchmark_func_f5_2017;
extern EvalFunc calc_benchmark_func_f6_2017;
extern EvalFunc calc_benchmark_func_f7_2017;
extern EvalFunc calc_benchmark_func_f8_2017;
extern EvalFunc calc_benchmark_func_f9_2017;
extern EvalFunc calc_benchmark_func_f10_2017;

extern void cec2017_f1_grad(double*, double*);
extern GradFunc cec2017_f2_grad;
extern GradFunc cec2017_f3_grad;
extern GradFunc cec2017_f4_grad;
extern GradFunc cec2017_f5_grad;
extern GradFunc cec2017_f6_grad;
extern GradFunc cec2017_f7_grad;
extern GradFunc cec2017_f8_grad;
extern GradFunc cec2017_f9_grad;
extern GradFunc cec2017_f10_grad;
#endif