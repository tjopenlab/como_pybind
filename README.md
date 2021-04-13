# como_pybind

#### 介绍
COMO python 绑定库

#### 软件架构
软件架构说明

#### 安装教程

首先进 COMO 工作环境：
```shell
- como_linux_x64:       Switch to build como for linux x64.
- como_linux_aarch64:   Switch to build como for linux aarch64.
- como_linux_riscv64:   Switch to build como for linux riscv64.
- como_android_aarch64: Switch to build como for android aarch64.
- como_openEuler_riscv: Switch to build como for openEuler RISC-V.
```
然后，进Anaconda工作环境：
```shell
~/home/como/out/target/como.linux.x64.rls$ source ~/anaconda3/bin/activate py36
```


```shell
pip install ./como_pybind
```
#### 使用说明
```python
import como_pybind

mc = como_pybind.como('ReflectionTestUnit.so')
name = mc.getName();
```



#### "CentOS on AARCH64" 上应用实例

- 安装ninja https://support.huaweicloud.com/prtg-kunpengdbs/kunpenggreenplum_02_0011.html
- CentOS7-arm64安装Archiconda3 https://blog.csdn.net/frdevolcqzyxynjds/article/details/105939421

```shell
进入COMO开发环境
$ source build/envsetup.sh
$ como_linux_aarch64

如果Anaconda有虚拟环境，激活相应的环境
$ source ~/anaconda3/bin/activate py36

$ export PYTHONPATH=$PYTHONPATH:${HOME}/como_pybind/pybind11/pybind11

设置COMO构件寻找路径
$ export LIB_PATH=$LIB_PATH:$BIN_PATH

安装como_pybind
$ cd ${HOME}/como_pybind
$ python setup.py install

运行como_pybind实验程序
$ python tests/como_pybind_basictest.py
```
