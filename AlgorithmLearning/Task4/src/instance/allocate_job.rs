struct Solver {
    job_matrix: Vec<Vec<usize>>,
    global_assigned_jobs: Vec<usize>,
    global_best_cost: usize,
    used_job: Vec<bool>,
    counter: usize,
    rest_of_cheapest_worker:Vec<usize>
}
impl Solver {
    fn dfs(&mut self, prev_cost: usize, curr_line: usize, assigned_jobs: &mut Vec<usize>) {
        let n = self.job_matrix.len();
        if curr_line == n {
            // 已经到叶子，触发结束条件
            self.counter += 1; // 统计完整方案条数
            if prev_cost < self.global_best_cost {
                self.global_best_cost = prev_cost;
                self.global_assigned_jobs = assigned_jobs.to_vec();
            }
            return;
        }
        
        // 剪枝
        if self.rest_of_cheapest_worker[curr_line] + prev_cost > self.global_best_cost{
            return;
        }

        for i in 0..n {
            if self.used_job[i] {
                continue;
            }

            let worker_cost = self.job_matrix[curr_line][i];

            // 做选择
            self.used_job[i] = true;
            assigned_jobs.push(i);

            self.dfs(prev_cost + worker_cost, curr_line + 1, assigned_jobs);

            // 撤销选择
            assigned_jobs.pop();
            self.used_job[i] = false;
        }
    }
    fn solve(&mut self) {
        let mut cost = 0;
        for i in 0..self.job_matrix.len(){
            cost += self.job_matrix[i].iter().copied().min().unwrap();
            self.rest_of_cheapest_worker.push(cost);
        }
        println!("{:?}",self.rest_of_cheapest_worker);

        let mut assigned_jobs = Vec::new();
        self.dfs(0, 0,&mut assigned_jobs)
    }
}


pub fn run_demo() {
    let job_matrix = vec![
        vec![4, 2, 5, 2],
        vec![3, 3, 2, 4],
        vec![5, 4, 3, 2],
        vec![2, 4, 6, 3],
    ];
    let n = job_matrix.len();
    let mut solver = Solver {
        job_matrix,
        global_assigned_jobs: vec![0; n],
        global_best_cost: usize::MAX,
        used_job:vec![false;n],
        counter:0,
        rest_of_cheapest_worker:vec![],
    };

    solver.solve();
    println!("best_cost = {}\n", solver.global_best_cost);
    println!("best_vec = {:?}",solver.global_assigned_jobs);
    println!("counter = {:?}",solver.counter);
}
