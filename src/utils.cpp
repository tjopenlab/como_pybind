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

#include <comoapi.h>
#include "utils.h"

/*
???    GetRadix(
        [out] Integer& radix);
*/
std::map<std::string, py::object> constantsToMap(Array<IMetaConstant*> &constants) {
    std::map<std::string, py::object> out;

    for (Integer i = 0; i < constants.GetLength(); i++) {
        String name, ns;
        constants[i]->GetName(name);
        constants[i]->GetNamespace(ns);
        if (! ns.IsEmpty()) {
            ns = ns.Replace("::", ".");
            ns = ns + ".";
        }
        std::string strName((ns + name).string());

        AutoPtr<IMetaType> type;
        constants[i]->GetType(type);
        AutoPtr<IMetaValue> value;
        constants[i]->GetValue(value);
        TypeKind kind;
        type->GetTypeKind(kind);

        switch (kind) {
            case TypeKind::Byte:
                {
                    Byte byte;
                    value->GetByteValue(byte);
                    out.insert({strName, py::int_(byte)});
                }
                break;
            case TypeKind::Short:
                {
                    Short svalue;
                    value->GetShortValue(svalue);
                    out.insert({strName, py::int_(svalue)});
                }
                break;
            case TypeKind::Integer:
                {
                    Integer ivalue;
                    value->GetIntegerValue(ivalue);
                    out.insert({strName, py::int_(ivalue)});
                }
                break;
            case TypeKind::Long:
                {
                    Long lvalue;
                    value->GetLongValue(lvalue);
                    out.insert({strName, py::int_(lvalue)});
                }
                break;
            case TypeKind::Float:
                {
                    Float fvalue;
                    value->GetFloatValue(fvalue);
                    out.insert({strName, py::float_(fvalue)});
                }
                break;
            case TypeKind::Double:
                {
                    Double dvalue;
                    value->GetDoubleValue(dvalue);
                    out.insert({strName, py::float_(dvalue)});
                }
                break;
            case TypeKind::Char:
                {
                    Char cvalue;
                    value->GetCharValue(cvalue);
                    out.insert({strName, py::int_(cvalue)});
                }
                break;
            case TypeKind::Boolean:
                {
                    Boolean b;
                    value->GetBooleanValue(b);
                    out.insert({strName, py::bool_(b)});
                }
                break;
            case TypeKind::String:
                {
                    String str;
                    value->GetStringValue(str);
                    out.insert({strName, py::str(str)});
                }
                break;
            case TypeKind::HANDLE:
            case TypeKind::CoclassID:
            case TypeKind::ComponentID:
            case TypeKind::InterfaceID:
            case TypeKind::Interface:
            case TypeKind::Unknown:
                break;
        }
    }

    return out;
}
