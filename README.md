# AMHE-CEC

## Dev setup

```bash
python3 -m venv .venv
.venv/bin/activate              # or adequate to your shell
pip install -r requirements.txt
pip install .                   # build and install library to site-packages (requires g++)
```

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

