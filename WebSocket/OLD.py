# server.py
import socket
import threading

print("Server started.")


def client_thread(conn, addr):
    try:
        while 1:
            passwd = conn.recv(1024).decode('utf-8')
            print()
            if passwd != '123456':
                conn.send(-1)
            else:
                conn.send(1)
                break
        clients.append(conn)
        name = conn.recv(1024).decode('utf-8')
        print(f"{addr} joined as {name}")
        broadcast(f"{name} joined the chat.", conn, name)
    except:
        print(f"{addr} disconnected.")
        return
    while True:
        # recv会阻塞程序的执行，直到有数据接收到
        try:
            message = conn.recv(1024).decode('utf-8')  # 1024是指定的缓冲区大小，单位为字节
            if message:
                print(f"{name} says: {message}")
                broadcast(message, conn, name)
            else:  # 如果客户端断开连接，recv会返回一个空字符串
                remove(conn)
                break
        except:
            print(f"{name} disconnected.")
            remove(conn)
            break


def broadcast(message, connection, sender):
    for client in clients:
        if client != connection:  # 排除自身
            try:
                client.send(sender + ':' + message.encode('utf-8'))
            except:
                remove(client)  # 如果发送失败，说明客户端已经断开连接，移除该客户端


def remove(connection):
    if connection in clients:
        clients.remove(connection)


server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # 创建一个socket对象，AF_INET是指定使用IPv4协议，SOCK_STREAM是指定使用TCP协议
server.bind(('localhost', 12345))
server.listen()

clients = []

while True:
    conn, addr = server.accept()  # 接受客户端的连接请求，返回一个新的socket对象和客户端的地址，这行代码会阻塞程序的执行，直到有客户端连接上来
    print(f"{addr} connected.")
    threading.Thread(target=client_thread, args=(conn, addr)).start()  # 创建一个新的线程来处理客户端的请求
