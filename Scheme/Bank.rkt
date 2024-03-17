#lang sicp
;定义了一个银行存取的过程
;withdraw-pureFunc函数有两个参数：金钱和行为
;行为则为多个操作构成的列表，会被层层解包成withdraw或deposit


(define (withdraw-pureFunc initial behaviors)
(define (calculate behav) ;behav的实际参数是behaviors，则为一个大的列表，会被解包
  (let ( (a ( if ( not (null? behav)) ;若不为空则变为(a initial)
                 (calculate (cdr behav))
                 initial))) ;若不为空，则初始化账户金额
    (cond ((null? behav) initial) ;同样判断是否为空
          ((eq? (caar behav) 'deposit) ;对behav进行解包，如果behav的第一个元素的第一个元素为'deposit，则开始执行存入，判断此处输入的a是不是合法的（大于0）
           (if (> a 0)
               (+ (cadar behav) a) ;如果输入合法，则获取behaviors列表的第一个值(list 'deposit 40)的第二个值（40），并执行余额+40的操作
               -1))
          ( else
            (if (>(- a (cadar behav)) 0) ;如果不为deposit，则执行取出过程，判断余额和需要取的数的差是否大于0
                (- a (cadar behav)) ;若大于零，则获取behaviors列表的第一个值(list 'withdraw 30)的第二个值（30），并执行余额-30的操作
                -1)))))
  
(calculate behaviors));递归调用calculate函数继续运行上面的过程直到behav（解包的列表）为空


;下面两行是尝试调用;withdraw-pureFunc函数
(define behaviors1 (list (list 'withdraw 30) (list 'deposit 80) (list 'withdraw 60) (list 'withdraw 10)))
(withdraw-pureFunc 100 behaviors1)

(define behaviors2 (list (list 'deposit 40) (list 'withdraw 40) (list 'withdraw 60)))
(withdraw-pureFunc 80 behaviors2)





;(define (a)
 ; (define (dispatch m)
  ;  (cond
   ;   ((= m 1) 1)
    ;  ((= m 2) 2)
     ; ((= m 3) 3)
      ;)
    ;)
 ; dispatch)

;((a) 1)