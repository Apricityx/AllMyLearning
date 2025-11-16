DATAS SEGMENT
      STRING  DB 'HELLO WORLD$'       ;DB是定义字节型数据的伪指令，STRING是标号，HELLO WORLD$是字符串
      STRING2 DB 'HELLO WORLD2$'
DATAS ENDS


CODES SEGMENT                             ; 定义CODES段
            ASSUME CS:CODES,DS:DATAS      ; ASSUME是一个宏，用于定义段寄存器的默认值 CS，DS都是段寄存器
      START:
      ; Coding here
            MOV    AX,DATAS               ; START用于标定程序的入口，DATAS指定了数据段在哪
            MOV    DS,AX                  ; 将数据段地址传给DS，DS是数据段寄存器 Data Segment
            LEA    DX,STRING              ; LEA是将字符串的偏移地址传给DX，DX是数据段寄存器 Data Segment
            MOV    AH,9                   ; AH是寄存器，09H是功能号，表示显示字符串
            INT    21H                    ; ？调用21H中断，显示字符串
            MOV    AH,4CH                 ; AH是寄存器，4CH是功能号，表示程序结束
            INT    21H                    ; ？调用21H中断，程序结束
      ;AH寄存器的作用是存放功能号，存放后将根据功能号执行相应的操作
CODES ENDS                                ;CODES段结束
END START
