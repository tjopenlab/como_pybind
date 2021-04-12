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

    // load COMO component meta data
    py::class_<MetaComponent> pymc = py::class_<MetaComponent>(m, "como");
    pymc.def(py::init([m](const std::string &str_) {
            metaComponent = new MetaComponent(str_);

            for(int i = 0;  i < metaComponent->como_classes.size();  i++) {
                MetaCoclass *metaCoclass = metaComponent->como_classes[i];
                std::string className = std::string(metaCoclass->GetName());

                py::class_<ComoPyClassStub> clz_ = py::class_<ComoPyClassStub>(m, className.c_str());
                switch (i) {

#define LAMBDA_FOR_METHOD(_NO_)                                                             \
                    case _NO_:                                                              \
                        clz_.def(py::init([]() {                                            \
                            MetaCoclass *metacc = metaComponent->como_classes[_NO_];        \
                            AutoPtr<IInterface> thisObject = metacc->CreateObject();        \
                            if (thisObject == nullptr) {                                    \
                                ;                                                           \
                            }                                                               \
                            ComoPyClassStub* stub = new ComoPyClassStub(thisObject);        \
                            return stub;                                                    \
                        }));                                                                \
                        break;

#include "LAMBDA_FOR_METHOD.inc"
#undef LAMBDA_FOR_METHOD
                }

                Array<IMetaMethod*> methods;
                int methodNumber;
                methodNumber = metaCoclass->GetMethodNumber();
                for (int j = 0;  j < methodNumber; j++) {
                    const char *str = metaCoclass->GetMethodName(j).c_str();
                    switch (j) {

#define LAMBDA_FOR_METHOD(_NO_)                                         \
                        case _NO_:                                      \
                            clz_.def(str, &ComoPyClassStub::m##_NO_);   \
                            break;

#include "LAMBDA_FOR_METHOD.inc"
#undef LAMBDA_FOR_METHOD
                    }
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
