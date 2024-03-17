#lang sicp
;求导
(define (deriv fx x)
  (/ (- (fx (+ x 0.0001) ) (fx x)) 0.0001)
  )


(define (function x)
(* x 5)
  )

(deriv function 10)