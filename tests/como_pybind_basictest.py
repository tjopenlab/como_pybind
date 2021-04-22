# -*- coding: utf-8 -*-

'''
$ source build/envsetup.sh
$ como_linux_x64
$ source ~/anaconda3/bin/activate py36

$ export PYTHONPATH=$PYTHONPATH:${HOME}/como/como_pybind/pybind11/pybind11
$ export LIB_PATH=$LIB_PATH:$BIN_PATH
'''

import como_pybind
import os, sys
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../")))

mc = como_pybind.como('ReflectionTestUnit.so')
name = mc.getName();
print('name is: ' + name)
#print ('constants: ', mc.getAllConstants());

cmt = como_pybind.CMethodTester()
print('load COMO class CMethodTester')
print('the name of class is ## {} ##'.format(cmt.__class__.__name__))

print(cmt.TestMethod1(12392021))
print(cmt.getAllConstants())
