CODES SEGMENT
          ASSUME CS:CODES
    START:
    ; ; Coding here
          MOV    AX,1234H
          MOV    BX,AX
          SUB    AX,BX
          MOV    CX,AX
          MOV    AX,4
          

CODES ENDS
END START