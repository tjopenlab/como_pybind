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

#include "como_bridge.h"
#include <comoapi.h>

// MetaComponent
///////////////////////////////
std::string MetaComponent::GetName() {
    String str;
    componentHandle->GetName(str);
    return std::string(str.string());
}

std::string MetaComponent::GetComponentID() {
    String str;
    componentHandle->GetName(str);
    return std::string(str.string());
}

int MetaComponent::GetConstantNumber() {
    return 0;
}

ComoArrayIMetaConstant *MetaComponent::GetAllConstants() {
    Array<IMetaConstant*> consts;
    componentHandle->GetAllConstants(consts);
    return new ComoArrayIMetaConstant(consts);
}

MetaConstant *MetaComponent::GetConstant() {
    return nullptr;
}

// MetaConstant
///////////////////////////////
std::string MetaConstant::GetName() {
    String str;
    constant->GetName(str);
    return std::string(str.string());
}

std::string MetaConstant::GetNamespace() {
    String str;
    constant->GetNamespace(str);
    return std::string(str.string());
}

MetaType *MetaConstant::GetType() {
    return nullptr;
}

MetaValue *MetaConstant::GetValue() {
    return nullptr;
}

// MetaCoclass
///////////////////////////////
std::string MetaCoclass::GetName() {
    String str;
    metaCoclass->GetName(str);
    return std::string(str.string());
}

std::string MetaCoclass::GetNamespace() {
    String str;
    metaCoclass->GetNamespace(str);
    return std::string(str.string());
}

std::string* GetAllMethodsName() {
    std::string* pStr = new std::string[3] { "hi", "there"};
    return pStr;
}
