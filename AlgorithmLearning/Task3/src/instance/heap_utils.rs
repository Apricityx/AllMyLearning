use std::cmp::{Reverse, Ordering};
use std::collections::BinaryHeap;

#[derive(Debug, Clone, Eq, PartialEq)]
pub struct File {
    pub ids: Vec<u32>,
    pub size: u32,
}

// 合并多个 File
pub fn merge_file(files: Vec<File>) -> File {
    let mut total_size = 0;
    let mut ids = Vec::new();
    for file in files {
        total_size += file.size;
        for id in file.ids {
            ids.push(id);
        }
    }
    File {
        ids: ids,
        size: total_size,
    }
}

/// 让 File 可以比较大小（按 size 排序）
/// BinaryHeap<Reverse<File>> 会把 size 最小的 File 当作“优先级最高”
impl Ord for File {
    fn cmp(&self, other: &Self) -> Ordering {
        self.size.cmp(&other.size)
    }
}

impl PartialOrd for File {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

/// 把各种“文件集合”转换成最小堆（BinaryHeap<Reverse<File>>）
pub trait IntoMinHeap {
    fn into_min_heap(self) -> BinaryHeap<Reverse<File>>;
}

// 情况 1：传切片 &[File]
impl<'a> IntoMinHeap for &'a [File] {
    fn into_min_heap(self) -> BinaryHeap<Reverse<File>> {
        // File 不是 Copy，只能 clone
        self.iter().cloned().map(Reverse).collect()
    }
}

// 情况 2：传 Vec<File>
impl IntoMinHeap for Vec<File> {
    fn into_min_heap(self) -> BinaryHeap<Reverse<File>> {
        // 拿走所有权，直接 into_iter
        self.into_iter().map(Reverse).collect()
    }
}

// 情况 3：本来就是最小堆，就直接返回自己
impl IntoMinHeap for BinaryHeap<Reverse<File>> {
    fn into_min_heap(self) -> BinaryHeap<Reverse<File>> {
        self
    }
}
