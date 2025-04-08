import gymnasium as gym
import numpy as np
import random
from collections import defaultdict

# 创建环境（请确保已安装 gym_game2048，并能创建 "game2048-v0" 环境）
env = gym.make("game2048-v0", board_size=4, seed=42, binary=False, extractor="mlp", penalty=-10)

# 定义 Q 表，使用 defaultdict，每个状态对应一个长度为动作数的 np.array
Q = defaultdict(lambda: np.zeros(env.action_space.n))

# 参数设置
num_episodes = 10000  # 总共训练的局数，可根据实际情况调整
alpha = 0.1  # 学习率
gamma = 0.99  # 折扣因子
epsilon = 1.0  # 初始探索率
epsilon_min = 0.1  # 最小探索率
epsilon_decay = 0.9995  # 每个 episode 后衰减因子


def get_state_key(state):
    """
    将环境状态转换为不可变类型（元组），作为 Q 表的 key。
    这里假设状态是一个 numpy 数组（例如 4x4），使用 flatten() 后转换为元组。
    """
    return tuple(state.flatten())


def choose_action(state_key):
    """
    ε-greedy 策略选择动作：
      - 以 epsilon 的概率随机选择一个动作；
      - 否则选择 Q 值最大的动作。
    """
    if random.random() < epsilon:
        return env.action_space.sample()
    else:
        return int(np.argmax(Q[state_key]))


for episode in range(num_episodes):
    state = env.reset()
    state_key = get_state_key(state)
    done = False
    total_reward = 0

    while not done:
        # 根据 ε-greedy 策略选择动作
        action = choose_action(state_key)
        next_state, reward, done, _ = env.step(action)
        next_state_key = get_state_key(next_state)
        total_reward += reward

        # Q-learning 更新公式：
        # 如果已经结束，则 td_target = reward，否则 td_target = reward + gamma * max(Q[next_state])
        td_target = reward if done else reward + gamma * np.max(Q[next_state_key])
        td_error = td_target - Q[state_key][action]
        Q[state_key][action] += alpha * td_error

        # 状态转换
        state_key = next_state_key

    # 每个 episode 结束后衰减 epsilon
    if epsilon > epsilon_min:
        epsilon *= epsilon_decay

    if episode % 100 == 0:
        print(f"Episode {episode}, Total Reward: {total_reward:.2f}, Epsilon: {epsilon:.4f}")

print("训练结束！")
