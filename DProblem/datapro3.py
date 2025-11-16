import pandas as pd
import json

# 读取节点数据
nodes_df = pd.read_csv('P:/阿里云盘/MCM/25年试题/2025_Problem_D_Data/nodes_all.csv')  # 节点数据

# 读取边数据
edges_df = pd.read_csv('processed_wieght_file.xlsx')  # 边数据

# 创建 GeoJSON 数据结构
geojson_data = {
    "type": "FeatureCollection",
    "features": []
}

# 添加节点到 GeoJSON
for _, row in nodes_df.iterrows():
    # 检查节点坐标是否有效
    if pd.notnull(row['x']) and pd.notnull(row['y']):
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

# 添加边到 GeoJSON
for _, row in edges_df.iterrows():
    try:
        # 查找起点和终点
        start_node = nodes_df[nodes_df['osmid'] == row['u']].iloc[0]
        end_node = nodes_df[nodes_df['osmid'] == row['v']].iloc[0]

        # 检查起点和终点坐标是否有效
        if pd.notnull(start_node['x']) and pd.notnull(start_node['y']) and pd.notnull(end_node['x']) and pd.notnull(end_node['y']):
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
    except IndexError:
        print(f"警告：未找到边的起点或终点，边 osmid: {row['osmid']} 被跳过。")
    except Exception as e:
        print(f"错误：处理边 osmid: {row['osmid']} 时出错，错误信息：{e}")

# 将 GeoJSON 保存到文件
try:
    with open('graph_data.geojson', 'w') as f:
        json.dump(geojson_data, f, indent=4)  # 使用缩进保存，方便检查格式
    print("GeoJSON 文件已保存：graph_data.geojson")
except Exception as e:
    print(f"错误：保存 GeoJSON 文件时出错，错误信息：{e}")
