cmake_minimum_required(VERSION 3.15...3.27)
project(amhe_cec)

if (NOT SKBUILD)
  message(WARNING "\
  This CMake file is meant to be executed using 'scikit-build-core'.
  Running it directly will almost certainly not produce the desired
  result. If you are a user trying to install this package, use the
  command below, which will install all necessary build dependencies,
  compile the package in an isolated environment, and then install it.
  =====================================================================
   $ pip install .
  =====================================================================
  If you are a software developer, and this is your own package, then
  it is usually much more efficient to install the build dependencies
  in your environment once and use the following command that avoids
  a costly creation of a new virtual environment at every compilation:
  =====================================================================
   $ pip install nanobind scikit-build-core[pyproject]
   $ pip install --no-build-isolation -ve .
  =====================================================================
  You may optionally add -Ceditable.rebuild=true to auto-rebuild when
  the package is imported. Otherwise, you need to rerun the above
  after editing C++ files.")
endif()

find_package(Python 3.8
  REQUIRED COMPONENTS Interpreter Development.Module
  OPTIONAL_COMPONENTS Development.SABIModule)

find_package(nanobind CONFIG REQUIRED)

# amhe_cec stuff

nanobind_add_module(
  _amhe_cec_impl
  STABLE_ABI 
  # main bindings factory
  src/cpp/bindings.cpp 
  # 2005
  src/cpp/cec2005/gradients.cpp 
  src/cpp/cec2005/rand.cpp 
  src/cpp/cec2005/misc.cpp 
  src/cpp/cec2005/inits.cpp 
  src/cpp/cec2005/basic.cpp 
  src/cpp/cec2005/implementations.cpp 
  src/cpp/cec2005/cec2005_allocate.cpp 
  # 2017
  src/cpp/cec2017/implementations.cpp
  src/cpp/cec2017/gradients.cpp 
  src/cpp/cec2017/Compare_fast.cpp)

nanobind_add_stub(
  amhe_cec_stub
  MODULE _amhe_cec_impl
  OUTPUT ${PROJECT_BINARY_DIR}/_amhe_cec_impl.pyi
  #  MARKER_FILE py.typed
  PYTHON_PATH $<TARGET_FILE_DIR:_amhe_cec_impl>
  DEPENDS _amhe_cec_impl)

add_compile_options(-Wno-unused-result)

install(TARGETS _amhe_cec_impl LIBRARY DESTINATION amhe_cec)
install(FILES ${PROJECT_BINARY_DIR}/_amhe_cec_impl.pyi DESTINATION "./amhe_cec")

# copy generated file to src/amhe_cec as well
install(FILES ${PROJECT_BINARY_DIR}/_amhe_cec_impl.pyi DESTINATION "${PROJECT_SOURCE_DIR}/src/amhe_cec")

