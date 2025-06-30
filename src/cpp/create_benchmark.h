#include <cstring>
#include <iostream>
#include "cec2005/cec2005.h"
#include "benchmark_handle.h"
#include "cec2017/cec2017.h"
#include "string.h"

extern int nfunc;
extern int nreal;
extern bool allocated;

struct BenchmarkInfo {
    const char* suite;
    int func_id;
    InitFunc init;
    EvalFunc eval;
    GradFunc grad;
};

static const BenchmarkInfo benchmark_table[] = {
    {"cec2005", 1, initialize_f1, &calc_benchmark_func_f1, &cec2005_f1_grad},
    {"cec2005", 2, initialize_f2, &calc_benchmark_func_f2, &cec2005_f2_grad},
    {"cec2005", 3, initialize_f3, &calc_benchmark_func_f3, &cec2005_f3_grad},
    {"cec2005", 4, initialize_f4, &calc_benchmark_func_f4, &cec2005_f4_grad},
    {"cec2005", 5, initialize_f5, &calc_benchmark_func_f5, &cec2005_f5_grad},
    {"cec2005", 6, initialize_f6, &calc_benchmark_func_f6, &cec2005_f6_grad},
    {"cec2005", 7, initialize_f7, &calc_benchmark_func_f7, &cec2005_f7_grad},
    {"cec2005", 8, initialize_f8, &calc_benchmark_func_f8, &cec2005_f8_grad},
    {"cec2005", 9, initialize_f9, &calc_benchmark_func_f9, &cec2005_f9_grad},
    {"cec2005", 10, initialize_f10, &calc_benchmark_func_f10, &cec2005_f10_grad},
    {"cec2005", 11, initialize_f11, &calc_benchmark_func_f11, &cec2005_f11_grad},
    {"cec2005", 12, initialize_f12, &calc_benchmark_func_f12, &cec2005_f12_grad},
    {"cec2005", 13, initialize_f13, &calc_benchmark_func_f13, &cec2005_f13_grad},
    {"cec2005", 14, initialize_f14, &calc_benchmark_func_f14, &cec2005_f14_grad},
    {"cec2005", 15, initialize_f15, &calc_benchmark_func_f15, &cec2005_f15_grad},
    {"cec2005", 16, initialize_f16, &calc_benchmark_func_f16, &cec2005_f16_grad},
    {"cec2005", 17, initialize_f17, &calc_benchmark_func_f17, &cec2005_f17_grad},
    {"cec2005", 18, initialize_f18, &calc_benchmark_func_f18, &cec2005_f18_grad},
    {"cec2005", 19, initialize_f19, &calc_benchmark_func_f19, &cec2005_f19_grad},
    {"cec2005", 20, initialize_f20, &calc_benchmark_func_f20, &cec2005_f20_grad},
    {"cec2005", 21, initialize_f21, &calc_benchmark_func_f21, &cec2005_f21_grad},
    {"cec2005", 22, initialize_f22, &calc_benchmark_func_f22, &cec2005_f22_grad},
    {"cec2005", 23, initialize_f23, &calc_benchmark_func_f23, &cec2005_f23_grad},
    {"cec2005", 24, initialize_f24_f25, &calc_benchmark_func_f24_f25, &cec2005_f24_f25_grad},
    
    {"cec2017", 1, NULL, &calc_benchmark_func_f1_2017, &cec2017_f1_grad}
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

    // this needs to be setup before calling alloc!
    nfunc = 2;
    nreal = dim;
    if (!strcmp(suite, "cec2005"))
    {
        if (!allocated) {
            allocate_memory();
        }
    }


    // create the handle for python
    auto* h = new BenchmarkHandle();
    h->dim = dim; // needed during gradient calculation to know the size
    h->evaluate = info->eval;
    h->gradient = info->grad;
    std::string inputpath = std::string{"input_data/"} + suite;
    if (info->init) {
        info->init(inputpath.data()); // only certain functions need init
    }

    return h;
}