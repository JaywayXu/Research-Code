<?php
$UID=$_GET["UID"];
$CID=$_GET["CID"];

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

if ($CID == "undefined") { //如果没有则删除
    $sql = "DELETE FROM UserCar WHERE (UID = '$UID');";//响应请求
    $result = mysqli_query($conn, $sql);
} else {
    $sql = "SELECT UID FROM UserCar WHERE UID='$UID'";//响应请求
    $result = mysqli_query($conn, $sql);

    if (mysqli_num_rows($result) > 0) {// 在库内,改变
        $sql = "UPDATE UserCar SET CID = '$CID' WHERE (UID = '$UID');";//响应请求
        $result = mysqli_query($conn, $sql);
    } else { //不在库内，添加
        $sql = "INSERT INTO UserCar (UID, CID) VALUES ('$UID', '$CID')";//响应请求
        $result = mysqli_query($conn, $sql);
    }
}
?>