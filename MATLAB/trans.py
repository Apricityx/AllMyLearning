# 读取excel表1.xlsx的每行，将其转为列储存在2.xlsx中
import pandas as pd

import pandas as pd

df = pd.read_excel("src/1.xlsx")
years = df.columns.values.tolist()
# 读取第2行数据
nums = df.iloc[0].values.tolist()

print(years)
print(nums)
# 将years输出到2.xlsx的第一列
# 将nums输出到2.xlsx的第二列
df = pd.DataFrame({"years": years, "nums": nums})
df.to_excel("src/2.xlsx", index=False)
# Compare this snippet from Regression%20models.py:
