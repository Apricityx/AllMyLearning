// 目标：查找有序列表中是否存在某个数
pub fn binary_search(arr: &[i32], finding: i32) -> i32 {
    let size: i32 = arr.len() as i32;
    let mid: usize = (size / 2) as usize;
    if size == 0 {
        0
    } else if arr[mid] == finding {
        1
    } else if arr[mid] > finding {
        binary_search(&arr[0..mid], finding)
    } else {
        binary_search(&arr[(mid + 1)..size as usize], finding)
    }
}
