from amhe_cec.benchmark import BenchmarkFactory
import numpy as np

input = np.array([0,0,0])

def test_singleton():
    b1 = BenchmarkFactory.get("cec2005", 1, 3)
    _ = b1.evaluate(input)

    b2 = BenchmarkFactory.get("cec2005", 1, 3)
    assert b1 is b2


def test_if_value_makes_sense():
    b = BenchmarkFactory.get("cec2005", 1, 3)
    val = b.evaluate(input)

    # assert np.allclose([0],val) # it's shifted

def test_sgd():
    dim = 3
    steps = 100
    lr = 0.1
    b = BenchmarkFactory.get("cec2005", 1, 3)
    x = np.random.randn(dim)  # random init
     
    for _ in range(steps):
        loss = b.evaluate(x)
        grad = b.gradient(x)
        x -= lr * np.array(grad)  # simple step
        print(f"Value: {loss:.5f}")