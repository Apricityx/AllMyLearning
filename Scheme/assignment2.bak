#lang sicp
(define (revert list result)
(if (null? (cdr list))
    (cons (car list) result)
    (revert (cdr list) (cons (car list) result))
    )
  )

(define (first-part num data)
  (define (process data num result originalData)
  (if (null? (cdr data))
    originalData
    (if (= num 0)
        (revert result '())
        (process (cdr data) (- num 1) (cons (car data) result) originalData)
        )
    ))
  (process data num '() data)
  )



(revert (list 1 2 3 4) '())
(first-part 6 (list 1 7 3 4 5))