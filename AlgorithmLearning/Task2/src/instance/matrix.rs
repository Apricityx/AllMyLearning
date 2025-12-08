use std::cmp::max;

type Matrix = Vec<Vec<i32>>;

/// 打印矩阵
fn print_matrix(m: &Matrix) {
    for row in m {
        for &val in row {
            print!("{}\t", val);
        }
        println!();
    }
}

/// 普通 O(n^3) 矩阵乘法：C = A × B
fn matrix_mul(a: &Matrix, b: &Matrix) -> Matrix {
    assert!(!a.is_empty() && !b.is_empty(), "矩阵不能为空");
    let (ar, ac) = (a.len(), a[0].len());
    let (br, bc) = (b.len(), b[0].len());
    assert_eq!(
        ac, br,
        "矩阵维度不匹配，无法相乘: {}x{} * {}x{}",
        ar, ac, br, bc
    );

    let mut c = vec![vec![0i32; bc]; ar];
    for i in 0..ar {
        for k in 0..ac {
            let aik = a[i][k];
            for j in 0..bc {
                c[i][j] += aik * b[k][j];
            }
        }
    }
    c
}

/// 维度数组 dims：长度 = n+1
/// 第 i 个矩阵 A_i 的大小是 dims[i] × dims[i+1]
/// 返回:
/// m[i][j]: Ai..Aj 连乘的最小标量乘法次数
/// s[i][j]: 达到最优时的分割点 k
fn matrix_chain_order(dims: &[usize]) -> (Vec<Vec<i64>>, Vec<Vec<usize>>) {
    let n = dims.len() - 1; // 矩阵个数
    let mut m = vec![vec![0i64; n]; n];
    let mut s = vec![vec![0usize; n]; n];

    // l 是链长，2..=n
    for l in 2..=n {
        for i in 0..=n - l {
            let j = i + l - 1;
            m[i][j] = i64::MAX;
            for k in i..j {
                // 代价 = 左区间 + 右区间 + 当前这次乘法的代价
                let cost = m[i][k] + m[k + 1][j] + (dims[i] * dims[k + 1] * dims[j + 1]) as i64;

                if cost < m[i][j] {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
    (m, s)
}

/// 按最优括号顺序做实际的矩阵连乘
/// mats: 原始矩阵数组
/// s:    DP 中记录的划分点
/// i,j:  当前要计算的区间 [i, j]
fn matrix_chain_multiply(mats: &[Matrix], s: &Vec<Vec<usize>>, i: usize, j: usize) -> Matrix {
    if i == j {
        return mats[i].clone();
    }
    let k = s[i][j];
    let left = matrix_chain_multiply(mats, s, i, k);
    let right = matrix_chain_multiply(mats, s, k + 1, j);
    matrix_mul(&left, &right)
}

/// 从一串矩阵推导 dims 数组
/// mats[0] 大小: r0 × c0
/// mats[1] 大小: r1 × c1，要求 r1 = c0，以此类推
/// dims = [r0, c0 (=r1), c1 (=r2), ..., c_{n-1}]
fn infer_dims(mats: &[Matrix]) -> Vec<usize> {
    assert!(!mats.is_empty(), "矩阵链不能为空");

    let n = mats.len();
    let mut dims = Vec::with_capacity(n + 1);

    let r0 = mats[0].len();
    let c0 = mats[0][0].len();
    dims.push(r0);
    let mut prev_cols = c0;
    dims.push(prev_cols);

    for (idx, m) in mats.iter().enumerate().skip(1) {
        let (r, c) = (m.len(), m[0].len());
        prev_cols = c;
        dims.push(prev_cols);
    }

    dims
}

pub fn run_demo() {
    // 构造三个可以连乘的矩阵 A(2×3), B(3×4), C(4×2)
    let a: Matrix = vec![vec![1, 2, 3], vec![4, 5, 6]]; // 2x3

    let b: Matrix = vec![
        vec![7, 8, 9, 10],
        vec![11, 12, 13, 14],
        vec![15, 16, 17, 18],
    ]; // 3x4

    let c: Matrix = vec![vec![1, 2], vec![3, 4], vec![5, 6], vec![7, 8]]; // 4x2

    // let d: Matrix = vec![vec![1, 2, 4, 7], vec![3, 4, 7, 8]]; // 4x2

    // let mats = vec![a, b, c, d];
    let mats = vec![a, b, c];

    // 推导维度数组 dims
    let dims = infer_dims(&mats);
    println!("dims = {:?}", dims);

    // DP 求最优加括号（最少乘法次数）
    let (m, s) = matrix_chain_order(&dims);
    let n = mats.len();
    println!("最少乘法次数: {}", m[0][n - 1]);

    // 按最优括号顺序做实际矩阵连乘
    let result = matrix_chain_multiply(&mats, &s, 0, n - 1);
    println!("连乘结果矩阵:");
    print_matrix(&result);
}
