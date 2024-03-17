#lang sicp
(define (cons x y)
(define (dispatch m)
  (cond ((= m 0) x)
        ((= m 1) y)
        (else (error "111" m))))
  dispatch)
(define (car z) (z 0))

(car (cons 1 2))

(define a 0)