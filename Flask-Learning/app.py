# 文件名必须为app.py，这是系统环境变量规定好的
from markupsafe import escape
from flask import Flask, url_for, render_template, request, redirect
import time

app = Flask(__name__)


# 创建app对象

@app.route('/hello/<name>')  # 当访问127.0.0.1:5000/hello时，会执行hello函数
# @app.route后面跟def hello()函数
def hello(name):  # name是可以获取的
    print("Hello world")
    print(name)
    return 'Hello world'  # return的内容会显示在网页上


# 这里就相当于已经把hello函数注入到了app.route里面，app这个函数是库提供的，会自动执行hello函数
@app.route('/user/')
def user():
    return 'Hello world'


# 定义初始数据
name = 'Grey Li'
movies = [
    {'title': 'My Neighbor Totoro', 'year': '1988'},
    {'title': 'Dead Poets Society', 'year': '1989'},
    {'title': 'A Perfect World', 'year': '1993'},
    {'title': 'Leon', 'year': '1994'},
    {'title': 'Mahjong', 'year': '1996'},
    {'title': 'Swallowtail Butterfly', 'year': '1996'},
    {'title': 'King of Comedy', 'year': '1999'},
    {'title': 'Devils on the Doorstep', 'year': '1999'},
    {'title': 'WALL-E', 'year': '2008'},
    {'title': 'The Pork of Music', 'year': '2012'},
]
# 输出当前时间
time = time.asctime()


@app.route('/')
def index_url():
    return render_template('index.html', name=name, movies=movies, time=time)


@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':  # 判断是否是 POST 请求
        # 获取表单数据
        get_name = request.form.get('name')  # 传入表单对应输入字段的 name 值
        get_time_year = request.form.get('time_year')
        get_time_year = request.values.get('time_year')
        get_time_month = request.form.get('time_month')
        get_time_day = request.form.get('time_day')
        get_time = [get_time_year, get_time_month, get_time_day]
        print(get_time)
        f = open(str(get_time[1]) + '.json', 'w')
        for i in range(100):
            f.write(str(i) + '\n')
            print('生成')
        f.close()
        # 生成log.txt文件
        print(get_name)
        return redirect(url_for('index'))  # 重定向回主页

    return render_template('index.html', movies=movies)
