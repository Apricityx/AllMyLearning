# 假设有一个 Job 类型，包含：
#   job.deadline : int   # 截止时间（可用时间槽数）
#   job.profit   : int   # 利润

def sorted_insert(selected_jobs, job):
    """
    把 job 插入到 selected_jobs 中，
    并保持 selected_jobs 按 profit 升序排列（最便宜的在最前面）
    """
    i = 0
    # 找到第一个 profit 大于当前 job 的位置
    while i < len(selected_jobs) and selected_jobs[i].profit <= job.profit:
        i += 1
    # 插入到该位置
    selected_jobs.insert(i, job)


def schedule(jobs):
    """
    输入: jobs 是 Job 的列表
    输出: (最大总利润, 选中的 Job 列表)
    """

    # 1. 按 deadline 升序排序（贪心前提）
    jobs.sort(key=lambda j: j.deadline)

    profit = 0
    selected_jobs = []  # 按 profit 升序维护的集合

    # 2. 逐个考虑排序后的 job
    for job in jobs:
        job_select_count = len(selected_jobs)

        if job_select_count < job.deadline:
            # 还有时间槽，直接加入集合
            # 并保持 selected_jobs 按 profit 升序
            sorted_insert(selected_jobs, job)
            profit += job.profit
        else:
            # 没有多余时间槽了，看看这个 job 是否比当前集合中最便宜的更赚
            if len(selected_jobs) > 0:
                cheapest_job = selected_jobs[0]  # 利润最低的那个
                if job.profit > cheapest_job.profit:
                    # 用更贵的 job 替换掉最便宜的
                    profit -= cheapest_job.profit
                    # 去掉最便宜的（索引 0）
                    selected_jobs.pop(0)
                    # 插入新的 job
                    sorted_insert(selected_jobs, job)
                    profit += job.profit

    # 返回最大利润和对应的 job 集合
    return profit, selected_jobs
