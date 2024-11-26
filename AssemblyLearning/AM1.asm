STACKS SEGMENT STACK            ; 定义堆栈段
             DW 128 DUP(0)      ; 定义128个字的堆栈
STACKS ENDS
CODES SEGMENT                                    ; 定义CODES段
            ASSUME CS:CODES,SS:STACKS            ; ASSUME是一个宏，用于定义段寄存器的默认值 CS，DS，SS都是段寄存器
      START:
      ; ; Coding here
            ; MOV    AX, 0FFFFH
            ; MOV    SI, 00FFH
            ; MOV    [SI],AX
            ; ADD    AL, 01H
            ; MOV    DX,3FFH
            ; ADD    AX, DX
            ; MOV    DS: WORD PTR[20H], 1000H
            ; ADD    [SI], AX
            MOV    AX,'1'
            PUSH   AX
            POP    BX
            MOV    DX,BX
            MOV    AH, 02H                       ; 设置功能号为02h，显示字符
            INT    21H                           ; 调用DOS中断，输出字符
CODES ENDS                                       ; CODES段结束
END START                            ; 程序结束，指定入口点