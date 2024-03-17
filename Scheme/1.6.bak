#lang sicp
;实现一个过程，输入数字n。计算1到n的和
(define (1ton n)
(define (plus sum counter n)
(if (< counter n)
(plus (+ sum counter) (+ counter 1) n)
    ;T
(+ sum counter)
    ;F
    )
  )
(plus 0 1 n)
  )


(1ton 3)



                      