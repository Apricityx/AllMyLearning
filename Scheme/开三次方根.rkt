#lang sicp
(define (goodenough x y)
(< (abs (- x y)) 0.001)
  )