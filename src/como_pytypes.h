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
    ComoPyClassStub(const std::string &className_) : className(className_) {}

private:
    std::string className;
};

#endif
