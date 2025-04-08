"""
This script implements a simple neural network from scratch to recognize handwritten digits from the MNIST dataset.
We use one hidden layer, sigmoid activation, gradient descent, and backpropagation.
"""
import numpy as np
from tensorflow.keras.datasets import mnist
from tensorflow.keras.utils import to_categorical

# Load MNIST data
(x_train, y_train), (x_test, y_test) = mnist.load_data()
# 将图片平铺为一维向量，-1代表自动计算，此处保持60000不变，60000是训练集图片的张数，/255是归一化
x_train = x_train.reshape(-1, 28 * 28) / 255.0  # shape: (60000, 784)
x_test = x_test.reshape(-1, 28 * 28) / 255.0  # shape: (10000, 784)
# to_categorical函数用于将整数标签转换为独热编码格式，例如5变为[0, 0, 0, 0, 1, 0, 0, 0, 0, 0]
y_train = to_categorical(y_train, 10)  # shape: (60000, 10)
y_test = to_categorical(y_test, 10)  # shape: (10000, 10)
# Define network architecture
input_size = 784  # 28x28 pixels 输入层神经元数量
hidden_size = 64  # number of neurons in hidden layer 隐藏层神经元数量
output_size = 10  # number of classes (digits 0-9) 输出层神经元数量
learning_rate = 0.1
epochs = 10  # 训练轮数 过少欠拟合，过多过拟合
batch_size = 64  # 分批训练，每次喂64张图片

# 随机猜测一个权重和偏置作为起点
# W为一个矩阵，W1为输入层到隐藏层的权重矩阵，W2为隐藏层到输出层的权重矩阵
# W和前面x_train矩阵相乘就可以得到一个评分
W1 = np.random.randn(input_size, hidden_size) * 0.01  # weights between input and hidden layer
b1 = np.zeros((1, hidden_size))  # biases for hidden layer
W2 = np.random.randn(hidden_size, output_size) * 0.01  # weights between hidden and output layer
b2 = np.zeros((1, output_size))  # biases for output layer


# Activation functions and derivatives
def sigmoid(z):
    """Sigmoid activation function"""
    return 1 / (1 + np.exp(-z))


def sigmoid_derivative(a):
    """Derivative of sigmoid given activation a"""
    return a * (1 - a)


def softmax(z):
    """Softmax activation for output layer"""
    exp_z = np.exp(z - np.max(z, axis=1, keepdims=True))
    return exp_z / np.sum(exp_z, axis=1, keepdims=True)


# 开始训练
for epoch in range(epochs):
    # Shuffle training data each epoch
    # 生成一个随机的排列，perm是一个随机的索引数组，例如[1,2,3,4]经过np.random.permutation后变成[3,1,4,2]
    perm = np.random.permutation(x_train.shape[0])
    # np的一个特性是可以用一个索引数组来对另一个数组进行重排
    # xy都用perm重排
    x_train_shuffled = x_train[perm]
    y_train_shuffled = y_train[perm]

    for i in range(0, x_train.shape[0], batch_size):  # 以batch_size为步长
        # 分批训练
        X_batch = x_train_shuffled[i:i + batch_size]
        Y_batch = y_train_shuffled[i:i + batch_size]

        # 前向传播
        Z1 = np.dot(X_batch, W1) + b1  # Linear transform to hidden layer
        A1 = sigmoid(Z1)  # Activation at hidden layer
        Z2 = np.dot(A1, W2) + b2  # Linear transform to output layer
        A2 = softmax(Z2)  # Activation at output layer (probabilities)

        # Compute loss (cross-entropy)
        loss = -np.mean(np.sum(Y_batch * np.log(A2 + 1e-8), axis=1))

        # Backward propagation
        dZ2 = A2 - Y_batch  # Gradient of loss w.r.t. Z2
        dW2 = np.dot(A1.T, dZ2) / batch_size  # Gradient w.r.t. W2
        db2 = np.sum(dZ2, axis=0, keepdims=True) / batch_size  # Gradient w.r.t. b2

        dA1 = np.dot(dZ2, W2.T)  # Gradient w.r.t. A1
        dZ1 = dA1 * sigmoid_derivative(A1)  # Gradient w.r.t. Z1
        dW1 = np.dot(X_batch.T, dZ1) / batch_size  # Gradient w.r.t. W1
        db1 = np.sum(dZ1, axis=0, keepdims=True) / batch_size  # Gradient w.r.t. b1

        # Update parameters using gradient descent
        W2 -= learning_rate * dW2
        b2 -= learning_rate * db2
        W1 -= learning_rate * dW1
        b1 -= learning_rate * db1

    # After each epoch, evaluate on training set
    Z1_train = np.dot(x_train, W1) + b1
    A1_train = sigmoid(Z1_train)
    Z2_train = np.dot(A1_train, W2) + b2
    A2_train = softmax(Z2_train)
    train_preds = np.argmax(A2_train, axis=1)
    train_labels = np.argmax(y_train, axis=1)
    train_accuracy = np.mean(train_preds == train_labels)
    print(f"Epoch {epoch + 1}/{epochs} - Loss: {loss:.4f} - Training Accuracy: {train_accuracy:.4f}")

# Evaluate on test set
Z1_test = np.dot(x_test, W1) + b1
A1_test = sigmoid(Z1_test)
Z2_test = np.dot(A1_test, W2) + b2
A2_test = softmax(Z2_test)

test_preds = np.argmax(A2_test, axis=1)
test_labels = np.argmax(y_test, axis=1)
test_accuracy = np.mean(test_preds == test_labels)
print(f"Test Accuracy: {test_accuracy:.4f}")
