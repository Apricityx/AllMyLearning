#lang sicp
;高级过程
;term是用来处理a的，next是用来控制a的步长的
(define (sum term a next b)
(if (> a b)
    0
    (+ (term a)
       (sum term (next a) next b))
  )
)

(define (square a)
(* a a)
  )

(sum square 1 inc 3)













(define (deriv-levels g n)
(if (> 0 n))
  0
(derive-levels (deriv g) (- n 1))
  )