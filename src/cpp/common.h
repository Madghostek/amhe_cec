#pragma once
#include "benchmark_handle.h"

using EvalFunc = double(*)(double*);
using GradFunc = void(*)(double*, double*);
using InitFunc = void(*)(const char* data_source);
