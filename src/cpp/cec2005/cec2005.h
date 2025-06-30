#pragma once
#ifndef _H_CEC2005
#define _H_CEC2005
#include "../common.h" // somehow this line isn't needed, C magic
#include <vector>
#include <limits>

EvalFunc calc_benchmark_func_f1;
EvalFunc calc_benchmark_func_f2;
EvalFunc calc_benchmark_func_f3;
EvalFunc calc_benchmark_func_f4;
EvalFunc calc_benchmark_func_f5;
EvalFunc calc_benchmark_func_f6;
EvalFunc calc_benchmark_func_f7;
EvalFunc calc_benchmark_func_f8;
EvalFunc calc_benchmark_func_f9;
EvalFunc calc_benchmark_func_f10;
EvalFunc calc_benchmark_func_f11;
EvalFunc calc_benchmark_func_f12;
EvalFunc calc_benchmark_func_f13;
EvalFunc calc_benchmark_func_f14;
EvalFunc calc_benchmark_func_f15;
EvalFunc calc_benchmark_func_f16;
EvalFunc calc_benchmark_func_f17;
EvalFunc calc_benchmark_func_f18;
EvalFunc calc_benchmark_func_f19;
EvalFunc calc_benchmark_func_f20;
EvalFunc calc_benchmark_func_f21;
EvalFunc calc_benchmark_func_f22;
EvalFunc calc_benchmark_func_f23;
EvalFunc calc_benchmark_func_f24_f25;

GradFunc cec2005_f1_grad;
GradFunc cec2005_f2_grad;
GradFunc cec2005_f3_grad;
GradFunc cec2005_f4_grad;
GradFunc cec2005_f5_grad;
GradFunc cec2005_f6_grad;
GradFunc cec2005_f7_grad;
GradFunc cec2005_f8_grad;
GradFunc cec2005_f9_grad;
GradFunc cec2005_f10_grad;
GradFunc cec2005_f11_grad;
GradFunc cec2005_f12_grad;
GradFunc cec2005_f13_grad;
GradFunc cec2005_f14_grad;
GradFunc cec2005_f15_grad;
GradFunc cec2005_f16_grad;
GradFunc cec2005_f17_grad;
GradFunc cec2005_f18_grad;
GradFunc cec2005_f19_grad;
GradFunc cec2005_f20_grad;
GradFunc cec2005_f21_grad;
GradFunc cec2005_f22_grad;
GradFunc cec2005_f23_grad;
GradFunc cec2005_f24_f25_grad;

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