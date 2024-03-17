import pymysql



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
