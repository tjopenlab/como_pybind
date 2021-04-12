#ifndef __COMO_PYTYPES_H__
#define __COMO_PYTYPES_H__

#include <comoapi.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

class ComoArrayIMetaConstant {
public:
    ComoArrayIMetaConstant(Array<IMetaConstant*>& arr_) : arr(arr_) {}

private:
    Array<IMetaConstant*> arr;
};

class ComoPyClassStub {
public:
    ComoPyClassStub(AutoPtr<IInterface> thisObject_);

#define LAMBDA_FOR_METHOD(_NO_)                             \
    py::tuple m##_NO_(py::args args, py::kwargs kwargs) {   \
        return methodimpl(_NO_, args, kwargs);              \
    }

#include "LAMBDA_FOR_METHOD.inc"
#undef LAMBDA_FOR_METHOD

private:
    py::tuple methodimpl(int idxMethod, py::args args, py::kwargs kwargs);

    std::string className;
    Array<IMetaMethod*> methods;
    AutoPtr<IInterface> thisObject;
};

#endif
