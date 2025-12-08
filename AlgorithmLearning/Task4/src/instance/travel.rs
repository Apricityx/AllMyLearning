use std::usize;

struct Solve {
    global_best_traveled_consequence: Vec<usize>, // 最优路径（不含最后回起点那条边）
    global_best_travel_cost: usize,               // 最优总成本（含回到起点）
    global_is_city_traveled: Vec<bool>,           // 城市是否已经走过
    cost_matrix: Vec<Vec<usize>>,
    counter: usize,                               // 统计完整回路数量
}

impl Solve {
    fn dfs(
        &mut self,
        prev_cost: usize,           // 之前所有 cost 总和（走到当前城市）
        traveled_city_count: usize, // 已经走过的城市数量
        travel_city_sequence: &mut Vec<usize>,
    ) {
        let n = self.cost_matrix.len();

        // 所有城市都走过了：计算回到起点的那条边
        if traveled_city_count == n {
            let last = *travel_city_sequence.last().unwrap();
            let first = *travel_city_sequence.first().unwrap();
            let total_cost = prev_cost + self.cost_matrix[last][first];

            // 统计完整回路条数（不管是不是最优）
            self.counter += 1;

            // 更新最优解
            if total_cost < self.global_best_travel_cost {
                self.global_best_travel_cost = total_cost;
                self.global_best_traveled_consequence = travel_city_sequence.clone();
            }
            return;
        }

        for i in 0..n {
            // 第一次选城市，当作起点：只负责枚举起点，不记 cost
            if traveled_city_count == 0 {
                self.global_is_city_traveled[i] = true;
                travel_city_sequence.push(i);

                // 起点之前没有边，所以 prev_cost 还是 0
                self.dfs(0, traveled_city_count + 1, travel_city_sequence);

                self.global_is_city_traveled[i] = false;
                travel_city_sequence.pop();
            } else {
                // 已经访问过的城市跳过
                if self.global_is_city_traveled[i] {
                    continue;
                }

                let prev_city_index = *travel_city_sequence.last().unwrap();
                let edge_cost = self.cost_matrix[prev_city_index][i];
                let next_cost = prev_cost + edge_cost;

                // 剪枝
                if next_cost >= self.global_best_travel_cost {
                    continue;
                }

                // 选择
                self.global_is_city_traveled[i] = true;
                travel_city_sequence.push(i);

                // 递归
                self.dfs(next_cost, traveled_city_count + 1, travel_city_sequence);

                // 撤销选择（回溯）
                self.global_is_city_traveled[i] = false;
                travel_city_sequence.pop();
            }
        }
    }

    fn solve(&mut self) {
        let mut travel_city_sequence = Vec::new();
        self.dfs(0, 0, &mut travel_city_sequence);
    }
}

pub fn run_demo() {
    // 最优回路 0-1-3-2-0，总成本 35
    let cost_matrix = vec![
        vec![0, 10, 15, 20],
        vec![5, 0, 9, 10],
        vec![6, 13, 0, 12],
        vec![8, 8, 9, 0],
    ];

    // let cost_matrix = vec![
    //     vec![4, 2, 5, 2],
    //     vec![3, 3, 2, 4],
    //     vec![5, 4, 3, 2],
    //     vec![2, 4, 6, 3],
    // ];

    let n = cost_matrix.len();
    let mut solver = Solve {
        cost_matrix,
        counter: 0,
        global_best_travel_cost: usize::MAX,
        global_best_traveled_consequence: vec![],
        global_is_city_traveled: vec![false; n],
    };

    solver.solve();
    println!("best_cost = {}", solver.global_best_travel_cost);
    println!("best_consequence = {:?}", solver.global_best_traveled_consequence);
    println!("counter = {}", solver.counter);
}
