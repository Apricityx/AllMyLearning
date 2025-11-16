import geopandas as gpd
import pandas as pd
from shapely.geometry import LineString
import matplotlib.pyplot as plt
import contextily as ctx
from matplotlib.colors import Normalize
from matplotlib.cm import ScalarMappable

# Step 1: 加载 Excel 数据
edges_df = pd.read_excel("merged_coordinates.xlsx")  # 替换为你的 Excel 文件路径
print("hello1")
# 检查 Weight 列
if "Weight" not in edges_df.columns:
    raise ValueError("Weight 列不存在！请检查数据。")
edges_df = edges_df.dropna(subset=["Weight"])  # 删除缺失值
print("hello2")
# Step 2: 创建 LineString 几何对象
edges_df['geometry'] = edges_df.apply(
    lambda row: LineString([(row['Source_Lon'], row['Source_Lat']),
                            (row['Target_Lon'], row['Target_Lat'])]),
    axis=1
)

# Step 3: 转换为 GeoDataFrame
edges = gpd.GeoDataFrame(edges_df, geometry='geometry', crs="EPSG:4326")  # 假设坐标系是 WGS 84
print("hello3")
# 检查几何数据
edges = edges[edges.is_valid & ~edges.is_empty]

# 将坐标系转换为 Web Mercator（EPSG:3857）
edges = edges.to_crs(epsg=3857)

# Step 4: 加载巴尔的摩边界数据
baltimore = gpd.read_file("baltimore_boundary.shp")
if baltimore.empty:
    raise ValueError("巴尔的摩边界数据为空，请检查文件路径或数据内容！")
baltimore = baltimore.to_crs(epsg=3857)
print("hello4")
# Step 5: 绘制热力图
fig, ax = plt.subplots(figsize=(12, 12))

# 绘制巴尔的摩边界
baltimore.plot(ax=ax, facecolor="none", edgecolor="black", linewidth=1)

# 绘制边数据，根据权重值着色
norm = Normalize(vmin=edges["Weight"].quantile(0.05), vmax=edges["Weight"].quantile(0.95))  # 使用分位数
cmap = plt.cm.Reds
print("hello5")
for _, row in edges.iterrows():
    weight = row["Weight"]
    color = cmap(norm(weight))  # 根据权重值映射颜色
    ax.plot(
        [coord[0] for coord in row["geometry"].coords],  # X 坐标
        [coord[1] for coord in row["geometry"].coords],  # Y 坐标
        color=color,
        linewidth=2
    )

# 添加底图（例如 OpenStreetMap）
ctx.add_basemap(ax, source=ctx.providers.OpenStreetMap.Mapnik, crs=edges.crs, zoom=12)
print("hello6")
# 限制显示范围（放大到巴尔的摩区域）
xmin, ymin, xmax, ymax = baltimore.total_bounds
ax.set_xlim(xmin, xmax)
ax.set_ylim(ymin, ymax)

# 添加颜色图例
sm = ScalarMappable(cmap=cmap, norm=norm)
sm.set_array([])
fig.colorbar(sm, ax=ax, label="Edge Weight")
print("hello7")
# 设置标题
plt.title("Edge Heatmap on Baltimore Map")
plt.show()
