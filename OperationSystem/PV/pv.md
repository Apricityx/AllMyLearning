# PV过程

```C
semaphore 
students = 0 // 学生数量
chairs = 3 // 椅子数量 
ta_sleep = 1 // 助教是否在睡觉
mutex // 互斥锁
helped = 0 // 学生是否得到帮助
```

学生询问问题过程

```C
P(mutex); // 等待共享变量使用完成
if (chairs > 0){
    P(chairs);
    V(ta_sleep);
    V(chairs);
    P(helped)
    leave();
}
else leave();
```

助教解决问题过程

```C
while(true){
    P(ta_sleep);
    help()
    V(helped)
}
```
