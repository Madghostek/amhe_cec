#ifndef _H_BENCHMARK_HANDLE
#define _H_BENCHMARK_HANDLE
#include "common.h"

typedef struct {
    int dim;
    EvalFunc evaluate;
    GradFunc gradient;
} BenchmarkHandle;

#endif