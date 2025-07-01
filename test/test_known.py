import amhe_cec.benchmark
import pytest
import numpy as np


def test_sphere_2005():
    b = amhe_cec.benchmark.BenchmarkFactory.get("cec2005",1,5)
    vector = np.array([0,0,0,0,0])
    val,grad = b.evaluate(vector), b.gradient(vector)

    # the benchmark is shifted, so these are the correct values
    assert val == pytest.approx(12565.46481572)
    assert grad == pytest.approx([78.6238, -117.7998, 92.6448, 149.303, 33.5994])
