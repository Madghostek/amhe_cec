from amhe_cec.benchmark import BenchmarkFactory
import numpy as np
from torch.optim import Adam
import torch

input = np.array([0,0,0])


def test_singleton():
    b1 = BenchmarkFactory.get("cec2005", 1, 3)
    _ = b1.evaluate(input)

    b2 = BenchmarkFactory.get("cec2005", 1, 3)
    assert b1 is b2

# def test_sgd():
#     dim = 2
#     steps = 100
#     lr = 0.1
#     b = BenchmarkFactory.get("cec2005", 2, dim)
#     x = np.random.randn(dim)  # random init
     
#     for _ in range(steps):
#         print(x)
#         loss = b.evaluate(x)
#         grad = b.gradient(x)
#         x -= lr * np.array(grad)  # simple step
#         print(f"Value: {loss:.5f}\n")


# def test_adam():
#     dim = 2
#     steps = 100000
#     b = BenchmarkFactory.get("cec2005", 3, dim)
#     x = torch.from_numpy(np.random.randn(dim))  # random init

#     #print("cec2005 2 optimum at", b.evaluate(np.array([3.5626700e+001, -8.2912300e+001])))

#     optim = Adam([x],lr=0.1)
     
#     for step in range(steps):
#         loss = b.evaluate(x)
#         grad = b.gradient(x)
#         x._grad = torch.tensor(grad).double()
#         optim.step()
#         if not steps % 1000:
#             print("step",step)
#             print(x)
#             print(f"Value: {loss:.5f}\n")


# def test_cec2017():
#     b = BenchmarkFactory.get("cec2017", 1, 2)
#     x = torch.from_numpy(np.random.randn(2))  # random init
#     res = b.evaluate(x)
#     print(res)