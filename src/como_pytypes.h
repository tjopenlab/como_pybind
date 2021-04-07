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
    ComoPyClassStub(const std::string &className_, AutoPtr<IInterface> thisObject_)
        : className(className_),
          thisObject(thisObject_)
        {}

    int methodimpl(ComoPyClassStub *thisObj, py::args args, py::kwargs kwargs) {
        IArgumentList* argList;
        return methods[1]->Invoke(thisObject, argList);
    }

    int m1(py::args args, py::kwargs kwargs) {}//method(1)}
private:
    std::string className;
    Array<IMetaMethod*> methods;
    AutoPtr<IInterface> thisObject;
};

namespace py = pybind11;

// alias<std::string[]>{"hi", "there"};
template<class T>
using alias = T;

#endif
