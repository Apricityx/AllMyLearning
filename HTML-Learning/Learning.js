let person = [
    {
        name:'Tom',
        age:18,
        money:1000
    },
    {
        name:'Alex',
        age:18,
        money:1000
    },
    {
        name:'Jack',
        age:18,
        money:1000
    }
]

let display_card = {type:4060,test: 111,name:"display_card", description:"显示卡", price:2000.0, nick : function (){ //此时的nick是一个函数
        return this.description + "型号为" + this.type;
    }};
//display_card是一个对象,对象中有很多属性,其中有一个属性是nick,这个属性是一个函数,函数的返回值是description + "型号为" + type
console.log(display_card.type); //访问对象中的属性
console.log(display_card.nick()) //访问对象中的函数
const {test} = display_card; //这一行是解包,将display_card中的test属性解包到test中
console.log(test);

//对象数组

console.log(person[1].name)
//访问对象数组
//将对象数组转换为json字符串
let json = JSON.stringify(person)
console.log(json)
//将json字符串转换为对象数组
let obj = JSON.parse(json)
console.log(obj)

//以下是通过遍历输出对象数组的一个例子
function output_person() {
    let person = [
        {
            name:'Tom',
            age:18,
            money:1000
        },
        {
            name:'Alex',
            age:18,
            money:1000
        },
        {
            name:'Jack',
            age:18,
            money:1000
        }
    ]
    text = '<ul>';
    for (let i = 0; i < person.length; i++) {
        text += '<li>' + person[i].name + ' ' + person[i].age + ' ' + person[i].money + '<br>' + '</li>';
    }
    text += '</ul>';
    document.getElementById('div').innerHTML = text;
    console.log(text);
}

//正则表达式 语法：/正则表达式主体/修饰符(可选)
//正则表达式的返回值是一个数或者字符串，取决于主体里面是什么，如果什么都没找到就返回-1

var str = "Visit W3School, W3School is a place to study web technology.";
var n = str.search(/W/i);
console.log(n); //输出6，意思是在第6个字符处找到了W

var n = str.replace(/W3School/ig, "Microsoft"); //将W3School替换为Microsoft 其中，g表示全部匹配

console.log(n);


//test方法返回布尔值
if (/W3Schoolwdnmd/i.test(str)){
    console.log("找到了");
}
else {
    console.log("找不到了");
}

//try catch语句
raw1 = '1 2 3 4 5'
list1 = raw1.split(' ')
try{
    for (i = 0;i < 5;i++)
    {
        console.log(list2.pop()) //抛出一个不存在的元素
    }
}
catch (err){
    console.log('出错了')
}

//调用API
api_url = 'https://api.jun.la/60s.php?format=imgapi'
fetch(api_url)
    .then(response => response.json()) // 解析 JSON 数据
    .then(data => {
        var img_id = data.id;
        var img_src = 'caotu.simsv.com/service/image?id=' + img_id;
        console.log(img_id)
        console.log(img_src)
        // session.send(data.imageTime) //输出时间
    }) // 处理数据
    .catch(error => session.send(error)); // 处理错误

// 引入fs和https模块
const fs = require('fs');
const https = require('https');

// 定义文件的URL和保存路径
const fileUrl = 'https://caotu.simsv.com/service/image?id=506af';
const filePath = './image.jpg';

// 创建一个可写流，指定文件的保存路径
const file = fs.createWriteStream(filePath);

// 发送一个GET请求，获取文件的数据
https.get(fileUrl, (response) => {
    // 将响应对象传递给可写流，实现文件的下载和保存
    response.pipe(file);
    // 监听finish事件，表示文件下载完成
    file.on('finish', () => {
        // 关闭可写流，释放资源
        file.close();
        // 打印提示信息
        console.log('File downloaded successfully.');
    });
}).on('error', (error) => {
    // 处理请求或者写入过程中的错误
    console.error(error.message);
});
