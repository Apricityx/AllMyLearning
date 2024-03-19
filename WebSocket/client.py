# client.py
import socket
import threading


def receive_message(sock):
    while True:
        try:
            message = sock.recv(1024).decode('utf-8')
            print(message)
        except:
            print("You have been disconnected from the server.")
            sock.close()
            break


server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.connect(('localhost', 12345))

threading.Thread(target=receive_message, args=(server,)).start()

while True:
    message = input('')
    server.send(message.encode('utf-8'))
