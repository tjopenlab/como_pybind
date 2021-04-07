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
static MetaComponent *metaComponent = nullptr;

PYBIND11_MODULE(como_pybind, m) {
    this_pymodule = &m;

    // this_pymodule->ptr() ==> return data type: handle
    // py::class_<MetaComponent> clz2 = py::class_<MetaComponent>(this_pymodule->ptr(), "MetaComponent");

    // load COMO component meta data
    py::class_<MetaComponent> pymc = py::class_<MetaComponent>(m, "MetaComponent");
    pymc.def(py::init([m](const std::string &str_) {
            metaComponent = new MetaComponent(str_);

            std::map<std::string, MetaCoclass*>::iterator iter;
            for(iter = metaComponent->como_classes.begin();  iter != metaComponent->como_classes.end();  iter++) {
                MetaCoclass *metaCoclass = iter->second;
                std::string className = std::string(metaCoclass->GetName());

                py::class_<ComoPyClassStub> clz_ = py::class_<ComoPyClassStub>(m, className.c_str())
                    .def(py::init([](const std::string &str_) {

                        // the MetaCoclass cann't be accepted from outer program,
                        // for these constructors are created dynamically
                        MetaCoclass *metacc = nullptr;
                        std::map<std::string, MetaCoclass*>::const_iterator pos = metaComponent->como_classes.find(str_);
                        if (pos == metaComponent->como_classes.end()) {
                            //handle the error
                        } else {
                            metacc = pos->second;
                        }

                        AutoPtr<IInterface> thisObject = metacc->CreateObject();
                        ComoPyClassStub* stub = new ComoPyClassStub(str_, thisObject);
                        return stub;
                    }));
                metaComponent->como_classes.insert(std::pair<std::string, MetaCoclass*>(className, metaCoclass));

                char buf[16];
                for (int j = 0;  j < metaComponent->interfaceNum; j++) {
                    sprintf(buf, "m%d", j);
                    clz_.def(buf, [](ComoPyClassStub *thisObj, py::args args, py::kwargs kwargs) {
                        return thisObj->methodimpl(thisObj, args, kwargs);
                    });
                }
            }
            return metaComponent;
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
