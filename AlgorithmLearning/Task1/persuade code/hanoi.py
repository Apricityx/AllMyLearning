def hanoi(n, from_rod, via_rod, to_rod):
    if n == 1:
        print(f"{from_rod} -> {to_rod}")
    else:
        hanoi(n - 1, from_rod, to_rod, via_rod) # 移动到临时柱
        print(f"{from_rod} -> {to_rod}")
        hanoi(n - 1, via_rod, from_rod, to_rod) # 回到递归初始态