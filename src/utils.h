//=========================================================================
// Copyright (C) 2021 The C++ Component Model(COMO) Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=========================================================================

#ifndef __UTILS_H__
#define __UTILS_H__

#include <pybind11/stl.h>

namespace py = pybind11;

std::map<std::string, py::object> constantsToMap(Array<IMetaConstant*> &constants);

void breakSignature(String &signature, std::vector<std::string> &signatureVector);

#endif
