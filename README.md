# AMHE-CEC

## Usage

The package exposes a factory pattern that builds benchmark objects. Each object has an `.evaluate()` and `.gradient()` method. The simplest example is as follows:

```python

from amhe_cec import BenchmarkFactory
import numpy as np


target_bench = "cec2017"
target_func = 1
dim = 3
bench = BenchmarkFactory.get(target_bench, target_func, dim)

value = bench.evaluate(np.array([1,2,3]))
grad = bench.gradient(np.arrayt([1,2,3]))
```

See `test/test_gradient_numerical.py` for working example of comparing the gradient method with numerical gradient.

> [!NOTE] 
> Usually CEC benchmarks are defined only for certain dimensions. Check the original documentations. Invalid dimentions are usually reported and the executions stops, but the original implementations are buggy and sometimes segfault instead!

## Problems

Only a limited set of functions has it's gradients implemented:
* cec2005 f1 through f10
    * the composite functions require highly complicated chaining of gradients due to stacking of base functions and transformations inbetween.
* cec2017 f1 through f10, excluding f6 and f7
    * f10 is highly contitioned, therefore the numerical gradient differs substantially from analytical (about 0.1 relative error)
    * composite functions also turned out very hard to implement.

## Dev setup

```bash
python3 -m venv .venv
.venv/bin/activate              # or adequate to your shell
pip install -r requirements.txt
pip install -e .                   # build and install library to site-packages (requires g++)
```

after changing the c++ side, run `pip install -e .` to see the changes 

## Project structure
```
src/
    cpp/            # C++ CEC functions
    amhe_cec/       # python interface
        __init__.py # stub to import the compiled shared library

test/               # at least check if it imports and calling works
pyproject.toml      # project description and build backend
CMakeLists.txt      # building instructions for pip
```

## Adding new benchmarks

Currently there are first 10 functions from 2005 and 2017. To add another year, you can roughly follow these steps:

1. You should place your code in the `cpp` folder with new subdirectory for organisation purposes, but it's optional
2. Add any new source files to `CMakeLists.txt` in the root directory
3. To expose a function to be usable through `BenchmarkFactory` on python side, add new entries in `src/cpp/create_benchmark.h`. Include necessary headers
4. Optionally, if you need a new top-level function visible from the python package, modify `src/cpp/bindings.cpp` according to existing functions and nanobind documentation.

## Design choices

Problem 1: We want to have CEC benchmarks with gradient

-> Create a library that will expose for exmaple `amhe_cec.cec2005.xxx`

Problem 2: We need it to be fast

-> How fast? Is numpy enough?
-> Try to bridge C code with python

Problem 3: How to bridge C with Python?

* Python C api - hardest, but the most basic
* Cython - superset of python that compiles to C.
* pybind11 - simple bindings for C without manual python C api hassle, but has some overhead
* ctypes - loads a .dll or .so, then you give it the header
* CFFI - dynamically compiles C code in runtime, even form a string

Problem 4: What about portability?

* Python C api - python builds stuff on its own, complex setup
* Cython - no problem
* ctypes - loads a library by hand, so needs compilation scripts for each os...
* CFFI - no problem
* pybind11 - uses c++ therefore needs c++ compiler, so whatever


Summing up:
pybind - looks cool and integrates well with setup.py
CFFI - seems more like you inline the C code inside python and compile on the fly
ctypes - managing shared libraries ehhh
python C api - maybe cross platforming this wouldn't be so hard, but you need to write boilerplate

also pybind11 will give clean code, wanted for AMHE

therefore I choose... nanobind, a new (2022) replacement for pybind

Update: After finishing work on the project, I think choosing nanobind was a really good idea, no problems whatsoever.

