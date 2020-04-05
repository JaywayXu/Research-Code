<?php
$UID=$_GET["UID"];
$Uname=$_GET["Uname"];
$Uphone=$_GET["Uphone"];

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

if ($Uname == "undefined") {
    $Uname = "";
}
if ($Uphone == "undefined") {
    $Uphone = "";
}

$sql = "UPDATE User SET Uname = '$Uname', Uphone = '$Uphone' WHERE (UID = '$UID')";//响应请求
$result = mysqli_query($conn, $sql);
?>