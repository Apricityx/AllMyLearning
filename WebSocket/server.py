import socket
import asyncio
import threading
import json

print("Server started.")

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # 创建一个socket对象，AF_INET是指定使用IPv4协议，SOCK_STREAM是指定使用TCP协议
server.bind(('localhost', 12345))
server.listen()

clients = []


def new_client(client, address):
    global clients
    print(f"{address} trying to login")
    while 1:
        passwd = client.recv(1024).decode('utf-8')
        if passwd == '12345':
            print('SUCCESS')
            client.send('1'.encode('utf-8'))
            break
        else:
            print('FAILED')
            client.send('-1'.encode('utf-8'))
    name = client.recv(1024).decode('utf-8')
    print(f"{address} joined as {name}")
    clients.append(client)
    # 客户端认证并加入聊天室
    welcome = json.dumps({
        "sender": "Server",
        "text": f"Welcome, {name}!"
    })
    broadcast(welcome, client)
    while 1:  # 开始监听消息
        try:
            message = client.recv(1024).decode('utf-8')
            if message:
                broadcast(message, client)
            else:
                remove(client)
                break
        except ConnectionError:
            remove(client)
            return


def broadcast(raw_message, self_client):
    massage = json.loads(raw_message)
    sender = massage['sender']
    message = massage['text']
    print(f"{sender} says: {message}")
    # print('当前在线人数：' + str(len(clients)))
    for client in clients:
        if client != self_client:
            client.send(raw_message.encode('utf-8'))


def remove(connection):
    if connection in clients:
        print(f"{connection} disconnected.")
        clients.remove(connection)


while 1:
    conn, addr = server.accept()
    threading.Thread(target=new_client, args=(conn, addr)).start()
