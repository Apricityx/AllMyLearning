STACKS SEGMENT STACK                ; Define stack segment
               DW 128 DUP(0)
STACKS ENDS

CODES SEGMENT
                      ASSUME CS:CODES,SS:STACKS

        DISPLAYNUM:   
                      MOV    DH, 0
                      MOV    CX, 0                     ; 初始化计数器
                      MOV    AX, DX                    ; 将 DX 中的数据放入 AX 进行操作
                      MOV    BX, 10                    ; 除数 10

        DISPLAYLOOP:  
                      XOR    DX, DX                    ; 清空 DX（高位），为除法做准备
                      DIV    BX                        ; AX / BX，商存入 AX，余数存入 DX
                      MOV    DH,0
                      PUSH   DX                        ; 将当前余数（个位）压入栈
                      INC    CX                        ; 增加位数计数
                      CMP    AX, 0                     ; 如果商为 0，则处理结束
                      JNE    DISPLAYLOOP

        DISPLAYNUMEND:
                      MOV    AH, 02h                   ; DOS 功能号：显示字符
        OUTPUTLOOP:   
                      POP    DX                        ; 从栈中弹出一位数字
                      ADD    DL, '0'                   ; 转换为 ASCII 字符
                      INT    21h                       ; 显示字符
                      LOOP   OUTPUTLOOP                ; 依次显示每一位
                      RET


        ; ; 转换 DX 中的数字(10进制)为 ASCII 码
        ;            ADD    DX, '0'
        ;            MOV    AH, 02H                   ; 设置功能号为 02h，显示字符
        ;            INT    21h                       ; 调用中断显示字符
        ;            RET
        INTPUT:       
                      MOV    AH, 01H                   ; 设置功能号为 01h，读取字符
                      INT    21h                       ; 调用中断读取字符
                      MOV    AH, 0                     ; 重置 AH
                      RET                              ; 函数结束后，AL中将存放输入的字符
        INPUTING:     
                      CALL   INTPUT
                      CMP    AL, 0Dh                   ; 检查是否按下回车键
                      JE     COVERTING
                      MOV    AH,0
                      SUB    AX, '0'                   ; 将字符转换为数字
                      PUSH   AX
                      INC    CX
                      JMP    INPUTING                  ;Jump if not equal
        COVERTING:                                     ;将输入的数字一个一个弹出，并整合为一个十进制数
                      MOV    BX,0                      ;以BX存储最终的十进制数
        ;       SUB    CX,1                      ;减去最后一个回车键
        COVERTLOOP:   
                      MOV    DH,0
                      MOV    AX,10
                      MUL    BX
                      POP    DX                        ; 将结果乘以10再加上DX即可
                      ADD    AX,DX
                      MOV    BX,AX
                      LOOP   COVERTLOOP
                      RET
        START:        
        ;       MOV    DX,1234
        ;       CALL   DISPLAYNUM
                      MOV    CX,0
                      MOV    BX,0
                      CALL   INPUTING
                      PUSH   BX
                      CALL   INPUTING
        ;       POP    BX -> CX
                      PUSH   BX
                      POP    BX
                      POP    CX
                      CALL   INTPUT
                      CMP    AL, '+'                   ;检查是否为加号
                      JE     PLUS
                      CMP    AL, '-'                   ;检查是否为减号
                      JE     MINUS
                      CMP    AL, '*'                   ;检查是否为乘号
                      JE     MULTIPLY
                      CMP    AL, '/'                   ;检查是否为除号
                      JE     DIVIDE
        PLUS:         
                      MOV    AX,CX
                      ADD    AX,BX
                      JMP    DISPLAYING
        MINUS:        
                      MOV    AX,CX
                      SUB    AX,BX
                      JMP    DISPLAYING
        MULTIPLY:     
                      MOV    AX,CX
                      MUL    BX
                      JMP    DISPLAYING
        DIVIDE:       
                      MOV    AX,CX
                      DIV    BL                        ;AX/BX
                      MOV    CH,0
                      JMP    DISPLAYING
        
        DISPLAYING:   
                      MOV    DX, AX                    ;将要显示的数字放入DX
                      CALL   DISPLAYNUM
                
        ENDING:       
                      MOV    AH, 4Ch                   ; 设置功能号为 4Ch，退出程序
                      INT    21h                       ; 调用中断退出

       
CODES ENDS
END START
