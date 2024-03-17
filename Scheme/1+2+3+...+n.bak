#lang sicp
#|再留一道思考题。作为本周的挑战性题目。
假定你面前有这样一台计算机，它上面只有一个drracket的超级青春版。
这个简化版软件只进行自然数的计算，所能用的过程只有一个过程inc，(inc n)的数值结果是n+1。除此以外不支持其他任何计算，包括加减乘除求余数。
好消息是这个青春版的drracket支持递归定义。
请在这种情况下编写递归程序实现加法。|#
(define greeting "请输入两个值，中间用换行的方式分割;") ;给字符串赋值
(define a (read))
(define b (read))

(define (plus input1 input2)
  ;具体实现
          ;3个参数，sum代表结果(内存为input1)   times代表需要+1的次数(input2) counter代表计数器
(define (counting sum times counter)
(if (< counter times)

    (begin
        (counting (inc sum) times (inc counter))
    );T begin执行多个语句

    (begin
        sum
        ;F
    )

)
  )
  (counting input1 input2 0)
)


(plus a b)








                      