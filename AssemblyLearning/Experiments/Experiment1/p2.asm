DATA SEGMENT
      HELLO_MESSAGE DB 0DH,0AH,'Hello! My university!$', 0      ; 以$为终止符
DATA ENDS

CODES SEGMENT
                  ASSUME CS:CODES, DS:DATA
      START:      
      ; 初始化数据段
                  MOV    AX, DATA
                  MOV    DS, AX

      ; 输出字母a到z
                  MOV    AL, 97                 ; 97 refers to 'a' in ASCII
                  MOV    CX, 26                 ; 26 letters in the alphabet
      PRINT_LOOP: 
                  MOV    DL, AL
                  MOV    AH, 02H                ; 02H refers to interrupt
                  INT    21H
                  INC    AL
                  LOOP   PRINT_LOOP

      ; 输出HELLO_MESSAGE，直到遇到终止符$
                  LEA    SI, HELLO_MESSAGE      ; Load HELLO_MESSAGE address to SI
      PRINT_LOOP2:
                  MOV    DL, [SI]
                  CMP    DL, '$'
                  JE     END_PRINT
                  MOV    AH, 02H
                  INT    21H
                  INC    SI
                  JMP    PRINT_LOOP2

      END_PRINT:  
      ; 退出程序
                  MOV    AX, 4C00h
                  INT    21h
CODES ENDS
END START
