<?php
$UID=$_GET["UID"];

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

$sql = "SELECT CID,Intime,Outtime,Cost FROM Record WHERE UID='$UID'";//响应请求
$result = mysqli_query($conn, $sql);

if (mysqli_num_rows($result) > 0) {// 输出小程序数组
    $s = "";
    while($row = mysqli_fetch_assoc($result)) {
        $s = $s . json_encode($row);//将请求结果转换为json格式
    }
    $s = '[' . join('},', array_slice(preg_split('/}\s*/i', $s), 0, -1)) . '}]';
    echo $s;
}
?>