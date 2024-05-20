from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP
import base64
import pymysql

f = open("passwd", "r")
lines = f.readlines()
passwd = lines[0]
f.close()

db = pymysql.connect(host="localhost", user="root", password=passwd)
cursor = db.cursor()
cursor.execute("use autoemail")

user = input("Enter Username: ")
passwd = input("Enter Password: ")


# 使用ras加密密码
def load_public_key(filename):
    with open(filename, 'r') as file:
        public_key = RSA.import_key(file.read())
    return public_key


def encrypt_message(message, public_key):
    # 创建cipher对象，cipher对象可以加密和解密
    cipher = PKCS1_OAEP.new(public_key)
    # Encrypt the message
    encrypted_message = cipher.encrypt(message.encode())
    # Encode the encrypted message with base64
    encoded_encrypted_message = base64.b64encode(encrypted_message)
    return encoded_encrypted_message


public_key = load_public_key('Keys/public.pem')
message = encrypt_message(passwd, public_key)
print(f"Encrypted message: {message.decode()}")