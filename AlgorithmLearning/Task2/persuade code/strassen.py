def strassen(A, B):
    """
    Strassen matrix multiplication (Python-style pseudocode).
    假设 A 和 B 是 n x n 的方阵，且 n 为 2 的幂。
    """

    n = size(A)  # 矩阵维度

    # === 基本情况：1x1 矩阵，直接相乘 ===
    if n == 1:
        C = [[0]]
        C[0][0] = A[0][0] * B[0][0]
        return C

    # === 将矩阵分成 4 个子块 ===
    # A = | A11  A12 |
    #     | A21  A22 |
    #
    # B = | B11  B12 |
    #     | B21  B22 |
    A11, A12, A21, A22 = split(A)
    B11, B12, B21, B22 = split(B)

    # === 计算 7 个中间矩阵 M1 ~ M7（递归调用）===
    M1 = strassen(add(A11, A22), add(B11, B22))
    M2 = strassen(add(A21, A22), B11)
    M3 = strassen(A11, sub(B12, B22))
    M4 = strassen(A22, sub(B21, B11))
    M5 = strassen(add(A11, A12), B22)
    M6 = strassen(sub(A21, A11), add(B11, B12))
    M7 = strassen(sub(A12, A22), add(B21, B22))

    # === 用 M1 ~ M7 组合结果子块 C11, C12, C21, C22 ===
    C11 = add(sub(add(M1, M4), M5), M7)
    C12 = add(M3, M5)
    C21 = add(M2, M4)
    C22 = add(sub(add(M1, M3), M2), M6)

    # === 合并 4 个子块得到最终矩阵 C ===
    C = combine(C11, C12, C21, C22)

    return C
