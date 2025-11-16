import geopandas as gpd

# 从 US Census TIGER 数据加载巴尔的摩边界
url = "https://www2.census.gov/geo/tiger/TIGER2021/PLACE/tl_2021_24_place.zip"
baltimore_boundary = gpd.read_file(url)
print("hello1")
# 筛选出巴尔的摩
baltimore = baltimore_boundary[baltimore_boundary["NAME"] == "Baltimore"]
print(baltimore)
# 保存为 Shapefile 文件
baltimore.to_file("baltimore_boundary.shp")
print("hello2")