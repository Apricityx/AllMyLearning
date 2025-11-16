use crate::instance::hanoi;

/// 用于计算某一个状态需要用多少次移动才能将所有圆柱从from移动到to
/// # 参数
/// - n 需要移动多少个圆环
/// # 返回
/// - u32 移动次数
fn hanoi(n: u32) -> u32 {
    if n.eq(&1u32) {
        return 1;
    }
    2 * hanoi(n - 1) + 1
}

pub fn run_demo() {
    let count = 4u32;
    let result = hanoi(count);
    println!("The step of hanoi with {} rings is {}", count, result)
}
