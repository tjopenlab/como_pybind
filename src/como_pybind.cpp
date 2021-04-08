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

                Array<IMetaMethod*> methods;
                int methodNumber;
                methodNumber = metaCoclass->GetMethodNumber();
                for (int j = 0;  j < methodNumber; j++) {
                    const char *str = metaCoclass->GetMethodName(j).c_str();
                    switch (j) {

#define LAMBDA_FOR_METHOD(_NO_) \
                        case _NO_:                                                                                      \
                            clz_.def(str, [](ComoPyClassStub *thisObj, py::args args, py::kwargs kwargs) -> py::tuple { \
                                return ComoPyClassStub::m##_NO_(thisObj, args, kwargs);                                 \
                            });                                                                                         \
                            break;
/*python script:
for i in range(255):
    print ("LAMBDA_FOR_METHOD(" + str(i) + ")")
*/
                        LAMBDA_FOR_METHOD(0)
                        LAMBDA_FOR_METHOD(1)
                        LAMBDA_FOR_METHOD(2)
                        LAMBDA_FOR_METHOD(3)
                        LAMBDA_FOR_METHOD(4)
                        LAMBDA_FOR_METHOD(5)
                        LAMBDA_FOR_METHOD(6)
                        LAMBDA_FOR_METHOD(7)
                        LAMBDA_FOR_METHOD(8)
                        LAMBDA_FOR_METHOD(9)
                        LAMBDA_FOR_METHOD(10)
                        LAMBDA_FOR_METHOD(11)
                        LAMBDA_FOR_METHOD(12)
                        LAMBDA_FOR_METHOD(13)
                        LAMBDA_FOR_METHOD(14)
                        LAMBDA_FOR_METHOD(15)
                        LAMBDA_FOR_METHOD(16)
                        LAMBDA_FOR_METHOD(17)
                        LAMBDA_FOR_METHOD(18)
                        LAMBDA_FOR_METHOD(19)
                        LAMBDA_FOR_METHOD(20)
                        LAMBDA_FOR_METHOD(21)
                        LAMBDA_FOR_METHOD(22)
                        LAMBDA_FOR_METHOD(23)
                        LAMBDA_FOR_METHOD(24)
                        LAMBDA_FOR_METHOD(25)
                        LAMBDA_FOR_METHOD(26)
                        LAMBDA_FOR_METHOD(27)
                        LAMBDA_FOR_METHOD(28)
                        LAMBDA_FOR_METHOD(29)
                        LAMBDA_FOR_METHOD(30)
                        LAMBDA_FOR_METHOD(31)
                        LAMBDA_FOR_METHOD(32)
                        LAMBDA_FOR_METHOD(33)
                        LAMBDA_FOR_METHOD(34)
                        LAMBDA_FOR_METHOD(35)
                        LAMBDA_FOR_METHOD(36)
                        LAMBDA_FOR_METHOD(37)
                        LAMBDA_FOR_METHOD(38)
                        LAMBDA_FOR_METHOD(39)
                        LAMBDA_FOR_METHOD(40)
                        LAMBDA_FOR_METHOD(41)
                        LAMBDA_FOR_METHOD(42)
                        LAMBDA_FOR_METHOD(43)
                        LAMBDA_FOR_METHOD(44)
                        LAMBDA_FOR_METHOD(45)
                        LAMBDA_FOR_METHOD(46)
                        LAMBDA_FOR_METHOD(47)
                        LAMBDA_FOR_METHOD(48)
                        LAMBDA_FOR_METHOD(49)
                        LAMBDA_FOR_METHOD(50)
                        LAMBDA_FOR_METHOD(51)
                        LAMBDA_FOR_METHOD(52)
                        LAMBDA_FOR_METHOD(53)
                        LAMBDA_FOR_METHOD(54)
                        LAMBDA_FOR_METHOD(55)
                        LAMBDA_FOR_METHOD(56)
                        LAMBDA_FOR_METHOD(57)
                        LAMBDA_FOR_METHOD(58)
                        LAMBDA_FOR_METHOD(59)
                        LAMBDA_FOR_METHOD(60)
                        LAMBDA_FOR_METHOD(61)
                        LAMBDA_FOR_METHOD(62)
                        LAMBDA_FOR_METHOD(63)
                        LAMBDA_FOR_METHOD(64)
                        LAMBDA_FOR_METHOD(65)
                        LAMBDA_FOR_METHOD(66)
                        LAMBDA_FOR_METHOD(67)
                        LAMBDA_FOR_METHOD(68)
                        LAMBDA_FOR_METHOD(69)
                        LAMBDA_FOR_METHOD(70)
                        LAMBDA_FOR_METHOD(71)
                        LAMBDA_FOR_METHOD(72)
                        LAMBDA_FOR_METHOD(73)
                        LAMBDA_FOR_METHOD(74)
                        LAMBDA_FOR_METHOD(75)
                        LAMBDA_FOR_METHOD(76)
                        LAMBDA_FOR_METHOD(77)
                        LAMBDA_FOR_METHOD(78)
                        LAMBDA_FOR_METHOD(79)
                        LAMBDA_FOR_METHOD(80)
                        LAMBDA_FOR_METHOD(81)
                        LAMBDA_FOR_METHOD(82)
                        LAMBDA_FOR_METHOD(83)
                        LAMBDA_FOR_METHOD(84)
                        LAMBDA_FOR_METHOD(85)
                        LAMBDA_FOR_METHOD(86)
                        LAMBDA_FOR_METHOD(87)
                        LAMBDA_FOR_METHOD(88)
                        LAMBDA_FOR_METHOD(89)
                        LAMBDA_FOR_METHOD(90)
                        LAMBDA_FOR_METHOD(91)
                        LAMBDA_FOR_METHOD(92)
                        LAMBDA_FOR_METHOD(93)
                        LAMBDA_FOR_METHOD(94)
                        LAMBDA_FOR_METHOD(95)
                        LAMBDA_FOR_METHOD(96)
                        LAMBDA_FOR_METHOD(97)
                        LAMBDA_FOR_METHOD(98)
                        LAMBDA_FOR_METHOD(99)
                        LAMBDA_FOR_METHOD(100)
                        LAMBDA_FOR_METHOD(101)
                        LAMBDA_FOR_METHOD(102)
                        LAMBDA_FOR_METHOD(103)
                        LAMBDA_FOR_METHOD(104)
                        LAMBDA_FOR_METHOD(105)
                        LAMBDA_FOR_METHOD(106)
                        LAMBDA_FOR_METHOD(107)
                        LAMBDA_FOR_METHOD(108)
                        LAMBDA_FOR_METHOD(109)
                        LAMBDA_FOR_METHOD(110)
                        LAMBDA_FOR_METHOD(111)
                        LAMBDA_FOR_METHOD(112)
                        LAMBDA_FOR_METHOD(113)
                        LAMBDA_FOR_METHOD(114)
                        LAMBDA_FOR_METHOD(115)
                        LAMBDA_FOR_METHOD(116)
                        LAMBDA_FOR_METHOD(117)
                        LAMBDA_FOR_METHOD(118)
                        LAMBDA_FOR_METHOD(119)
                        LAMBDA_FOR_METHOD(120)
                        LAMBDA_FOR_METHOD(121)
                        LAMBDA_FOR_METHOD(122)
                        LAMBDA_FOR_METHOD(123)
                        LAMBDA_FOR_METHOD(124)
                        LAMBDA_FOR_METHOD(125)
                        LAMBDA_FOR_METHOD(126)
                        LAMBDA_FOR_METHOD(127)
                        LAMBDA_FOR_METHOD(128)
                        LAMBDA_FOR_METHOD(129)
                        LAMBDA_FOR_METHOD(130)
                        LAMBDA_FOR_METHOD(131)
                        LAMBDA_FOR_METHOD(132)
                        LAMBDA_FOR_METHOD(133)
                        LAMBDA_FOR_METHOD(134)
                        LAMBDA_FOR_METHOD(135)
                        LAMBDA_FOR_METHOD(136)
                        LAMBDA_FOR_METHOD(137)
                        LAMBDA_FOR_METHOD(138)
                        LAMBDA_FOR_METHOD(139)
                        LAMBDA_FOR_METHOD(140)
                        LAMBDA_FOR_METHOD(141)
                        LAMBDA_FOR_METHOD(142)
                        LAMBDA_FOR_METHOD(143)
                        LAMBDA_FOR_METHOD(144)
                        LAMBDA_FOR_METHOD(145)
                        LAMBDA_FOR_METHOD(146)
                        LAMBDA_FOR_METHOD(147)
                        LAMBDA_FOR_METHOD(148)
                        LAMBDA_FOR_METHOD(149)
                        LAMBDA_FOR_METHOD(150)
                        LAMBDA_FOR_METHOD(151)
                        LAMBDA_FOR_METHOD(152)
                        LAMBDA_FOR_METHOD(153)
                        LAMBDA_FOR_METHOD(154)
                        LAMBDA_FOR_METHOD(155)
                        LAMBDA_FOR_METHOD(156)
                        LAMBDA_FOR_METHOD(157)
                        LAMBDA_FOR_METHOD(158)
                        LAMBDA_FOR_METHOD(159)
                        LAMBDA_FOR_METHOD(160)
                        LAMBDA_FOR_METHOD(161)
                        LAMBDA_FOR_METHOD(162)
                        LAMBDA_FOR_METHOD(163)
                        LAMBDA_FOR_METHOD(164)
                        LAMBDA_FOR_METHOD(165)
                        LAMBDA_FOR_METHOD(166)
                        LAMBDA_FOR_METHOD(167)
                        LAMBDA_FOR_METHOD(168)
                        LAMBDA_FOR_METHOD(169)
                        LAMBDA_FOR_METHOD(170)
                        LAMBDA_FOR_METHOD(171)
                        LAMBDA_FOR_METHOD(172)
                        LAMBDA_FOR_METHOD(173)
                        LAMBDA_FOR_METHOD(174)
                        LAMBDA_FOR_METHOD(175)
                        LAMBDA_FOR_METHOD(176)
                        LAMBDA_FOR_METHOD(177)
                        LAMBDA_FOR_METHOD(178)
                        LAMBDA_FOR_METHOD(179)
                        LAMBDA_FOR_METHOD(180)
                        LAMBDA_FOR_METHOD(181)
                        LAMBDA_FOR_METHOD(182)
                        LAMBDA_FOR_METHOD(183)
                        LAMBDA_FOR_METHOD(184)
                        LAMBDA_FOR_METHOD(185)
                        LAMBDA_FOR_METHOD(186)
                        LAMBDA_FOR_METHOD(187)
                        LAMBDA_FOR_METHOD(188)
                        LAMBDA_FOR_METHOD(189)
                        LAMBDA_FOR_METHOD(190)
                        LAMBDA_FOR_METHOD(191)
                        LAMBDA_FOR_METHOD(192)
                        LAMBDA_FOR_METHOD(193)
                        LAMBDA_FOR_METHOD(194)
                        LAMBDA_FOR_METHOD(195)
                        LAMBDA_FOR_METHOD(196)
                        LAMBDA_FOR_METHOD(197)
                        LAMBDA_FOR_METHOD(198)
                        LAMBDA_FOR_METHOD(199)
                        LAMBDA_FOR_METHOD(200)
                        LAMBDA_FOR_METHOD(201)
                        LAMBDA_FOR_METHOD(202)
                        LAMBDA_FOR_METHOD(203)
                        LAMBDA_FOR_METHOD(204)
                        LAMBDA_FOR_METHOD(205)
                        LAMBDA_FOR_METHOD(206)
                        LAMBDA_FOR_METHOD(207)
                        LAMBDA_FOR_METHOD(208)
                        LAMBDA_FOR_METHOD(209)
                        LAMBDA_FOR_METHOD(210)
                        LAMBDA_FOR_METHOD(211)
                        LAMBDA_FOR_METHOD(212)
                        LAMBDA_FOR_METHOD(213)
                        LAMBDA_FOR_METHOD(214)
                        LAMBDA_FOR_METHOD(215)
                        LAMBDA_FOR_METHOD(216)
                        LAMBDA_FOR_METHOD(217)
                        LAMBDA_FOR_METHOD(218)
                        LAMBDA_FOR_METHOD(219)
                        LAMBDA_FOR_METHOD(220)
                        LAMBDA_FOR_METHOD(221)
                        LAMBDA_FOR_METHOD(222)
                        LAMBDA_FOR_METHOD(223)
                        LAMBDA_FOR_METHOD(224)
                        LAMBDA_FOR_METHOD(225)
                        LAMBDA_FOR_METHOD(226)
                        LAMBDA_FOR_METHOD(227)
                        LAMBDA_FOR_METHOD(228)
                        LAMBDA_FOR_METHOD(229)
                        LAMBDA_FOR_METHOD(230)
                        LAMBDA_FOR_METHOD(231)
                        LAMBDA_FOR_METHOD(232)
                        LAMBDA_FOR_METHOD(233)
                        LAMBDA_FOR_METHOD(234)
                        LAMBDA_FOR_METHOD(235)
                        LAMBDA_FOR_METHOD(236)
                        LAMBDA_FOR_METHOD(237)
                        LAMBDA_FOR_METHOD(238)
                        LAMBDA_FOR_METHOD(239)
                        LAMBDA_FOR_METHOD(240)
                        LAMBDA_FOR_METHOD(241)
                        LAMBDA_FOR_METHOD(242)
                        LAMBDA_FOR_METHOD(243)
                        LAMBDA_FOR_METHOD(244)
                        LAMBDA_FOR_METHOD(245)
                        LAMBDA_FOR_METHOD(246)
                        LAMBDA_FOR_METHOD(247)
                        LAMBDA_FOR_METHOD(248)
                        LAMBDA_FOR_METHOD(249)
                        LAMBDA_FOR_METHOD(250)
                        LAMBDA_FOR_METHOD(251)
                        LAMBDA_FOR_METHOD(252)
                        LAMBDA_FOR_METHOD(253)
                        LAMBDA_FOR_METHOD(254)
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
