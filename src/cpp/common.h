#pragma once
#include "benchmark_handle.h"

using EvalFunc = long double(*)(const long double*, int);
using GradFunc = void(*)(const long double*, long double*, int);