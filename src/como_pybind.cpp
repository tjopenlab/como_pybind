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

static py::module_ *this_pymodule = nullptr;
//static std::map<std::string, py::class_<ComoPyClassStub>*> como_classes;
static std::map<std::string, std::shared_ptr<ComoPyClassStub>> como_classes;

PYBIND11_MODULE(como_pybind, m) {
    this_pymodule = &m;

    py::class_<ComoPyClassStub>(m, "ComoPyClassStub")
        .def(py::init([](const std::string &str_) {
            ComoPyClassStub* stub = new ComoPyClassStub(str_);
            std::shared_ptr<ComoPyClassStub> stub_(stub);
            como_classes.insert(std::pair<std::string, std::shared_ptr<ComoPyClassStub>>(str_, stub_));
            return stub;
        }));

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
