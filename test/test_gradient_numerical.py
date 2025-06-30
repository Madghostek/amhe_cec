import numpy as np
from amhe_cec.benchmark import BenchmarkFactory
from amhe_cec._amhe_cec_impl import cec2005_disablerand, cec2005_enablerand
import pytest


# year, function, dimensions
test_data = [("cec2005",1,3),
             ("cec2005",2,3),
             ("cec2005",3,2),
             ("cec2005",4,3)]

def numerical_gradient(f, x, eps=1e-6):
    grad = np.zeros_like(x)
    for i in range(len(x)):
        x_eps_plus = x.copy()
        x_eps_minus = x.copy()
        x_eps_plus[i] += eps
        x_eps_minus[i] -= eps
        grad[i] = (f(x_eps_plus) - f(x_eps_minus)) / (2 * eps)
    return grad


@pytest.mark.parametrize("target_bench,target_func,dim",test_data)
def test_gradient_parametrised(target_bench,target_func, dim):
    print("Testing", target_bench, target_func, dim)

    x = np.random.random(dim)

    b = BenchmarkFactory.get(target_bench, target_func, dim)
 
    cec2005_disablerand() # disable randomness for numerical evaluation (one sample is stored)
    # don't remove this, otherwise randomness won't be initialized
    b.evaluate(x) # call the function first, in case there is randomness (2005 f4)


    true_grad = b.gradient(x)
    num_grad = numerical_gradient(b.evaluate,x)

    diff = np.linalg.norm(num_grad - true_grad)
    print("Difference (L2 norm):", diff)

    rel_error = diff / (np.linalg.norm(true_grad) + np.linalg.norm(num_grad))
    assert rel_error < 1e-6, "Gradient check failed!"+target_bench+", "+str(target_func)+", "+str(num_grad)+" "+str(true_grad)

    cec2005_enablerand() # restore