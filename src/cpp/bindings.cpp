#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/string.h> // needed for std::string conversion
#include <nanobind/stl/vector.h>
#include <vector>
#include <iostream>
#include "benchmark_handle.h"
#include "create_benchmark.h"

namespace nb = nanobind;

class PyBenchmark{
    BenchmarkHandle* handle;

    public:
    PyBenchmark(std::string suite, int func_id, int dim) {
        handle = create_benchmark(suite.c_str(), func_id, dim);
    }

    long double evaluate(nb::ndarray<const double> x) const {
        std::vector<long double> x_ld(handle->dim);
        for (int i = 0; i < handle->dim; ++i){
            x_ld[i] = static_cast<long double>(x.data()[i]);
        }
        auto val = handle->evaluate(x_ld.data(), handle->dim);
        return val;
    }

    std::vector<double> gradient(nb::ndarray<const double> x) {
        std::vector<long double> x_ld(handle->dim);
        std::vector<double> grad_double(handle->dim);
        std::vector<long double> grad(handle->dim);
        for (int i = 0; i < handle->dim; ++i)
            x_ld[i] = static_cast<long double>(x.data()[i]);
        handle->gradient(x_ld.data(), grad.data(), handle->dim);
        for (int i = 0; i < handle->dim; ++i)
            grad_double[i] = static_cast<double>(grad.data()[i]);
        return grad_double;
    }

    ~PyBenchmark() {
        free(handle);
    }
};

NB_MODULE(_amhe_cec_impl, m) {
    nb::class_<PyBenchmark>(m, "Benchmark")
        .def(nb::init<std::string, int, int>())
        .def("evaluate", &PyBenchmark::evaluate) // use pointers to C functions here for speed 
        .def("gradient", &PyBenchmark::gradient);
}