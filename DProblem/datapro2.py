import pandas as pd
import json

# 读取节点数据
nodes_df = pd.read_csv('P:/阿里云盘/MCM/25年试题/2025_Problem_D_Data/nodes_all.csv')  # 节点数据

# 读取边数据
edges_df = pd.read_csv('P:/阿里云盘/MCM/25年试题/2025_Problem_D_Data/edges_all.csv')  # 边数据

print("hello1")
# 创建 GeoJSON 数据结构
geojson_data = {
    "type": "FeatureCollection",
    "features": []
}
print("hello2")
# 添加节点到 GeoJSON
for _, row in nodes_df.iterrows():
    geojson_data["features"].append({
        "type": "Feature",
        "geometry": {
            "type": "Point",
            "coordinates": [row['x'], row['y']]  # 经纬度
        },
        "properties": {
            "osmid": row['osmid']
        }
    })
print("hello3")
# 添加边到 GeoJSON
for _, row in edges_df.iterrows():
    # 获取边的起点和终点坐标
    start_node = nodes_df[nodes_df['osmid'] == row['u']].iloc[0]
    end_node = nodes_df[nodes_df['osmid'] == row['v']].iloc[0]

    geojson_data["features"].append({
        "type": "Feature",
        "geometry": {
            "type": "LineString",
            "coordinates": [
                [start_node['x'], start_node['y']],  # 起点坐标
                [end_node['x'], end_node['y']]  # 终点坐标
            ]
        },
        "properties": {
            "osmid": row['osmid']
        }
    })
print("hello4")
# 将 GeoJSON 保存到文件
with open('graph_data.geojson', 'w') as f:
    json.dump(geojson_data, f)
print("hello5")
print("GeoJSON 文件已保存：graph_data.geojson")
