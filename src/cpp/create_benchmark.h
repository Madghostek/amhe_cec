#include <cstring>
#include <iostream>
#include "cec2005.h"
#include "benchmark_handle.h"

using InitFunc = void(*)(int dim);
struct BenchmarkInfo {
    const char* suite;
    int func_id;
    InitFunc init;
    EvalFunc eval;
    GradFunc grad;
};

static const BenchmarkInfo benchmark_table[] = {
    {"cec2005", 1, cec2005_f1_init, &cec2005_f1_eval, &cec2005_f1_grad},
    {"cec2005", 2, cec2005_f1_init, &cec2005_f1_eval, &cec2005_f1_grad},
    {"cec2005", 3, cec2005_f1_init, &cec2005_f1_eval, &cec2005_f1_grad},
};

BenchmarkHandle* create_benchmark(const char* suite, int func_id, int dim) {
    const BenchmarkInfo* info = nullptr;
    for (const auto& b : benchmark_table) {
        if (strcmp(suite,b.suite)==0 && func_id == b.func_id) {
            info = &b;
            break;
        }
    }
    if (!info) {
        throw std::runtime_error("Invalid suite or function ID");
    }

    // create the handle for python
    auto* h = new BenchmarkHandle();
    h->dim = dim;
    h->evaluate = info->eval;
    h->gradient = info->grad;
    if (info->init) {
        info->init(dim); // only certain functions need init
    }

    return h;
}