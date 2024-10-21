#   

## 无符号数比较规则

```
CMP AH, AL
```

指令执行后会更改标志位，通过标志位来确定大小

实质上是执行了AH-AL

## 乘法指令

### 无符号

MUL SRC
需要将乘数放入AX或是AL中去，需确保字乘字，字节乘字节

## 除法指令

```
DIV SRC
```

AL <- AX/(SRC)8 ;商存入AL中

AH <- AX/(SRC)8 ;余数存入AHx中

## 字节转换为字命令

```nasm
CBW
```

AL中的符号为扩展到AH中

## 与指令

```nasm
AND DEST, SRC
```

DEST <- DEST , SRC

## 或指令

```nasm
OR DEST, SRC
```

DEST <- DEST , SRC

## 与和或的用途

### 清零

```nasm
AND AX, 0
```

说明：将AX中的所有位清零

指令执行完成后，AL和AH中的值都为0

### 保留
    
```nasm
OR AX, 0
```

说明：将AX中的所有位保留

指令执行完成后，AL和AH中的值不变


## 异或指令

```nasm
XOR DEST, SRC
```

DEST <- DEST , SRC

## TEST指令

```nasm
TEST DEST, SRC
```

TEST用于测试两个操作数的逻辑与结果，不改变操作数的值，只改变标志位

例：检测AL中的内容是否为负数，若为负则跳转

```nasm
TEST AL, 80H
JNZ NEXT

NEXT:
```

解释：

TEST与AND指令很相似，他们的区别在于，TEST不改变操作数的值

80H = 1000 0000

NZ是标志位，表示AL中的内容不为0

那么意思是，检测AL中的最高位是否为1，若为1则跳转
