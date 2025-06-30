#pragma once
#ifndef _H_CEC2005
#define _H_CEC2005
#include "../common.h" // somehow this line isn't needed, C magic
#include <vector>
#include <limits>

double calc_benchmark_func_f1(double*);
double calc_benchmark_func_f2(double*);
double calc_benchmark_func_f3(double*);
double calc_benchmark_func_f4(double*);
double calc_benchmark_func_f5(double*);
double calc_benchmark_func_f6(double*);
double calc_benchmark_func_f7(double*);
double calc_benchmark_func_f8(double*);
double calc_benchmark_func_f9(double*);
double calc_benchmark_func_f10(double*);
double calc_benchmark_func_f11(double*);
double calc_benchmark_func_f12(double*);
double calc_benchmark_func_f13(double*);
double calc_benchmark_func_f14(double*);
double calc_benchmark_func_f15(double*);
double calc_benchmark_func_f16(double*);
double calc_benchmark_func_f17(double*);
double calc_benchmark_func_f18(double*);
double calc_benchmark_func_f19(double*);
double calc_benchmark_func_f20(double*);
double calc_benchmark_func_f21(double*);
double calc_benchmark_func_f22(double*);
double calc_benchmark_func_f23(double*);
double calc_benchmark_func_f24_f25(double*);

void cec2005_f1_grad(double*, double*);
void cec2005_f2_grad(double*, double*);
void cec2005_f3_grad(double*, double*);
void cec2005_f4_grad(double*, double*);
void cec2005_f5_grad(double*, double*);
void cec2005_f6_grad(double*, double*);
void cec2005_f7_grad(double*, double*);
void cec2005_f8_grad(double*, double*);
void cec2005_f9_grad(double*, double*);
void cec2005_f10_grad(double*, double*);
void cec2005_f11_grad(double*, double*);
void cec2005_f12_grad(double*, double*);
void cec2005_f13_grad(double*, double*);
void cec2005_f14_grad(double*, double*);
void cec2005_f15_grad(double*, double*);
void cec2005_f16_grad(double*, double*);
void cec2005_f17_grad(double*, double*);
void cec2005_f18_grad(double*, double*);
void cec2005_f19_grad(double*, double*);
void cec2005_f20_grad(double*, double*);
void cec2005_f21_grad(double*, double*);
void cec2005_f22_grad(double*, double*);
void cec2005_f23_grad(double*, double*);
void cec2005_f24_f25_grad(double*, double*);

void initialize_f1(const char* data_path);
void initialize_f2(const char* data_path);
void initialize_f3(const char* data_path);
void initialize_f4(const char* data_path);
void initialize_f5(const char* data_path);
void initialize_f6(const char* data_path);
void initialize_f7(const char* data_path);
void initialize_f8(const char* data_path);
void initialize_f9(const char* data_path);
void initialize_f10(const char* data_path);
void initialize_f11(const char* data_path);
void initialize_f12(const char* data_path);
void initialize_f13(const char* data_path);
void initialize_f14(const char* data_path);
void initialize_f15(const char* data_path);
void initialize_f16(const char* data_path);
void initialize_f17(const char* data_path);
void initialize_f18(const char* data_path);
void initialize_f19(const char* data_path);
void initialize_f20(const char* data_path);
void initialize_f21(const char* data_path);
void initialize_f22(const char* data_path);
void initialize_f23(const char* data_path);
void initialize_f24_f25(const char* data_path);
void allocate_memory();

#endif