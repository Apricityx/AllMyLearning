import numpy as np
from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score

# 加载 Wine 数据集
wine = load_wine()
X, y = wine.data, wine.target

# 拆分数据集为训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.8, random_state=42)
X_temp, X_test, y_temp, y_test = train_test_split(X, y, test_size=0.3, random_state=42)
model = RandomForestClassifier(random_state=42)
model.fit(X_train, y_train)
y_pred = model.predict(X_test)
accuracy = accuracy_score(y_test, y_pred)
print(f"Random Forest Accuracy before tuning: {accuracy * 100:.2f}%")
param_grid = {
    'n_estimators': [50, 100, 150],  # 尝试减少树的数量
    'max_depth': [10, 15, 20, None],  # 控制树的深度，防止过拟合
    'min_samples_split': [2, 5, 10],  # 增加最小样本分割数量
    'min_samples_leaf': [1, 2, 4],  # 增加最小样本叶节点数量
    'max_features': [None, 'sqrt', 'log2']  # 尝试不同的特征选择方式
}

rf_clf = RandomForestClassifier(random_state=42)

grid_search = GridSearchCV(estimator=rf_clf, param_grid=param_grid, cv=10, n_jobs=-1, verbose=0, error_score='raise')
grid_search.fit(X_train, y_train)

# 获取最佳模型并进行预测
best_rf_clf = grid_search.best_estimator_
rf_y_pred = best_rf_clf.predict(X_test)

# 计算准确率
rf_accuracy = accuracy_score(y_test, rf_y_pred)
print(f"Random Forest Accuracy after tuning: {rf_accuracy * 100:.2f}%")
print(f"Best parameters found: {grid_search.best_params_}")
