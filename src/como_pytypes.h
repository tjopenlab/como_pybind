#ifndef __COMO_PYTYPES_H__
#define __COMO_PYTYPES_H__

#include <comoapi.h>

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

    int funExample();
    ECode method1() {
        IArgumentList* argList;
        return methods[1]->Invoke(thisObject, argList);
    }

private:
    std::string className;
    Array<IMetaMethod*> methods;
    AutoPtr<IInterface> thisObject;
};

namespace py = pybind11;

using T_COMO_PYCLASS = py::class_<ComoPyClassStub>;
using TS_COMO_PYCLASS = std::shared_ptr<T_COMO_PYCLASS>;
using TMAP_COMO_PYCLASSES = std::map<std::string, TS_COMO_PYCLASS>;

// alias<std::string[]>{"hi", "there"};
template<class T>
using alias = T;

#endif
