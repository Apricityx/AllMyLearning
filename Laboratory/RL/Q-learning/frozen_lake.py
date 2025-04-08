import gymnasium as gym
import numpy as np
import random

# 创建环境，未启用渲染
env = gym.make('FrozenLake-v1',
               desc=None,
               map_name="4x4",
               is_slippery=False,
               render_mode=None)  # 不渲染

# 获取状态和动作的数量
n_states = env.observation_space.n
n_actions = env.action_space.n

Q = np.zeros((n_states, n_actions))

total_episodes = 10000
max_steps = 50

alpha = 0.8      # 学习率
gamma = 0.95     # 折扣因子
epsilon = 1.0    # 初始探索率
min_epsilon = 0.01  # 最低探索率
decay_rate = 0.995  # 衰减率

# 训练过程
for episode in range(total_episodes):
    state, info = env.reset()
    done = False

    for step in range(max_steps):
        # 使用 ε-greedy 策略选择动作：
        if random.uniform(0, 1) < epsilon:
            # 探索：随机选择动作
            action = env.action_space.sample()
        else:
            # 利用：选择 Q 值最大的动作
            action = np.argmax(Q[state, :])

        new_state, reward, terminated, truncated, info = env.step(action)
        done = terminated or truncated

        # Q-learning 更新公式
        Q[state, action] = Q[state, action] + alpha * (
            reward + gamma * np.max(Q[new_state, :]) - Q[state, action]
        )

        state = new_state

        if done:
            break

    # 衰减 epsilon
    epsilon = max(min_epsilon, epsilon * decay_rate)

print("训练完成")
print("最终 Q 表：")
print(Q)

# 创建环境，启用渲染
env = gym.make('FrozenLake-v1',
               desc=None,
               map_name="4x4",
               is_slippery=False,
               render_mode="human")

for test_episode in range(10):
    state, info = env.reset()
    done = False
    print(f"测试 {test_episode + 1}:")
    while not done:
        action = np.argmax(Q[state, :])
        state, reward, terminated, truncated, info = env.step(action)
        done = terminated or truncated
        env.render()
    print()

env.close()
