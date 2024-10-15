## 微处理器

即CPU，由ALU运算器，CU控制器，寄存器组，时钟组成
实现了运算功能和控制功能

### 内存读写的步骤

缩写：AB为 `地址总线`，DB为 `数据总线`，CB为 `控制总线`

CPU将要读写的内存单元放到AB上

写操作时，CPU将数据放到DB上，然后通过CB发出写命令

读操作时，CPU通过CB发出读命令，然后将数据从DB上取出

### 接口

- 提供驱动外设的电压与电流

### 总线

即为AB，DB，CB
CPU的寻址范围为2^n，n为地址总线的位数

## 物理结构

- 北桥和南桥都是芯片
- 北桥通过PCI连接速度快的外设，如内存等
- PCI是一种总线，通过接口卡连接外设，如网卡，显卡
- CPU通过北桥连接内存，南桥连接BIOS，硬盘，USB等，速度比较低的外部接口，由ISA总线连接
  ![img.png](img.png)

## 汇编程序执行加法

![img.png](img2.png)

## 汇编程序执行过程

![img_1.png](img_1.png)

缩写：PC为 `程序计数器`，AR为 `地址寄存器`，DR为 `数据寄存器`，IR为 `指令寄存器`，ID为 `指令译码器`

1. 操作系统给PC置初值
2. 输出指令地址到PC中，并将地址存入AR
3. PC+1
4. 从AR中取出地址，进行译码
5. 读写命令
6. 从内存中取出数据，放入DR与IR中
7. 由ID译码，通过时序逻辑电路控制ALU进行运算

## 8086CPU的流水线操作

![img_2.png](img_2.png)