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

#ifndef __COMO_BRIDGE_H__
#define __COMO_BRIDGE_H__

#include <pybind11/stl.h>
#include <comoapi.h>
#include "como_pytypes.h"

class MetaConstant;
class MetaType;
class MetaValue;
class MetaCoclass;

#define MAX_METHOD_NAME_LENGTH 1024
extern std::map<std::string, py::class_<ComoPyClassStub>> g_como_classes;

// MetaComponent
///////////////////////////////

#pragma GCC visibility push(hidden)
// disable warning: ‘MetaComponent’ declared with greater visibility than the
// type of its field ‘MetaComponent::como_classes’ [-Wattributes]

class MetaComponent {
public:
    MetaComponent(const std::string &componentPath_) : componentPath(componentPath_) {
        String path(componentPath.c_str());
        CoGetComponentMetadataWithPath(path, nullptr, componentHandle);
        GetAllCoclasses();
    }

    std::string GetName();
    std::string GetComponentID();
    int GetConstantNumber();
    std::map<std::string, py::object> GetAllConstants();
    MetaConstant *GetConstant();

    std::string componentPath;
    std::vector<MetaCoclass*> como_classes;
private:
    void GetAllCoclasses();
    AutoPtr<IMetaComponent> componentHandle;
};

#pragma GCC visibility pop

// MetaConstant
///////////////////////////////
class MetaConstant {
public:
    MetaConstant(AutoPtr<IMetaConstant> constant_) : constant(constant_) {}

    std::string GetName();
    std::string GetNamespace();
    MetaType *GetType();
    MetaValue *GetValue();

private:
    AutoPtr<IMetaConstant> constant;
};


class MetaType {
public:
    MetaType(AutoPtr<IMetaType> metaType_) : metaType(metaType_) {}

private:
    AutoPtr<IMetaType> metaType;
};

class MetaValue {
public:
    MetaValue(AutoPtr<IMetaValue> metaValue_) : metaValue(metaValue_) {}

private:
    AutoPtr<IMetaValue> metaValue;
};

// MetaCoclass
///////////////////////////////
class MetaCoclass {
public:
    MetaCoclass(AutoPtr<IMetaCoclass> metaCoclass_) : metaCoclass(metaCoclass_) {
        metaCoclass_->GetMethodNumber(methodNumber);
        Array<IMetaMethod*> methods_(methodNumber);
        ECode ec = metaCoclass_->GetAllMethods(methods_);
        if (FAILED(ec)) {
            String str;
            metaCoclass_->GetName(str);
            std::string className = std::string(str.string());
            throw std::runtime_error("COMO class GetAllMethods: " + className);
        }
        methods = methods_;
    }

    std::string GetName();
    std::string GetNamespace();
    void GetMethodName(int idxMethod, char *buf);
    AutoPtr<IInterface> CreateObject();

    Integer methodNumber;

private:
    AutoPtr<IMetaCoclass> metaCoclass;
    Array<IMetaMethod*> methods;
};

#endif
