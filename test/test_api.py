from amhe_cec.benchmark import BenchmarkFactory
import numpy as np

input = np.array([0,0,0])


def test_singleton():
    b1 = BenchmarkFactory.get("cec2005", 1, 3)
    _ = b1.evaluate(input)

    b2 = BenchmarkFactory.get("cec2005", 1, 3)
    assert b1 is b2