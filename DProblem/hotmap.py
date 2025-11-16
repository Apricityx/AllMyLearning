import pandas as pd
import folium
from shapely.wkt import loads
from shapely.geometry import LineString
import branca.colormap as cm

# Step 1: 读取 Excel 文件
input_file = "routeData.xlsx"  # 替换为你的文件名
df = pd.read_excel(input_file)

# 填充 NaN 值
df['Weight'] = df['Weight'].fillna(0)

# 将字符串解析为几何对象
df['geometry'] = df['geometry'].apply(loads)

# 检查解析结果
print(df['geometry'].head())

# 设置初始位置
initial_location = [df['geometry'][0].coords[0][1], df['geometry'][0].coords[0][0]]
print("初始位置:", initial_location)


# Step 2: 解析几何数据 (geometry 列)
def parse_linestring(geometry):
    geometry = geometry.replace("LINESTRING (", "").replace(")", "")
    coords = [tuple(map(float, coord.split())) for coord in geometry.split(", ")]
    return LineString(coords)

# Step 3: 检查权重列
df['Weight'].fillna(0, inplace=True)  # 将 NaN 填充为 0
if df['Weight'].isnull().any():
    print("警告: 权重列中存在 NaN 值，请清理数据！")
    df = df.dropna(subset=['Weight'])

min_weight = df['Weight'].min()
max_weight = df['Weight'].max()

if min_weight >= max_weight:
    raise ValueError("权重列的最小值和最大值无效，无法生成颜色映射！")

# Step 4: 创建 Folium 地图
initial_location = [df['geometry'][0].coords[0][1], df['geometry'][0].coords[0][0]]
mymap = folium.Map(location=initial_location, zoom_start=14)

# Step 5: 创建颜色映射
colormap = cm.LinearColormap(colors=['blue', 'green', 'yellow', 'red'], vmin=min_weight, vmax=max_weight)
colormap.caption = "Road Weight Heatmap"
mymap.add_child(colormap)

# Step 6: 绘制每条道路
for _, row in df.iterrows():
    line = row['geometry']
    weight = row['Weight']
    color = colormap(weight)
    coords = [(point[1], point[0]) for point in line.coords]

    folium.PolyLine(
        locations=coords,
        color=color,
        weight=5,
        opacity=0.8,
        popup=f"{row['name']}: {weight:.2f}"
    ).add_to(mymap)

# Step 7: 保存地图
output_file = "road_heatmap.html"
mymap.save(output_file)
print(f"热力图已保存为: {output_file}")
