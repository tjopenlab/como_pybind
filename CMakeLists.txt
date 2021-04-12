cmake_minimum_required(VERSION 3.4...3.18)
project(como_pybind)

set(OBJ_DIR $ENV{OUT_PATH})
set(BIN_DIR $ENV{BIN_PATH})
set(INC_DIR ${BIN_DIR}/inc)

find_library(LIB_comort comort.so "${BIN_DIR}")
# message(STATUS "LIB_comort = ${LIB_comort}")

include_directories(
    ./
    ${INC_DIR}
    pybind11/include
    )

add_subdirectory(pybind11)

# pybind11_add_module, no way to link with comort.so, so do with add_library
#pybind11_add_module(como_pybind
add_library(como_pybind MODULE
#    src/py_test.cpp)
    src/como_bridge.cpp
    src/utils.cpp
    ${LIB_comort}
    src/como_pybind.cpp)

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(como_pybind PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})

# output filename style: como_pybind.cpython-38-x86_64-linux-gnu.so
set_target_properties(como_pybind PROPERTIES PREFIX "" SUFFIX "${PYTHON_MODULE_EXTENSION}")

target_link_libraries(como_pybind PRIVATE
            pybind11::module
            ${LIB_comort}
  )
