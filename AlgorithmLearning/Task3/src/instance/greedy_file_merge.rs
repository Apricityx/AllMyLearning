use crate::instance::heap_utils::{File, IntoMinHeap, merge_file};
use std::cmp::Reverse;

/// 贪心算法实现文件合并问题
/// 采用泛型编程实现无论传入数组还是最小堆都统一为最小堆处理
///
/// # 参数
/// - `files`: 一个包含所有文件大小的向量
/// - `k`: k元合并
fn optimal_merge<F>(files: F, k: i32)
where
    F: IntoMinHeap,
{
    let mut heap = files.into_min_heap();
    // 使用大小为0的元素填充files，使其长度为k的倍数
    while (heap.len() - 1) % (k - 1) as usize != 0 {
        heap.push(Reverse(File {
            ids: vec![],
            size: 0,
        }));
    }

    while heap.len() > 1 {
        let mut to_merge = Vec::new();
        for i in 0..k {
            // 模式匹配语法
            if let Some(Reverse(file)) = heap.pop() {
                to_merge.push(file);
            }
        }
        println!("将以下文件合并: {:?}", to_merge.iter().map(|f| f.ids.clone()).collect::<Vec<_>>());
        let merged_file = merge_file(to_merge);
        heap.push(Reverse(merged_file));
    }
    if let Some(Reverse(final_file)) = heap.pop() {
        println!("合并后的文件大小: {}", final_file.size);
    }
}

pub fn run_demo() {
    let files = vec![
        File {
            ids: vec![0, 1],
            size: 30,
        },
        File {
            ids: vec![2],
            size: 10,
        },
        File {
            ids: vec![3],
            size: 25,
        },
        File {
            ids: vec![4],
            size: 23,
        },
        File {
            ids: vec![5],
            size: 12,
        },
    ];
    let k = 3;
    optimal_merge(files, k);
}