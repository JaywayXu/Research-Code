<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://apps.bdimg.com/libs/jquerymobile/1.4.5/jquery.mobile-1.4.5.min.css">
    <script src="https://apps.bdimg.com/libs/jquery/1.10.2/jquery.min.js"></script>
    <script src="https://apps.bdimg.com/libs/jquerymobile/1.4.5/jquery.mobile-1.4.5.min.js"></script>
</head>

<body>

    <div data-role="page" id="pageone">
        <div data-role="header">
            <h1>停车场人工管理系统</h1>
        </div>
        <?php
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

        $sql = "SELECT LID, Num FROM Lot";
        $result = $conn->query($sql);

        if ($result->num_rows > 0) {
            // 输出数据
            while($row = $result->fetch_assoc()) {
                echo "LID: " . $row["LID"]. ", Num: " . $row["Num"]. "<br>";
            }
        } else {
            echo "0 结果";
        }
        $conn->close();
        ?>
        <div data-role="main" class="ui-content">
            <div data-role="collapsible" data-collapsed="false">
                <h1>车位剩余</h1>
                <table data-role="table" data-mode="columntoggle" class="ui-responsive ui-shadow" id="myTable">
                    <thead>
                        <tr>
                            <th data-priority="1">下单人</th>
                            <th data-priority="2">地址</th>
                            <th data-priority="3">下单时间</th>
                            <th data-priority="4">取件日期</th>
                            <th data-priority="5">联系电话</th>
                            <th data-priority="6">订单状态</th>
                            <th data-priority="7">处理</th>
                        </tr>
                    </thead>
                    <tbody>
                        <tr>
                            <td>Lyc</td>
                            <td>北区25栋314</td>
                            <td>2019-19-21 09:10:54</td>
                            <td>2019-10-21</td>
                            <td>11112332</td>
                            <td>待接单</td>
                            <td><a href="#" class="ui-btn ui-btn-inline ui-mini">接单</a></td>
                        </tr>
                        <tr>
                            <td>abc</td>
                            <td>北区25栋314</td>
                            <td>2019-19-22 09:10:54</td>
                            <td>2019-10-23</td>
                            <td>11123332</td>
                            <td>待接单</td>
                            <td><a href="#" class="ui-btn ui-btn-inline ui-mini">接单</a></td>
                        </tr>
                    </tbody>
                </table>
            </div>
            <div data-role="collapsible">
                <h1>正在进行</h1>
                <table data-role="table" data-mode="columntoggle" class="ui-responsive ui-shadow" id="myTable">
                    <thead>
                        <tr>
                            <th data-priority="1">下单人</th>
                            <th data-priority="2">地址</th>
                            <th data-priority="3">下单时间</th>
                            <th data-priority="4">取件日期</th>
                            <th data-priority="5">联系电话</th>
                            <th data-priority="6">订单状态</th>
                            <th data-priority="7">处理</th>
                        </tr>
                    </thead>
                    <tbody>
                        <tr>
                            <td>xx</td>
                            <td>西区25栋314</td>
                            <td>2019-19-21 09:10:54</td>
                            <td>2019-10-21</td>
                            <td>11112332</td>
                            <td>正在进行</td>
                            <td><a href="#" class="ui-btn ui-btn-inline ui-mini">完成</a></td>
                        </tr>
                        <tr>
                            <td>abc</td>
                            <td>北区25栋314</td>
                            <td>2019-19-22 09:10:54</td>
                            <td>2019-10-23</td>
                            <td>11123332</td>
                            <td>正在进行</td>
                            <td><a href="#" class="ui-btn ui-btn-inline ui-mini">完成</a></td>
                        </tr>
                    </tbody>
                </table>
            </div>
            <div data-role="collapsible">
                <h1>已完成</h1>
                <table data-role="table" data-mode="columntoggle" class="ui-responsive ui-shadow" id="myTable">
                    <thead>
                        <tr>
                            <th data-priority="1">下单人</th>
                            <th data-priority="2">地址</th>
                            <th data-priority="3">下单时间</th>
                            <th data-priority="4">取件日期</th>
                            <th data-priority="5">联系电话</th>
                            <th data-priority="6">订单状态</th>
                            <th data-priority="7">处理</th>
                        </tr>
                    </thead>
                    <tbody>
                        <tr>
                            <td>Lyc</td>
                            <td>北区25栋314</td>
                            <td>2019-19-21 09:10:54</td>
                            <td>2019-10-21</td>
                            <td>11112332</td>
                            <td>已完成</td>
                            <td><a href="#" class="ui-btn ui-btn-inline ui-mini">删除</a></td>
                        </tr>
                        <tr>
                            <td>abc</td>
                            <td>北区25栋314</td>
                            <td>2019-19-22 09:10:54</td>
                            <td>2019-10-23</td>
                            <td>11123332</td>
                            <td>已完成</td>
                            <td><a href="#" class="ui-btn ui-btn-inline ui-mini">删除</a></td>
                        </tr>
                    </tbody>
                </table>
            </div>
        </div>

    </div>

</body>

</html>