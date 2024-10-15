# 移传送类指令

## 压栈

压栈时高位数据在上面，低位数据在下面

## 交换指令

XCHG AX,BX
交换AX,BX的内容

## 查表指令

XLAT
在BX中存储基地址
在AL中存储偏移量
XLAT将[BX+AL]的值存进AX

等效于

```Assembly
MOV BX 2000H
MOV SI,0BH
MOV AL,[BX][SI]
```

## 地址传送指令

LEA AX,VAR
将VAR的偏移量传送到AX中

LDS AX,VAR
将VAR的第一个字传送到AX中，VAR的第二个字传送到DS中
高位在DS，低位在AX

# 逻辑运算指令

## 加法指令

ADD AX,BX
等效于AX = AX + BX
会全面影响标志寄存器

## 带进位加法指令

ADC AX,BX
等效于AX = AX + BX + CF
其中的CF是上一次运算的进位标志
例如实现的16位加法运算中，寄存器只能存储8位，所以需要进位标志

```Assembly
MOV AX,0FFFH
MOV BX,0213H
ADD AX,BX
MOV CX,2332H
ADC CX,AX
最终获得结果为2332H+0FFFH+0213H
```

## 自增指令

INC AX
AX = AX + 1

## 减法操作

## 不带借位减法

SUB AX,BX

## 带借位减法

SBB AX,BX
AX = AX - BX - CF
和ADC类似

## 自减指令

DEC AX
AX = AX - 1
和INC类似

## 求补指令

求绝对值
```Assembly
ADD AL,0 ; 产生SF=1
JNS LI ;当AL为正数时跳转
NEG AL ;求补
LI:
.......
```