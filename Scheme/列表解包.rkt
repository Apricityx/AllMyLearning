#lang sicp
; 创建列表
(define list1 (list 1 2 3 4 5 6 7))

; 计算列表长度
(define (length items)
  (if (null? items)
      0
      (+ 1 (length (cdr items)))
  )
)

; 解包列表
(define (unpacking items counter times)
  (if (< counter times)
      (unpacking (cdr items) (+ counter 1) times)
      items
  )
)

; 解包函数
(define (unpack items times)
  (if (<= (length items) times)
      -1
      (unpacking items 0 times)
  )
)

; 测试代码
(display (length list1))
(newline)
(display (unpack list1 7))
(newline)
