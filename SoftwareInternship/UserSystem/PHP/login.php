<?php
$UID=$_GET["UID"];
$Upswd=$_GET["Upswd"];

$servername = "127.0.0.1";
$username = "root";
$password = "0017";
$dbname = "ParkingLot";

// 创建连接
$conn = new mysqli($servername, $username, $password, $dbname);
// 检测连接
if ($conn->connect_error) {
    die("连接失败: " . $conn->connect_error);
}

// 查询用户名和密码是否在库中
$sql = "SELECT UID FROM User WHERE UID='$UID' AND Upswd='$Upswd'";//响应请求
$result = mysqli_query($conn, $sql);

if (mysqli_num_rows($result) > 0) {// 在库中
    echo '{"result": true}';
} else {
    echo '{"result": false}';
}
?>