#lang sicp
;平方过程
(define (square x)
(* x x)
  )

(define (goodenough? n m)
(if (< (abs (- (/ n m) 1)) 00.1)
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
  (if (goodenough? x (improve x y))
    x
    (process (improve x y) y)
))

(define (sqrt n)
(process 1.0 n)
  )


(sqrt 400000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000)