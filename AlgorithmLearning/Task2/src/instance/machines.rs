use std::cmp::max;
use std::collections::HashMap;

#[derive(Clone, Debug)]
struct Job {
    id: usize,  // 作业编号
    time1: i64, // 在机器1上的加工时间
    time2: i64, // 在机器2上的加工时间
}

fn remove_index(jobs: &[Job], j: usize) -> Vec<Job> {
    assert!(j < jobs.len());

    let mut v = Vec::with_capacity(jobs.len() - 1);
    v.extend_from_slice(&jobs[..j]);
    v.extend_from_slice(&jobs[j + 1..]);
    v
}

fn T1(jobs: &[Job]) -> i64 {
    jobs.iter().map(|job| job.time1).sum()
}

/// 内部递归 + 记忆化：
/// jobs 表示当前子集 S
fn calculate_internal(
    jobs: &[Job],
    memo: &mut HashMap<Vec<usize>, (i64, Vec<Job>)>,
) -> (i64, Vec<Job>) {
    if jobs.is_empty() {
        return (0, Vec::new());
    }

    let mut key: Vec<usize> = jobs.iter().map(|j| j.id).collect();
    key.sort_unstable();

    // 如果已经算过这个集合，直接返回
    if let Some((best_time, best_seq)) = memo.get(&key) {
        return (*best_time, best_seq.clone());
    }

    if jobs.len() == 1 {
        let j = &jobs[0];
        let result = (j.time1 + j.time2, vec![j.clone()]);
        memo.insert(key, result.clone());
        return result;
    }

    let mut best = i64::MAX;
    let mut best_seq: Vec<Job> = Vec::new();

    let total_t1 = T1(jobs); // T1(S)

    for j in 0..jobs.len() {
        // S - {j}
        let jobs_except_j = remove_index(jobs, j);

        // 递归算 F(S\{j}) 和对应的顺序（带 memo）
        let (prev_best, mut seq) = calculate_internal(&jobs_except_j, memo);

        // 最后一个 job
        let last_job = jobs[j].clone();

        // DP 转移：max(F(S\{j}), T1(S)) + t2_j
        let j_best = max(prev_best, total_t1) + last_job.time2;

        if j_best < best {
            best = j_best;

            seq.push(last_job);
            best_seq = seq;
        }
    }

    // 记忆化存入
    memo.insert(key, (best, best_seq.clone()));

    (best, best_seq)
}

fn calculate(jobs: &[Job]) -> (i64, Vec<Job>) {
    let mut memo: HashMap<Vec<usize>, (i64, Vec<Job>)> = HashMap::new();
    calculate_internal(jobs, &mut memo)
}

pub fn run_demo() {
    let jobs = vec![
        Job { id: 0, time1: 2, time2: 3 },
        Job { id: 1, time1: 4, time2: 1 },
        Job { id: 2, time1: 3, time2: 5 },
    ];
    let (best_time, best_seq) = calculate(&jobs);
    println!("最小完工时间: {}", best_time);
    println!(
        "最优顺序(按 id): {:?}",
        best_seq.iter().map(|j| j.id).collect::<Vec<_>>()
    );
}
