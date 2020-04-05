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

// 查询用户名是否在库中
$sql = "SELECT UID FROM User WHERE UID='$UID'";//响应请求
$result = mysqli_query($conn, $sql);

if (mysqli_num_rows($result) > 0) {// 在库中
    echo '{"result": false}';//返回
} else {
    $sql = "INSERT INTO User (UID, Upswd) VALUES ('$UID', '$Upswd')";//响应请求
    $result = mysqli_query($conn, $sql);
    
    if ($result) {// 成功
        echo '{"result": true}';//将请求结果转换为json格式
    } else {// 失败
        echo '{"result": false}';//将请求结果转换为json格式
    }
}
?>