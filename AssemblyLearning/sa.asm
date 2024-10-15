DATAS SEGMENT
      STRING  DB 'HELLO WORLD$'       ; DB是定义字节型数据的伪指令，STRING是标号，HELLO WORLD$是字符串
      STRING2 DB 'HELLO WORLD2$'
DATAS ENDS

STACKS SEGMENT STACK            ; 定义堆栈段
             DW 128 DUP(0)      ; 定义128个字的堆栈
STACKS ENDS

CODES SEGMENT                                       ; 定义CODES段
            ASSUME CS:CODES,DS:DATAS,SS:STACKS      ; ASSUME是一个宏，用于定义段寄存器的默认值 CS，DS，SS都是段寄存器
      ; ; Coding here
            MOV    AX,DATAS        ; START用于标定程序的入口，DATAS指定了数据段在哪
            MOV    DS,AX           ; 将数据段地址传给DS，DS是数据段寄存器 Data Segment
            LEA    DX,STRING       ; LEA是将字符串的偏移地址传给DX，DX是数据段寄存器 Data Segment
            MOV    AH,9            ; AH是寄存器，09H是功能号，表示显示字符串
            INT    21H             ; 调用21H中断，显示字符串
            MOV    AH,4CH          ; AH是寄存器，4CH是功能号，表示程序结束
            INT    21H             ; 调用21H中断，程序结束
      ; AH寄存器的作用是存放功能号，存放后将根据功能号执行相应的操作
      ; 寄存器最多可以存储FFFFH=65535
            MOV    AX,1018H                         ; 将1018H传给AX
            MOV    SI,030AH                         ; 将030AH传给SI
            MOV    [SI],AX                          ; 将AX的值传给SI
            ADD    AL,30H                           ; 将AL的值加上30H, 此时的AX=1018H+30H=1048H
            MOV    DX,3FFH
            ADD    AX,DX
            MOV    DS:WORD PTR[20H],1000H           ; 将1000H传给DS:WORD PTR[20H]
            ADD    [SI],AX
            PUSH   AX
            POP    AX
      START:
            MOV    AX,0A0AH
            ADD    AX,0FFFFH
            MOV    CX,0FF00H
            ADC    AX, CX
            SUB    AX,AX
            INC    AX
            OR     CX,0FFH
            AND    CX,0F0FH
            MOV    DS:[10H],CX
            ; 正常结束程序
            MOV    AH,4CH
            INT    21H
CODES ENDS                                          ; CODES段结束
END START                            ; 程序结束，指定入口点