<?php
header('Content-Type: application/json');
header('Pragma: no-cache');
header('Cache-Control: no-cache, no-store, max-age=0');
header('Expires: 1L');
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: *");
header("Access-Control-Allow-Headers: *");
$rawData = file_get_contents("php://input");
$decodedData = json_decode($rawData, true);
$encrypted = $decodedData['encrypted'];
$privateKeyFile = file('../keys/private.key');
$privateKey = '';
for ($i = 0; $i < count($privateKeyFile); $i++) {
    $privateKey .= $privateKeyFile[$i];
}
$decrypted = "";
openssl_private_decrypt(base64_decode($encrypted), $decrypted, $privateKey);
// 消息解密，先用base64解密，再用私钥解密
// 解密得到的JSON文本：
// {
//     "name":"222023321062106",
//     "password":"062106"
// }
$data = json_decode($decrypted, true);
// 获取用户名密码
$user_name = $data['name'];
$password = $data['password'];
// 连接到数据库
$passwd_file = file('passwd');
$servername = "localhost";
$username = 'root';
$pass = trim($passwd_file[0]);
$dbname = 'autoemail';
$conn = new mysqli($servername, $username, $pass, $dbname);
if ($conn->connect_error) {
    die("连接失败: " . $conn->connect_error);
}
//echo $password;
//$password = 'qwdguiwqguidqw or 1=1';
$sql = "SELECT * FROM students WHERE student_id = $user_name AND passwd = '$password'";
$stmt = $conn->query($sql);
// 输出登录结果
if ($stmt->num_rows > 0) {
    echo json_encode(array('status' => 'success', 'msg' => '登录成功'), 256);
} else {
    echo json_encode(array('status' => 'fail', 'msg' => '登录失败'), 256);
}
