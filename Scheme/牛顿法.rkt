#lang sicp
;平方过程
(define (square x)
(* x x)
  )

(define (goodenough? n m)
(if (< (abs (- (square n) m)) 0000.1)
  #t
  #f
))
;求平均数过程
(define (average a b)
(/ (+ a b) 2)
)


(define (improve guess original)
(average guess (/ original guess))
  )


(define (process x y)
  (if (goodenough? x y)
    x
    (process (improve x y) y)
))

(define (sqrt n)
(process 1.0 n)
  )


(sqrt 300000)