<?php
$UID=$_GET["UID"];
$Balance=$_GET["Balance"];

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

if ($Balance == "undefined") {
    $Balance = 0;
}

$sql = "SELECT Balance FROM User WHERE (UID = '$UID')";//响应请求
$result = mysqli_query($conn, $sql);
if (mysqli_num_rows($result) > 0) {
    $row = mysqli_fetch_assoc($result);
    $Balance = (float)$Balance + (float)$row["Balance"];

    $sql = "UPDATE User SET Balance = '$Balance' WHERE (UID = '$UID')";//响应请求
    $result = mysqli_query($conn, $sql);
}
?>