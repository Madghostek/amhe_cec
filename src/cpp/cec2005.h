#pragma once
#ifndef _H_CEC2005
#define _H_CEC2005
#include <vector>
#include <limits>

long double cec2005_f1_eval(const long double* x, int n);
void cec2005_f1_grad(const long double* x, long double* gradient, int n);
void cec2005_f1_init(int dim);

#endif