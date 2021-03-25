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
como_pybind.add(1, 2)
```
