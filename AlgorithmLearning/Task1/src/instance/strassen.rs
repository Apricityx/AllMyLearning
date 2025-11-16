type Matrix = Vec<Vec<i32>>;

fn assert_same_shape(a: &Matrix, b: &Matrix) {
    assert!(!a.is_empty() && !b.is_empty(), "矩阵不能为空");
    assert_eq!(a.len(), b.len(), "行数不一致");
    assert_eq!(a[0].len(), b[0].len(), "列数不一致");
}

fn matrix_add(a: &Matrix, b: &Matrix) -> Matrix {
    assert_same_shape(a, b);
    let (r, c) = (a.len(), a[0].len());
    let mut res = vec![vec![0; c]; r];
    for i in 0..r {
        for j in 0..c {
            res[i][j] = a[i][j] + b[i][j];
        }
    }
    res
}

fn matrix_sub(a: &Matrix, b: &Matrix) -> Matrix {
    assert_same_shape(a, b);
    let (r, c) = (a.len(), a[0].len());
    let mut res = vec![vec![0; c]; r];
    for i in 0..r {
        for j in 0..c {
            res[i][j] = a[i][j] - b[i][j];
        }
    }
    res
}

fn print_matrix(m: &Matrix) {
    for row in m {
        for &val in row {
            print!("{}\t", val); // 修正为整型打印
        }
        println!();
    }
}

fn split_matrix(m: &Matrix) -> (Matrix, Matrix, Matrix, Matrix) {
    assert!(!m.is_empty());
    let (r, c) = (m.len(), m[0].len());
    assert_eq!(r, c, "Strassen 仅示例方阵");
    assert_eq!(r % 2, 0, "维度需为偶数（或先 padding）");

    let mr = r / 2;
    let mc = c / 2;

    let mut a11 = vec![vec![0; mc]; mr];
    let mut a12 = vec![vec![0; c - mc]; mr];
    let mut a21 = vec![vec![0; mc]; r - mr];
    let mut a22 = vec![vec![0; c - mc]; r - mr];

    for i in 0..mr {
        for j in 0..mc {
            a11[i][j] = m[i][j];
        }
        for j in mc..c {
            a12[i][j - mc] = m[i][j];
        }
    }
    for i in mr..r {
        for j in 0..mc {
            a21[i - mr][j] = m[i][j];
        }
        for j in mc..c {
            a22[i - mr][j - mc] = m[i][j];
        }
    }
    (a11, a12, a21, a22)
}

fn combine(a11: Matrix, a12: Matrix, a21: Matrix, a22: Matrix) -> Matrix {
    let (tr, br) = (a11.len(), a21.len());
    let (lc, rc) = (a11[0].len(), a12[0].len());
    let (r, c) = (tr + br, lc + rc);
    let mut res = vec![vec![0; c]; r];

    for i in 0..tr {
        for j in 0..lc {
            res[i][j] = a11[i][j];
        }
        for j in 0..rc {
            res[i][lc + j] = a12[i][j];
        }
    }
    for i in 0..br {
        for j in 0..lc {
            res[tr + i][j] = a21[i][j];
        }
        for j in 0..rc {
            res[tr + i][lc + j] = a22[i][j];
        }
    }
    res
}

fn strassen(a: &Matrix, b: &Matrix) -> Matrix {
    assert!(!a.is_empty() && !b.is_empty());
    assert_eq!(a.len(), a[0].len(), "仅支持方阵");
    assert_eq!(b.len(), b[0].len(), "仅支持方阵");
    assert_eq!(a.len(), b.len(), "两个方阵必须同阶");

    let n = a.len();
    if n == 1 {
        return vec![vec![a[0][0] * b[0][0]]];
    }

    let (a11, a12, a21, a22) = split_matrix(a);
    let (b11, b12, b21, b22) = split_matrix(b);

    let m1 = strassen(&matrix_add(&a11, &a22), &matrix_add(&b11, &b22));
    let m2 = strassen(&matrix_add(&a21, &a22), &b11);
    let m3 = strassen(&a11, &matrix_sub(&b12, &b22));
    let m4 = strassen(&a22, &matrix_sub(&b21, &b11));
    let m5 = strassen(&matrix_add(&a11, &a12), &b22);
    let m6 = strassen(&matrix_sub(&a21, &a11), &matrix_add(&b11, &b12));
    let m7 = strassen(&matrix_sub(&a12, &a22), &matrix_add(&b21, &b22));

    let c11 = matrix_add(&matrix_sub(&matrix_add(&m1, &m4), &m5), &m7);
    let c12 = matrix_add(&m3, &m5);
    let c21 = matrix_add(&m2, &m4);
    // 修正：C22 = M1 - M2 + M3 + M6
    let c22 = matrix_add(&matrix_add(&matrix_sub(&m1, &m2), &m3), &m6);

    combine(c11, c12, c21, c22)
}

pub fn run_demo(){
    // 改成 2×2 方阵示例（维度为偶数，便于 split）
    let a: Matrix = vec![
        vec![7, 8, 9, 10],
        vec![1, 2, 3, 4],
        vec![3, 4, 5, 6],
        vec![4, 5, 6, 7],
    ];
    let b: Matrix = vec![
        vec![1, 2, 3, 4],
        vec![4, 5, 6, 7],
        vec![7, 8, 9, 10],
        vec![11, 12, 13, 14],
    ];

    let c = strassen(&a, &b);
    print_matrix(&c);
}