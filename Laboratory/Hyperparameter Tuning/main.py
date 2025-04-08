from sklearn import datasets
from sklearn import linear_model
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.preprocessing import StandardScaler

# 加载数据集
iris = datasets.load_iris()
X = iris.data
y = iris.target

# 划分数据集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)
X_basic, X_valid, y_basic, y_valid = train_test_split(X_train, y_train, test_size=0.3, random_state=42)

# X_train为训练数据集，X_basic和X_valid为训练数据集的划分，X_test为测试数据集

# 标准化数据
scaler = StandardScaler()
X_basic = scaler.fit_transform(X_basic)
X_valid = scaler.transform(X_valid)
X_test = scaler.transform(X_test)
X_train = scaler.transform(X_train)

# 逻辑回归模型
model = linear_model.LogisticRegression(max_iter=200)
# ======================== 1. 直接训练模型，不调参 ========================
model.fit(X_train, y_train)
y_direct_pred = model.predict(X_test)
print("直接训练模型，不调参")
print("验证数据：", y_direct_pred)
print("实际数据：", y_test)
print("准确率：", model.score(X_test, y_test))


# 调整参数的范围
param_grid = {'C': [0.001, 0.01, 0.1, 1, 10, 100]}

# 使用GridSearchCV进行调参
grid_search = GridSearchCV(estimator=model, param_grid=param_grid, cv=5, scoring='accuracy')

# 训练模型
grid_search.fit(X_train, y_train)

# 获取最佳参数
best_model = grid_search.best_estimator_

# 在验证集上预测
y_grid_pred = best_model.predict(X_test)

print("最佳参数：", grid_search.best_params_)
print("验证数据：", y_grid_pred)
print("实际数据：", y_test)
print("准确率：", best_model.score(X_test, y_test))

