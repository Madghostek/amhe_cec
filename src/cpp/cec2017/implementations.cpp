#include "cec2017.h"

extern int nreal;

// smarter macro, since only one thing changes
#define DEFINE_CEC2017_FUNC(N) \
double calc_benchmark_func_f##N##_2017(double *x) \
{ \
    double f = 0; \
    cec17_test_func(x, &f, nreal, 1, N); \
    return f; \
}
DEFINE_CEC2017_FUNC(1)
DEFINE_CEC2017_FUNC(2)
DEFINE_CEC2017_FUNC(3)
DEFINE_CEC2017_FUNC(4)
DEFINE_CEC2017_FUNC(5)
DEFINE_CEC2017_FUNC(6)
DEFINE_CEC2017_FUNC(7)
DEFINE_CEC2017_FUNC(8)
DEFINE_CEC2017_FUNC(9)
DEFINE_CEC2017_FUNC(10)