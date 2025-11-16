import folium
from selenium import webdriver
from PIL import Image
import time
import geopandas as gpd
# 创建地图
m = folium.Map(location=[39.3, -76.5], zoom_start=12)
print("hello1")
# 加载 GeoJSON 数据
# 读取 GeoJSON 文件
gdf = gpd.read_file("graph_data.geojson")
# 简化几何数据（保留 10% 的细节）
# gdf["geometry"] = gdf["geometry"].simplify(tolerance=0.01, preserve_topology=True)
# # 保存为新的 GeoJSON 文件
# gdf.to_file("simplified_graph_data.geojson", driver="GeoJSON")

print("hello2")
# 保存地图为 HTML 文件
html_file = "map.html"
m.save(html_file)
print("hello3")
# 使用 Selenium 打开 HTML 并截屏
driver = webdriver.Chrome()  # 确保已安装 ChromeDriver，并将其路径加入系统 PATH
driver.set_window_size(1920, 1080)
driver.get(f"file://{html_file}")
time.sleep(3)  # 等待地图加载
print("hello4")
# 截图并保存为图片
screenshot_file = "map_screenshot.png"
driver.save_screenshot(screenshot_file)
# driver.quit()
# 裁剪地图区域（可选，去掉多余边框）
# image = Image.open(screenshot_file)
# # 例如，裁剪地图中间部分
# cropped_image = image.crop((0, 0, 1920, 1080))  # 根据实际需要调整 crop 的参数
# cropped_image.save("map_cropped.png")
# print("hello6")
print("地图截图已保存：map_cropped.png")
