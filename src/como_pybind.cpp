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

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <comoapi.h>
#include "como_bridge.h"

using namespace pybind11::literals;
namespace py = pybind11;

using namespace como;

using T_COMO_PYCLASS = py::class_<ComoPyClassStub>;
using TS_COMO_PYCLASS = std::shared_ptr<T_COMO_PYCLASS>;
using TMAP_COMO_PYCLASSES = std::map<std::string, TS_COMO_PYCLASS>;

static py::module_ *this_pymodule = nullptr;
static TMAP_COMO_PYCLASSES como_classes;

py::class_<MetaComponent> clz0 = py::class_<MetaComponent>(this_pymodule->ptr(), "MetaComponent");

PYBIND11_MODULE(como_pybind, m) {
    this_pymodule = &m;
    // this_pymodule->ptr() ==> return data type: handle

    for (int i = 0;  i < 10;  i++) {
        char buf[32];
        sprintf(buf, "ComoPyClassStub%d", i);

        py::class_<ComoPyClassStub> clz1 = py::class_<ComoPyClassStub>(m, buf)
            .def(py::init([](const std::string &str_) {
                ComoPyClassStub* stub = new ComoPyClassStub(str_);
                return stub;
            }));
        TS_COMO_PYCLASS stub_(&clz1);
        std::string str_1(buf);
        como_classes.insert(std::pair<std::string, TS_COMO_PYCLASS>(str_1, stub_));
    }

    for (int i = 0;  i < 10;  i++) {
        TMAP_COMO_PYCLASSES::const_iterator pos = como_classes.find("string");
        if (pos == como_classes.end()) {
            //handle the error
        } else {
            TS_COMO_PYCLASS value = pos->second;
        }

        char buf[32];
        sprintf(buf, "getName%d", i);
        clz0.def(buf, &MetaComponent::GetName);
    }

    py::class_<MetaComponent>(m, "MetaComponent")
        .def(py::init<const std::string &>())
        .def("getName", &MetaComponent::GetName)
        .def(
            "getConstant",
            [](MetaComponent& m) {
                return m.GetConstant();
            },
            py::return_value_policy::take_ownership)
        .def(
            "getAllConstants",
            [](MetaComponent& m) {
                return m.GetAllConstants();
            },
            py::return_value_policy::take_ownership)

        .def("__repr__",
            [](const MetaComponent &a) {
                return "<MetaComponent componentPath '" + a.componentPath + "'>";
            }
    );
}
