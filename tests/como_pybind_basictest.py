# -*- coding: utf-8 -*-
import como_pybind

mc = como_pybind.MetaComponent('ReflectionTestUnit.so')
name = mc.getName();
print ('name is: ' + name)
