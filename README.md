# como_pybind

#### 介绍
como_pybind是COMO python 绑定库。

python通过反射机制调用COMO构件，不需要COMO做任何改变，写出的构件就可以在python中使用。只要是用COMO规范开发的C++程序，就可以象python自己写的程序模块module一样，但效率高得多。

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
pip install como_pybind
```
#### 使用说明
```python
import como_pybind

# 通过下面这条语句，ReflectionTestUnit.so这个COMO构件中的所有构件类（Coclass）就都加载到python环境中了
mc = como_pybind.como('ReflectionTestUnit.so')
name = mc.getName();
print ('name is: ' + name)
print ('constants: ', mc.getAllConstants());

# CMethodTester是ReflectionTestUnit.so这个COMO构件中的一个构件类（Coclass）
cmt = como_pybind.CMethodTester()
print ('load COMO class CMethodTester')

print (cmt.TestMethod1(12392021))
print (cmt.getAllConstants())
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



#### "openEuler on RISC-V" 上应用实例

- 安装python开发包：

```shell
$ yum install python3-devel
```

其它与"CentOS on AARCH64" 相同。



##### 常用Linux命令行剪贴板
```shell
$ wget https://repo.openeuler.org/openEuler-preview/RISC-V/Image/fw_payload_oe.elf
$ wget https://repo.openeuler.org/openEuler-preview/RISC-V/Image/openEuler-preview.riscv64.qcow2

$ wget https://isrc.iscas.ac.cn/mirror/openeuler-sig-riscv/images/fw_payload_oe.elf
$ wget https://isrc.iscas.ac.cn/mirror/openeuler-sig-riscv/images/oe-rv-rv64g-30G.qcow2

$ qemu-system-riscv64  -nographic -machine virt  -smp 8 -m 2G  -kernel fw_payload_oe.elf  -drive file=openEuler-preview.riscv64.qcow2,format=qcow2,id=hd0  -object rng-random,filename=/dev/urandom,id=rng0  -device virtio-rng-device,rng=rng0  -device virtio-blk-device,drive=hd0  -device virtio-net-device,netdev=usernet  -netdev user,id=usernet,hostfwd=tcp::12055-:22  -append 'root=/dev/vda1 rw console=ttyS0 systemd.default_timeout_start_sec=600 selinux=0 highres=off mem=4096M earlycon'

$ ssh -p 12055 root@localhost
默认的登陆用户名/密码是：root/openEuler12#$
```
