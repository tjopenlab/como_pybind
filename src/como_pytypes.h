#ifndef __COMO_PYTYPES_H__
#define __COMO_PYTYPES_H__

#include <comoapi.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

class ComoPyClassStub {
public:
    ComoPyClassStub(AutoPtr<IMetaCoclass> mCoclass);
    ComoPyClassStub(AutoPtr<IMetaCoclass> mCoclass, AutoPtr<IInterface> thisObject_);

#define LAMBDA_FOR_METHOD(_NO_)                                 \
    py::tuple m##_NO_(py::args args, py::kwargs kwargs) {       \
        return methodimpl(methods[_NO_], args, kwargs, false);  \
    }

#include "LAMBDA_FOR_METHOD.inc"
#undef LAMBDA_FOR_METHOD

    std::map<std::string, py::object> GetAllConstants();
    py::tuple methodimpl(IMetaMethod *method, py::args args, py::kwargs kwargs, bool isConstructor);
    void refreshThisObject(AutoPtr<IMetaCoclass> mCoclass);

    AutoPtr<IInterface> thisObject;
    std::string className;

private:
    Array<IMetaMethod*> methods;
};

#endif
