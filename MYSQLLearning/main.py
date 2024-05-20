# import MySQLdb
import pymysql

db = pymysql.connect(host="localhost", user="root", passwd="520520SQL")


# 查看所有数据库名字

def print_tuple(tuple):
    print("数据库有：", end="")
    for i in tuple:
        if i == tuple[-1]:
            print(i[0])
        else:
            print(i[0], end=", ")


def make_user():
    username = input('请输入用户名：')
    password = input('请输入密码：')
    _cursor = db.cursor()
    _cursor.execute("USE autoemail")
    if if_user_exist(username):
        print('用户已存在')
        return
    _cursor.execute("INSERT INTO user (user, pwd) VALUES ('" + username + "', '" + password + "')")
    _cursor.execute("SELECT * FROM user")
    print(_cursor.fetchall())
    print('确定提交吗？', end='(y/n)')

    temp = input()
    if temp == 'y':
        db.commit()
    else:
        db.rollback()


def if_user_exist(lookup):
    _cursor = db.cursor()
    _cursor.execute("USE autoemail")
    _cursor.execute("SELECT user FROM user WHERE user = '" + lookup + "'")
    try:
        person = _cursor.fetchall()[0]
        if person[0] == lookup:
            return True
        else:
            return False
    except IndexError:
        return False


def delete_user():
    username = input('请输入用户名：')
    _cursor = db.cursor()
    _cursor.execute("USE autoemail")
    if not if_user_exist(username):
        print('用户不存在')
        return


def show_databases():
    _cursor = db.cursor()
    _cursor.execute("SHOW DATABASES")
    print("数据库有：", end="")
    _data = _cursor.fetchall()
    print(_data)
    print('尝试选择第一个数据库', _data[0][0])
    _cursor.execute("USE " + _data[0][0])
    _cursor.execute("SHOW TABLES")
    print(_cursor.fetchall())
    # 选择数据库
    # databases = list(data)
    # print(databases)
    # cursor.execute("USE")


# show_databases()
make_user()
# if_user_exist('test')
db.close()


def person_generator(count):
    person = []
    for i in range(1, count + 1):
        person.append(i)
    return person


def killing(person):
    print(person)
    kill_num = 3
    counter = 0
    index = 0
    while len(person) > 1:
        counter += 1
        if counter == kill_num:
            counter = 0
            print(person.pop(index), 'is killed')
        else:
            index += 1
        if index == len(person):
            index = 0
    print(person[0], "is the last one")

# killing(person_generator(6))
