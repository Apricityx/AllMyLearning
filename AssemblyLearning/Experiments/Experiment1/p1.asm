DATA SEGMENT
                ORG 3500H
      SRC_DATA  DB  8 DUP(?)      ; 源数据存储在3500H开始的8个字节

                ORG 3600H
      DEST_DATA DB  8 DUP(?)      ; 目标数据存储在3600H开始的8个字节
DATA ENDS

CODES SEGMENT
                ASSUME CS:CODES, DS:DATA
      START:    
      ; ; Coding here
                MOV    SI,3500H
                MOV    DI,3600H
                MOV    AX,DATA
                MOV    DS,AX
                MOV    CX,8
      COPY_LOOP:
                MOV    AL,[SI]                ; 读取原地址
                MOV    [DI],AL                ; 写入目标地址
                INC    SI
                INC    DI
                LOOP   COPY_LOOP              ;CX为0时跳出循环
                INT    21H
CODES ENDS
END START