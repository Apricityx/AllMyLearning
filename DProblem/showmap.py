import geopandas as gpd
import matplotlib.pyplot as plt
import contextily as ctx

# 加载巴尔的摩边界（从步骤 1 获取）
baltimore = gpd.read_file("baltimore_boundary.shp")

# 将边界投影转换为 Web Mercator（EPSG:3857），以匹配瓦片地图
baltimore = baltimore.to_crs(epsg=3857)

# 绘制巴尔的摩边界和地形底图
fig, ax = plt.subplots(figsize=(10, 10))
baltimore.plot(ax=ax, facecolor="none", edgecolor="red", linewidth=2)

# 添加地形底图
ctx.add_basemap(ax, source=ctx.providers.OpenStreetMap.Mapnik)

plt.title("Baltimore, Maryland, USA - Terrain Map")
plt.show()