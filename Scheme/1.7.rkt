#lang sicp

(define (goodenough? n m)
(if (< (abs (- (/ n m) 1)) 0.0001)
  #t
  #f
))

;求平均数过程
(define (average a b)
(/ (+ a b) 2)
)


(define (improve guess original)


(define (sqrt x y))
  (if (goodenough? guess original)
    guess
    ()
  )