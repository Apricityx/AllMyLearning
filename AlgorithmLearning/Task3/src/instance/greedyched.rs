#[derive(Clone, Copy, Debug)]
struct Job {
    deadline: i32,
    profit: i64,
    id: i32,
}

// 按 profit 升序插入：最便宜的在前面
fn sorted_insert(jobs: &mut Vec<Job>, new_job: Job) {
    if jobs.is_empty() {
        jobs.push(new_job);
        return;
    }

    let pos = jobs
        .iter()
        .position(|j| j.profit > new_job.profit)
        .unwrap_or(jobs.len());

    jobs.insert(pos, new_job);
}

fn schedule(mut jobs: Vec<Job>) -> (i64, Vec<Job>) {
    // 1. 按 deadline 升序排序（贪心前提）
    jobs.sort_by_key(|j| j.deadline);

    let mut profit: i64 = 0;
    let mut selected_jobs: Vec<Job> = Vec::new();

    for job in jobs {
        let job_select_count = selected_jobs.len() as i32;

        if job_select_count < job.deadline {
            // 还有时间槽，直接插入，并保持按 profit 升序
            sorted_insert(&mut selected_jobs, job);
            profit += job.profit;
        } else {
            // 没有时间槽了，看这个 job 是否值得替换当前集合中最便宜的
            if let Some(cheapest_job) = selected_jobs.first() {
                if job.profit > cheapest_job.profit {
                    profit -= cheapest_job.profit;
                    selected_jobs.remove(0);           // 去掉最便宜的
                    sorted_insert(&mut selected_jobs, job);
                    profit += job.profit;
                }
            }
        }
    }

    (profit, selected_jobs)
}

pub(crate) fn run_demo() {
    let jobs = vec![
        Job { id: 0, deadline: 1, profit: 60 },
        Job { id: 1, deadline: 2, profit: 20 },
        Job { id: 2, deadline: 2, profit: 40 },
        Job { id: 3, deadline: 3, profit: 40 },
        Job { id: 4, deadline: 1, profit: 50 },
    ];

    let (p, selected) = schedule(jobs);
    println!("max profit = {}", p);
    println!("selected jobs = {:?}", selected);
}
