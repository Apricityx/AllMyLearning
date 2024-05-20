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
print("SELECT * FROM students WHERE name=" + user + " AND passwd=" + passwd)

# while ' ' in user or ' ' in passwd:  # 检查是否有空格，有空格就重新输入，防止SQL注入
#     print("Invalid username or password, try again.")
#     user = input("Enter Username: ")
#     passwd = input("Enter Password: ")
if cursor.execute("SELECT * FROM students WHERE name=" + user + " AND passwd=" + passwd):
    print("Login Successful")
else:
    print("Invalid username or password, try again.")
