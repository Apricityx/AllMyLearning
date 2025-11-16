import networkx as nx
import random
import matplotlib.pyplot as plt

def create_graph(num_nodes, avg_degree):
    """使用随机图模型创建图，控制平均度数"""
    graph = nx.gnp_random_graph(num_nodes, p=avg_degree / (num_nodes - 1), directed=True) # 使用gnp随机图，p是连接概率
    for node in list(nx.isolates(graph)):
        target = random.choice(list(graph.nodes()))
        graph.add_edge(node, target)

    # 为边随机分配传播概率
    for u, v in graph.edges():
        graph[u][v]['prob'] = random.uniform(0.3, 0.9)
    return graph

def propagation_simulation(graph, initial_infected):
    """传播模拟函数（改进）"""
    infected = set(initial_infected)
    new_infected = set(initial_infected)
    time = 0
    propagation_history = {time: list(infected)}

    while new_infected:
        time += 1
        next_infected = set()
        for i in list(infected):
            for j in graph.successors(i):
                if j not in infected:
                    prob = graph[i][j]['prob']
                    if random.random() < prob:
                        next_infected.add(j)
        infected.update(next_infected)
        new_infected = next_infected - infected
        propagation_history[time] = list(infected)
        if len(infected) == graph.number_of_nodes(): #如果所有节点都被感染，则停止模拟
            break

    return infected, propagation_history

# 设置参数
num_nodes = 50
avg_degree = 10
initial_infected = [random.randint(0, num_nodes - 1)] # 随机选择初始感染节点

# 创建图
graph = create_graph(num_nodes, avg_degree)

# 传播模拟
final_infected, history = propagation_simulation(graph, initial_infected)

print("\n最终感染节点:", final_infected)
print("传播历史:", history)
print("感染比例:", len(final_infected)/num_nodes)

pos = nx.spring_layout(graph)
nx.draw(graph, pos, with_labels=True, node_size=100, font_size=6)
plt.show()

def identify_key_nodes(graph):
    degree_centrality = nx.degree_centrality(graph)
    return degree_centrality

key_nodes = identify_key_nodes(graph)
print("\n度中心性:", key_nodes)

most_influential_node = max(key_nodes, key=key_nodes.get)
print(f"度中心性最高的节点: {most_influential_node}, 中心性值: {key_nodes[most_influential_node]:.2f}")