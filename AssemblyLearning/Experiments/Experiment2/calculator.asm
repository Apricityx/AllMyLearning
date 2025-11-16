STACKS SEGMENT STACK        ; Define stack segment
           DW 128 DUP(0)
STACKS ENDS

CODES SEGMENT
               ASSUME CS:CODES,SS:STACKS
    START:     
               XOR    AX, AX
               XOR    BX, BX
               XOR    CX, CX
               XOR    DX, DX
               MOV    BX, 1234              ; BX中存储的十进制数为1234
    REVERSE:   
               MOV    AX, BX
               XOR    DX, DX                ; 清空高位，使得DX:AX为被除数
               MOV    CX, 10                ; 除以10
               MOV    AH,0
               MOV    DH, 0
               DIV    DL                    ; 将结果存储在AX中
               MOV    BX,AX
               PUSH   DX
               INC    CX
               CMP    AX,0
               JNE    REVERSE
               XOR    AX,AX
               XOR    BX,BX
               XOR    DX,DX
    REVERSEEND:
               MOV    AX,BX
               MOV    DX,10
               MUL    DX
               MOV    BX,AX
               POP    DX
               ADD    AX,DX
               LOOP   REVERSEEND
               MOV    BX,AX
CODES ENDS
END START
