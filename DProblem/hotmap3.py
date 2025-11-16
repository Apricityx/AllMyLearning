import pandas as pd
import geopandas as gpd
from shapely import wkt
import matplotlib.pyplot as plt
import contextily as ctx
from scipy.stats import gaussian_kde
import numpy as np

# Step 1: 加载 Excel 数据
# 替换为你的 Excel 文件路径
excel_file = "withoutFlood.xls"  # 替换为实际文件名
edges_df = pd.read_excel(excel_file)

# Step 2: 将 WKT 字段转换为几何对象
# 确保 "geometry" 列包含有效的 WKT 格式
edges_df['geometry'] = edges_df['geometry'].apply(wkt.loads)

# Step 3: 转换为 GeoDataFrame
edges_gdf = gpd.GeoDataFrame(edges_df, geometry='geometry', crs="EPSG:4326")  # 使用 WGS 84 坐标系

# Step 4: 提取节点信息
# 从 "u" 和 "v" 列提取节点坐标
nodes = pd.concat([
    edges_df[['u', 'geometry']].rename(columns={'u': 'node'}),
    edges_df[['v', 'geometry']].rename(columns={'v': 'node'})
]).drop_duplicates(subset=['node'])

# 提取节点坐标
nodes['lon'] = nodes['geometry'].apply(lambda geom: geom.coords[0][0])
nodes['lat'] = nodes['geometry'].apply(lambda geom: geom.coords[0][1])

# 转换为 GeoDataFrame
nodes_gdf = gpd.GeoDataFrame(nodes, geometry=gpd.points_from_xy(nodes['lon'], nodes['lat']), crs="EPSG:4326")

# Step 5: 计算节点密度
# 提取节点的经纬度坐标
coords = np.vstack([nodes['lon'], nodes['lat']])
kde = gaussian_kde(coords)  # 使用高斯核密度估计
nodes['density'] = kde(coords)  # 计算每个节点的密度

# 将密度值归一化以便可视化
nodes['norm_density'] = (nodes['density'] - nodes['density'].min()) / (nodes['density'].max() - nodes['density'].min())

# 更新 GeoDataFrame
nodes_gdf['density'] = nodes['density']
nodes_gdf['norm_density'] = nodes['norm_density']

# Step 6: 在地图上绘制节点和边
fig, ax = plt.subplots(figsize=(12, 12))

# 绘制边（线段）
edges_gdf.plot(ax=ax, color="blue", linewidth=0.5, label="Edges")

# 绘制节点，根据密度值动态调整颜色
nodes_gdf.plot(
    ax=ax,
    column='norm_density',  # 使用归一化的密度值作为颜色映射
    cmap='YlOrRd',  # 使用黄色到红色渐变色
    markersize=10,
    legend=True,
    alpha=0.8
)

# 添加底图（OpenStreetMap）
ctx.add_basemap(ax, source=ctx.providers.OpenStreetMap.Mapnik, crs=edges_gdf.crs)

# 设置图例和标题
ax.set_title("Node Density Heatmap on OpenStreetMap", fontsize=16)

# 显示地图
plt.show()
