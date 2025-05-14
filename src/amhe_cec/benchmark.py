from typing import Dict, Tuple
from amhe_cec import Benchmark

class BenchmarkFactory:
    _instances: Dict[Tuple[str, int, int], Benchmark] = {} # don't recreate benchmarks if they exist

    @classmethod
    def get(cls, suite: str, func_id: int, dim: int) -> Benchmark:
        key = (suite, func_id, dim)

        if key not in cls._instances:
            print("[debug] making new instance")
            cls._instances[key] = Benchmark(suite, func_id, dim)

        return cls._instances[key]

    @classmethod
    def clear_cache(cls):
        """Clear all cached benchmark instances (useful for testing)."""
        cls._instances.clear()