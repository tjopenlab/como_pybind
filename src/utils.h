
#ifndef __UTILS_H__
#define __UTILS_H__

#include <pybind11/stl.h>

namespace py = pybind11;

std::map<std::string, py::object> constantsToMap(Array<IMetaConstant*> &constants);

void breakSignature(String &signature, std::vector<std::string> &signatureVector);

#endif
