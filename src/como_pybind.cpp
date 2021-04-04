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

PYBIND11_MODULE(como_pybind, m) {
    this_pymodule = &m;

    // this_pymodule->ptr() ==> return data type: handle
    // py::class_<MetaComponent> clz2 = py::class_<MetaComponent>(this_pymodule->ptr(), "MetaComponent");

    // load COMO component meta data
    py::class_<MetaComponent> pymc = py::class_<MetaComponent>(m, "MetaComponent");
    pymc.def(py::init([m](const std::string &str_) {
            MetaComponent* stub = new MetaComponent(str_);
            for (int i = 0;  i < stub->classNum;  i++) {
                char buf[32];
                sprintf(buf, "ComoPyClassStub%d", i);

                AutoPtr<IInterface> thisObject = stub->metaCoclass[i].CreateObject();

                py::class_<ComoPyClassStub> clz1 = py::class_<ComoPyClassStub>(m, buf)
                    .def(py::init([thisObject](const std::string &str_) {

                        AutoPtr<IInterface> thisObject_(thisObject);

                        ComoPyClassStub* stub = new ComoPyClassStub(str_, thisObject_);
                        return stub;
                    }));
                TS_COMO_PYCLASS stub_(&clz1);
                std::string str_1(buf);
                stub->como_classes.insert(std::pair<std::string, TS_COMO_PYCLASS>(str_1, stub_));
                /*
                TS_COMO_PYCLASS clz0;
                TMAP_COMO_PYCLASSES::const_iterator pos = stub->como_classes.find("className");
                if (pos == stub->como_classes.end()) {
                    //handle the error
                } else {
                    clz0 = pos->second;
                }
                */

                for (int j = 0;  j < stub->interfaceNum; j++) {
                    sprintf(buf, "method%d", i);
                    clz1.def(buf, &ComoPyClassStub::method1);
                }
            }
            return stub;
        }))
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
