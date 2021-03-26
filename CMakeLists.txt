cmake_minimum_required(VERSION 3.4...3.18)
project(como_pybind)

set(OBJ_DIR $ENV{OUT_PATH})
set(BIN_DIR $ENV{BIN_PATH})
set(INC_DIR ${BIN_DIR}/inc)

find_library(LIB_comort comort.so)
# message(STATUS "LIB_comort = ${LIB_comort}")

include_directories(
    ./
    ${INC_DIR}
    )

add_subdirectory(pybind11)

add_library(como_pybind MODULE
#pybind11_add_module(como_pybind
#    src/py_test.cpp)
    src/como_bridge.cpp
    ${LIB_comort}
    src/como_pybind.cpp)

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(como_pybind PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})

target_link_libraries(como_pybind
            pybind11::module
            ${LIB_comort}
  )