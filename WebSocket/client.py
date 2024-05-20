# client.py
import json
import socket
import threading
from time import sleep

url = 'localhost'
port = 12345
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.connect((url, port)) # connect方法用于连接到服务器


def re_login(name, passwd):
    global server
    server.send(passwd.encode('utf-8'))
    server.recv(1024).decode('utf-8')
    server.send(name.encode('utf-8'))
    print('Reconnect successful')


while 1:
    passwd = input('PASSWD:')
    server.send(passwd.encode('utf-8'))
    respond = server.recv(1024).decode('utf-8')
    print("respond:", respond)
    if respond == '-1':
        print("Wrong Passwd.")
    else:
        break

name = input('Your Name:')
server.send(name.encode('utf-8'))
print(f"Welcome, {name}! ")


def receive_message():
    global server
    while 1:
        try:
            raw_message = server.recv(1024).decode('utf-8')
            message = json.loads(raw_message)
            sender = message['sender']
            text = message['text']
            print(sender + ':' + text)
        except ConnectionError as e:  # 连接意外终止，尝试重连
            print(e)
            server.close()
            while 1:
                try:
                    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                    server.connect((url, port))
                    re_login(name, passwd)
                    break
                except Exception as e:
                    print(e)
                    print('Reconnecting...')
                    sleep(1)
                    continue


# {
#     "sender": "name",
#     "text": "message"
# }

threading.Thread(target=receive_message, args=()).start()
while True:  # 开始接受消息，进行聊天
    message = input()
    if message == '':
        message = message + ' '
    # 将消息转换为JSON格式的字符串
    json_message = json.dumps({
        "sender": name,
        "text": message
    })
    server.send(json_message.encode('utf-8'))
