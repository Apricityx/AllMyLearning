<!doctype html>
<html lang="zh_CN">
<head>
    <title>PHP LEARNING</title>
</head>
<body>
<p id="PC_ID"></p>
<p id="PC_IP"></p>
<?php
$address = '127.0.0.1';
$port = '8083';
$test_data = <<<EOF
hello
My friend
EOF;
echo $test_data;
echo "<br>";
//PHP数组
$test_array = array("one", "two", "three");
echo $test_array[0];
//PHP资源类型
//资源类型一共有三种，分别是：数据库连接，文件句柄，图形画布
//资源类型是一种特殊的变量，保存了到外部资源的一个引用
$myfile = fopen("APIKEY", "r") or die("Unable to open file!");
echo fread($myfile, filesize("APIKEY"));
echo "<br>";
//获取资源类型的类型
echo "资源类型：" . get_resource_type($myfile) . "<br>";
//stream类型是文件句柄的类型
fclose($myfile);
//PHP常量
//常量是一个简单值的标识符，在脚本中无法改变
//使用define() 函数进行定义
const GREETING = "HELLO WORLD!";
//strpos函数用于寻找一串特定的字符串，并返回其首次出现的位置（索引）
echo strpos(GREETING, "WORLD");
echo "<br>";
echo GREETING[strpos(GREETING, "WORLD")];
echo "<br>";
//PHP中的整数除法
//PHP中的整数除法是向下取整的
echo 5 / 2;
echo "<br>";
echo intdiv(10, 3); //使用intdiv函数进行整数除法
echo "<br>";
echo 1 ? 1 : 2; //三元运算符，此处必定返回1
echo "<br>";
//PHP中的数组，PHP和python不同的一点是，python中的列表和字典是两种不同的数据结构，而PHP中的数组是两者的结合
//PHP中的合并运算符
$_GET['user'] = '111';
$username = $_GET['user'] ?? 'nobody';
echo $username;
echo "<br>";
//PHP中的数组
?>

</body>
</html>
