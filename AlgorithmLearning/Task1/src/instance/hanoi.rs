use crate::instance::hanoi;

/// 用于计算某一个状态需要用多少次移动才能将所有圆柱从from移动到to
/// # 参数
/// - n 需要移动多少个圆环
/// # 返回
/// - u32 移动次数
fn hanoi(n: u32) -> u64 {
    if n.eq(&1u32) {
        return 1;
    }
    2 * hanoi(n - 1) + 1
}

pub fn run_demo() {
    for count in (4..65).step_by(4){
        println!("The step of hanoi with {} rings is {}", count, hanoi(count))
    }
}

use crate::instance::hanoi;

/// 用于计算某一个状态需要用多少次移动才能将所有圆柱从from移动到to
// fn hanoi(n: u32, from: char, aux: char, to: char, moves: &mut Vec<(u32, char, char)>) {
//     if n == 0 {
//         return;
//     }

//     hanoi(n - 1, from, to, aux, moves);

//     moves.push((n, from, to));

//     hanoi(n - 1, aux, from, to, moves);
// }
// fn main() {
//     let n = 4; // 这里随便改，比如 6、10 都可以
//     let mut moves = Vec::new();

//     // 把 n 个盘子从 A 移到 B，C 为辅助塔
//     hanoi(n, 'A', 'C', 'B', &mut moves);

//     println!("Total moves: {}", moves.len());
//     for (disk, from, to) in moves {
//         println!("Move disk {disk} from {from} to {to}");
//     }
// }
type moves = Vec<>;