from PIL import Image
import numpy as np
import tensorflow as tf
import tensorflow_datasets as tfds
import tkinter as tk
from tkinter import filedialog

def show_image(image):  # image = ds.take(1)
    image_np = image.numpy().squeeze()  # 从 (28, 28, 1) 转为 (28, 28)
    # 翻转图像（EMNIST 图像可能是左右翻转的）
    image_np = np.fliplr(image_np)
    image_np = np.rot90(image_np, 1)
    # 转换为 Pillow 图像
    image_pil = Image.fromarray(image_np.astype(np.uint8))
    # 显示图像
    image_pil.show()

# noinspection PyUnresolvedReferences
from tensorflow.keras import layers, models

# 加载 EMNIST 数据集（字母部分）
ds, info = tfds.load('emnist/letters', split='train', with_info=True, as_supervised=True)
ds_test = tfds.load('emnist/letters', split='test', as_supervised=True)

def preprocess(image, label):
    image = tf.cast(image, tf.float32) / 255.0  # 归一化
    image = tf.reshape(image, (-1,))  # 展平为784维向量（28x28）
    label = label - 1  # 标签从1-26调整为0-25
    return image, label

ds = ds.map(preprocess).batch(32).prefetch(tf.data.AUTOTUNE)
ds_test = ds_test.map(preprocess).batch(32).prefetch(tf.data.AUTOTUNE)

# 构建全连接神经网络
model = models.Sequential([
    layers.Dense(128, activation='relu', input_shape=(784,)),  # 输入784维
    layers.Dropout(0.2),  # 防止过拟合
    layers.Dense(64, activation='relu'),
    layers.Dropout(0.2),
    layers.Dense(26, activation='softmax')  # 输出26类（字母A-Z）
])

# 编译模型
model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])

# 训练模型
model.fit(ds, epochs=10, validation_data=ds_test)

# 评估模型
test_loss, test_accuracy = model.evaluate(ds_test)
print(f"Test accuracy: {test_accuracy:.4f}")

# 新增：预测用户上传的图片
def preprocess_user_image(image_path):
    # 加载图片
    img = Image.open(image_path).convert('L')  # 转换为灰度图
    # 调整到 28x28（EMNIST 数据集的尺寸）
    img = img.resize((28, 28))
    # 转换为 numpy 数组
    img_np = np.array(img)
    # 翻转和旋转以匹配 EMNIST 数据集的预处理
    img_np = np.fliplr(img_np)
    img_np = np.rot90(img_np, 1)
    # 归一化
    img_np = img_np.astype(np.float32) / 255.0
    # 展平为784维向量
    img_np = img_np.reshape(1, -1)  # (1, 784)
    return img_np

def predict_image(model, image_path):
    # 预处理图片
    processed_img = preprocess_user_image(image_path)
    # 进行预测
    prediction = model.predict(processed_img)
    # 获取预测的类别
    predicted_class = np.argmax(prediction, axis=1)[0]
    # 将类别转换为字母 (0-25 对应 A-Z)
    predicted_letter = chr(predicted_class + 65)  # 0 -> A, 1 -> B, ..., 25 -> Z
    print(f"Predicted letter: {predicted_letter}")
    # 显示图片
    img = Image.open(image_path).convert('L').resize((28, 28))
    img.show()

# 让用户选择图片
def select_and_predict():
    root = tk.Tk()
    root.withdraw()  # 隐藏主窗口
    file_path = filedialog.askopenfilename(
        title="Select an image",
        filetypes=[("Image files", "*.png *.jpg *.jpeg *.bmp")]
    )
    if file_path:
        print(f"Selected image: {file_path}")
        predict_image(model, file_path)
    else:
        print("No image selected.")
    root.destroy()

# 运行选择和预测
select_and_predict()