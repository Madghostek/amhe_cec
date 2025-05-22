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
    PyBenchmark(std::string suite, int func_id, int ndim) {
        handle = create_benchmark(suite.c_str(), func_id, ndim);
    }

    double evaluate(nb::ndarray<double> x) const {
        auto val = handle->evaluate(x.data());
        return val;
    }

    std::vector<double> gradient(nb::ndarray<double> x) {
        std::vector<double> grad(handle->dim);
        handle->gradient(x.data(), grad.data());
        return grad;
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