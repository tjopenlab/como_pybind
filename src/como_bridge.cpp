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

void MetaComponent::GetAllCoclasses() {
    Integer number;
    componentHandle->GetCoclassNumber(number);
    Array<IMetaCoclass*> klasses(number);
    componentHandle->GetAllCoclasses(klasses);
    for (int i = 0;  i < number;  i++) {
        String name;
        klasses[i]->GetName(name);
        std::string className = std::string(name);

        MetaCoclass *metaCoclass;
        metaCoclass = new MetaCoclass(klasses[i]);
        como_classes.insert(std::pair<std::string, MetaCoclass*>(className, metaCoclass));
    }
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


int MetaCoclass::GetMethodNumber() {
    int methodNumber;
    metaCoclass->GetMethodNumber(methodNumber);
    return methodNumber;
}


std::string MetaCoclass::GetMethodName(int idxMethod) {
    String str;
    methods[idxMethod]->GetName(str);
    return std::string(str.string());
}

AutoPtr<IInterface> MetaCoclass::CreateObject() {
    AutoPtr<IInterface> object(nullptr);
    ECode ec = metaCoclass->CreateObject(IID_IInterface, &object);
    return object;
}


// ComoPyClassStub
///////////////////////////////

/*
The class py::args derives from py::tuple and py::kwargs derives from py::dict.

access data from args:
    printf("%d", int(py::int_(args[0])));
    printf("%d", int(args[0].cast<py::int_>()));
    printf("%d", int(py::int_(kwargs["get"])));
*/
py::tuple ComoPyClassStub::methodimpl(int idxMethod, py::args args, py::kwargs kwargs) {
    ECode ec = 0;
    AutoPtr<IArgumentList> argList;
    AutoPtr<IMetaMethod> method(methods[idxMethod]);

    Boolean outArgs;
    Integer paramNumber;
    method->HasOutArguments(outArgs);
    method->GetParameterNumber(paramNumber);

    py::tuple out_tuple;
    HANDLE *outResult = nullptr;
    if (outArgs) {
        py::tuple out_tuple = py::make_tuple();
        outResult = (HANDLE*)calloc(sizeof(HANDLE), paramNumber);
    }

    method->CreateArgumentList(argList);
    Array<IMetaParameter*> params(paramNumber);
    method->GetAllParameters(params);
    Integer inParam = 0;
    for (Integer i = 0; i < paramNumber; i++) {
        IMetaParameter* param = params[i];

        String name;
        Integer index;
        IOAttribute attr;
        AutoPtr<IMetaType> type;
        String tname;
        TypeKind kind;

        param->GetName(name);
        param->GetIndex(index);
        param->GetIOAttribute(attr);
        param->GetType(type);
        type->GetName(tname);
        type->GetTypeKind(kind);

        if (inParam >= args.size()) {
            // too much COMO input paramter
            ec = E_ILLEGAL_ARGUMENT_EXCEPTION;
            break;
        }

        if (attr == IOAttribute::IN) {
            switch (kind) {
                case TypeKind::Byte:
                    argList->SetInputArgumentOfByte(i, int(py::int_(args[inParam])));
                    break;
                case TypeKind::Short:
                    argList->SetInputArgumentOfShort(i, int(py::int_(args[inParam])));
                    break;
                case TypeKind::Integer:
                    argList->SetInputArgumentOfInteger(i, int(py::int_(args[inParam])));
                    break;
                case TypeKind::Long:
                    argList->SetInputArgumentOfLong(i, int(py::int_(args[inParam])));
                    break;
                case TypeKind::Float:
                    argList->SetInputArgumentOfFloat(i, float(py::float_(args[inParam])));
                    break;
                case TypeKind::Double:
                    argList->SetInputArgumentOfDouble(i, float(py::float_(args[inParam])));
                    break;
                case TypeKind::Char:
                    argList->SetInputArgumentOfChar(i, int(py::int_(args[inParam])));
                    break;
                case TypeKind::Boolean:
                    argList->SetInputArgumentOfBoolean(i, Boolean(py::bool_(args[inParam])));
                    break;
                case TypeKind::String:
                    argList->SetInputArgumentOfString(i, String(std::string(py::str(args[inParam])).c_str()));
                    break;
                case TypeKind::HANDLE:
                case TypeKind::CoclassID:
                case TypeKind::ComponentID:
                case TypeKind::InterfaceID:
                case TypeKind::Interface:
                case TypeKind::Unknown:
                    break;
            }
            inParam++;
        }
        else /*if (attr == IOAttribute::OUT)*/ {
            switch (kind) {
                case TypeKind::Byte:
                    outResult[i] = reinterpret_cast<HANDLE>(malloc(sizeof(Byte)));
                    argList->SetOutputArgumentOfInteger(i, outResult[i]);
                    break;
                case TypeKind::Short:
                    outResult[i] = reinterpret_cast<HANDLE>(malloc(sizeof(Short)));
                    argList->SetOutputArgumentOfInteger(i, outResult[i]);
                    break;
                case TypeKind::Integer:
                    outResult[i] = reinterpret_cast<HANDLE>(malloc(sizeof(Integer)));
                    argList->SetOutputArgumentOfInteger(i, outResult[i]);
                    break;
                case TypeKind::Long:
                    outResult[i] = reinterpret_cast<HANDLE>(malloc(sizeof(Long)));
                    argList->SetOutputArgumentOfInteger(i, outResult[i]);
                    break;
                case TypeKind::Float:
                    outResult[i] = reinterpret_cast<HANDLE>(malloc(sizeof(Float)));
                    argList->SetOutputArgumentOfInteger(i, outResult[i]);
                    break;
                case TypeKind::Double:
                    outResult[i] = reinterpret_cast<HANDLE>(malloc(sizeof(Double)));
                    argList->SetOutputArgumentOfInteger(i, outResult[i]);
                    break;
                case TypeKind::Char:
                    outResult[i] = reinterpret_cast<HANDLE>(malloc(sizeof(Char)));
                    argList->SetOutputArgumentOfInteger(i, outResult[i]);
                    break;
                case TypeKind::Boolean:
                    outResult[i] = reinterpret_cast<HANDLE>(malloc(sizeof(Boolean)));
                    argList->SetOutputArgumentOfInteger(i, outResult[i]);
                    break;
                case TypeKind::String:
                    outResult[i] = reinterpret_cast<HANDLE>(malloc(sizeof(String)));
                    argList->SetOutputArgumentOfInteger(i, outResult[i]);
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
    }

    if (ec == 0) {
        ec = methods[1]->Invoke(thisObject, argList);
    }

    if (outArgs && (outResult != nullptr)) {
        // collect output results into out_tuple
        for (Integer i = 0; i < paramNumber; i++) {
            IMetaParameter* param = params[i];

            IOAttribute attr;
            AutoPtr<IMetaType> type;
            TypeKind kind;

            param->GetIOAttribute(attr);
            param->GetType(type);
            type->GetTypeKind(kind);

            if (attr == IOAttribute::OUT) {
                switch (kind) {
                    case TypeKind::Byte:
                        out_tuple = py::make_tuple(out_tuple, *(reinterpret_cast<Byte*>(outResult[i])));
                        free(reinterpret_cast<void*>(outResult[i]));
                        break;
                    case TypeKind::Short:
                        out_tuple = py::make_tuple(out_tuple, *(reinterpret_cast<Short*>(outResult[i])));
                        free(reinterpret_cast<void*>(outResult[i]));
                        break;
                    case TypeKind::Integer:
                        out_tuple = py::make_tuple(out_tuple, *(reinterpret_cast<int*>(outResult[i])));
                        free(reinterpret_cast<void*>(outResult[i]));
                        break;
                    case TypeKind::Long:
                        out_tuple = py::make_tuple(out_tuple, *(reinterpret_cast<Long*>(outResult[i])));
                        free(reinterpret_cast<void*>(outResult[i]));
                        break;
                    case TypeKind::Float:
                        out_tuple = py::make_tuple(out_tuple, *(reinterpret_cast<Float*>(outResult[i])));
                        free(reinterpret_cast<void*>(outResult[i]));
                        break;
                    case TypeKind::Double:
                        out_tuple = py::make_tuple(out_tuple, *(reinterpret_cast<Double*>(outResult[i])));
                        free(reinterpret_cast<void*>(outResult[i]));
                        break;
                    case TypeKind::Char:
                        out_tuple = py::make_tuple(out_tuple, *(reinterpret_cast<Char*>(outResult[i])));
                        free(reinterpret_cast<void*>(outResult[i]));
                        break;
                    case TypeKind::Boolean:
                        out_tuple = py::make_tuple(out_tuple, *(reinterpret_cast<Boolean*>(outResult[i])));
                        free(reinterpret_cast<void*>(outResult[i]));
                        break;
                    case TypeKind::String:
                        out_tuple = py::make_tuple(out_tuple, *(reinterpret_cast<String*>(outResult[i])));
                        free(reinterpret_cast<void*>(outResult[i]));
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
        }

        free(outResult);
    }
    else {
        out_tuple = py::make_tuple(ec);
    }

    return out_tuple;
}
