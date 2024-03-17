#lang sicp
(if (= (- 0.5 0.2) (+ 0.1 0.2))
1
2
    )


;cons 构造序对
;car 输出序对第一个数字
;cdr 输出序对第二个数字
;newline过程换行
;let定义匿名过程

(define c (cons 1 2))
(display c)
(newline)
(cons c c)
(newline)
(cdr c)

(define (reduce-fraction fraction)
  (let ((g (gcd (car fraction) (cdr fraction)))) ;求出最大公约数
    (cons (/ (car fraction) g) (/ (cdr fraction) g)))) ;用最大公约数约分

;测试
(reduce-fraction '(12 . 18)) ; => (2 . 3)
(reduce-fraction '(15 . 20)) ; => (3 . 4)
(reduce-fraction '(7 . 21)) ; => (1 . 3)

((lambda (x) (+ x 4)) 4)
;lamada 形参 形参参与的过程 传参

