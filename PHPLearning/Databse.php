<?php
$db = new mysqli('pve.zwtsvx.xyz:1128', 'root', '20050125@Wy', 'mysql');
if ($db->connect_error) {
    die("连接失败: " . $db->connect_error);
}
echo "连接成功";
