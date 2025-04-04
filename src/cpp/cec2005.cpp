#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/tuple.h>
#include <cmath>

namespace nb = nanobind;

int n;

void init_benchmark(int dim) {
    n = dim;
}


using OutType = std::tuple<double, std::vector<double>>;

// CEC definitions
constexpr double a = 20.0, b = 0.2, c = 2.0 * M_PI;
OutType ackley(const std::vector<double>& x) {
    if (x.size() != n) {
        throw std::invalid_argument("Input vector size must match n.");
    }

    double sum1 = 0.0, sum2 = 0.0;
    for (int i = 0; i < n; ++i) {
        sum1 += x[i] * x[i];
        sum2 += cos(c * x[i]);
    }

    double term1 = -a * exp(-b * sqrt(sum1 / n));
    double term2 = -exp(sum2 / n);
    double value = term1 + term2 + a + M_E;

    std::vector<double> gradient(n);
    double grad_common_term1 = (a * b / n) * exp(-b * sqrt(sum1 / n)) / sqrt(sum1 / n);
    double grad_common_term2 = (c / n) * exp(sum2 / n);

    for (int i = 0; i < n; ++i) {
        gradient[i] = grad_common_term1 * 2.0 * x[i] + grad_common_term2 * sin(c * x[i]);
    }

    return {value, gradient};
}

OutType shifted_sphere(const std::vector<double>& x) {
    // placeholder
    double shift_vector[n] = {1.0, -1.5, 0.5, 2.0, -3.0, 4.0, -2.5, 3.5, -1.0, 0.0};
    if (x.size() != n) {
        throw std::invalid_argument("Input vector size must match n.");
    }

    double value = 0.0;
    std::vector<double> gradient(n);

    for (int i = 0; i < n; ++i) {
        double z = x[i] - shift_vector[i];
        value += z * z;
        gradient[i] = 2.0 * z;  // d/dz (z^2) is 2z
    }

    return {value, gradient};
}
// CEC definitions end

NB_MODULE(_amhe_cec_impl, m) {
    m.def("ackley", &ackley);
    m.def("init_benchmark", &init_benchmark);
    m.def("f1", &shifted_sphere, "CEC 2005 F1 - shifted sphere");
}
