from typing import Annotated

from numpy.typing import ArrayLike


class Benchmark:
    def __init__(self, arg0: str, arg1: int, arg2: int, /) -> None: ...

    def evaluate(self, arg: Annotated[ArrayLike, dict(dtype='float64')], /) -> float: ...

    def gradient(self, arg: Annotated[ArrayLike, dict(dtype='float64')], /) -> list[float]: ...
