import pandas as pd
import networkx as nx
import matplotlib.pyplot as plt
import numpy as np
import scipy as sp

# Load datasets
bus_routes_path = "Bus_Routes.csv"
edges_all_path = "edges_all.csv"

traffic_data_path = "MDOT_SHA_Annual_Average_Daily_Traffic_Baltimore.csv"

bus_routes = pd.read_csv(bus_routes_path)
edges_all = pd.read_csv(edges_all_path)
traffic_data = pd.read_csv(traffic_data_path)

# Step 1: Data Cleaning
#  edges_all dataset
edges_all['lanes'] = pd.to_numeric(edges_all['lanes'], errors='coerce')
edges_all['maxspeed'] = edges_all['maxspeed'].str.replace(' mph', '').astype(float)

# Fill missing values with median values
edges_all['lanes'].fillna(edges_all['lanes'].median(), inplace=True)
edges_all['maxspeed'].fillna(edges_all['maxspeed'].median(), inplace=True)

# Clean traffic_data dataset
traffic_data['AADT 2022'] = pd.to_numeric(traffic_data['AADT 2022'], errors='coerce')
traffic_data['AADT 2022'].fillna(traffic_data['AADT 2022'].median(), inplace=True)

# Merge edges_all with traffic_data based on common columns (e.g., road names)
edges_all = edges_all.merge(
    traffic_data[['Road Name', 'AADT 2022']],
    left_on='name',
    right_on='Road Name',
    how='left'
)

edges_all['AADT 2022'].fillna(edges_all['AADT 2022'].median(), inplace=True)

# Step 3: Calculate Edge Weights
# Define weights based on length, AADT, and lanes
alpha, beta, gamma = 0.4, 0.4, 0.2
max_length = edges_all['length'].max()
max_aadt = edges_all['AADT 2022'].max()
max_lanes = edges_all['lanes'].max()

def calculate_weight(row):
    length_weight = row['length'] / max_length
    aadt_weight = row['AADT 2022'] / max_aadt
    lanes_weight = row['lanes'] / max_lanes
    return alpha * length_weight + beta * aadt_weight + gamma * lanes_weight

edges_all['weight'] = edges_all.apply(calculate_weight, axis=1)

# Step 4: Build the Traffic Network
# Create a directed graph using NetworkX
G = nx.DiGraph()
for _, row in edges_all.iterrows():
    G.add_edge(
        row['u'], row['v'],
        weight=row['weight'],
        length=row['length'],
        lanes=row['lanes'],
        maxspeed=row['maxspeed']
    )

# Step 5: Visualize the Traffic Network
plt.figure(figsize=(12, 8))
pos = nx.spring_layout(G, seed=42) # Use spring layout for better visualization

# Draw nodes and edges
nx.draw_networkx_nodes(G, pos, node_size=20, node_color='blue', alpha=0.7)
nx.draw_networkx_edges(G, pos, edge_color='gray', alpha=0.5)

# Highlight edges with highest weights
high_weight_edges = [(u, v) for u, v, d in G.edges(data=True) if d['weight'] > 0.8]
nx.draw_networkx_edges(G, pos, edgelist=high_weight_edges, edge_color='red', width=2)

# Add title and legend
plt.title("Traffic Network of Baltimore", fontsize=16)
plt.axis("off")
plt.show()

# Step 6: Analyze the Network
# Compute shortest path based on weights
def compute_shortest_path(graph, source, target):
    return nx.shortest_path(graph, source=source, target=target, weight='weight')

# Example: Compute shortest path between two nodes
try:
    shortest_path = compute_shortest_path(G, source=27029857, target=775383890)
    print("Shortest path (by weight):", shortest_path)
except nx.NetworkXNoPath:
    print("No path exists between the selected nodes.")

# Compute network metrics
average_degree = np.mean([deg for _, deg in G.degree()])
print("Average Degree of the Network:", average_degree)

# Save processed data
edges_all.to_csv("processed_edges_all.csv", index=False)