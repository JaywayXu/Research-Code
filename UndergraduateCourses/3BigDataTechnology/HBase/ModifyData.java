import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.Cell;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.TableName;
import org.apache.hadoop.hbase.client.*;

import java.io.IOException;

public class ModifyData {

    public static long ts;
    public static Configuration configuration;
    public static Connection connection;
    public static Admin admin;

    public static void modifyData(String tableName, String row, String column, String val) throws IOException {
        init();
        Table table = connection.getTable(TableName.valueOf(tableName));
        Put put = new Put(row.getBytes());
        Scan scan = new Scan();
        ResultScanner resultScanner = table.getScanner(scan);
        for (Result r : resultScanner) {
            for (Cell cell : r.getColumnCells(row.getBytes(), column.getBytes())) {
                ts = cell.getTimestamp();
            }
        }
        put.addColumn(row.getBytes(), column.getBytes(), ts, val.getBytes());
        table.put(put);
        table.close();
        close();
    }

    public static void init() {
        configuration = HBaseConfiguration.create();
        configuration.set("hbase.rootdir", "hdfs://Master:9000/hbase");
        try {
            connection = ConnectionFactory.createConnection(configuration);
            admin = connection.getAdmin();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void close() {
        try {
            if (admin != null) {
                admin.close();
            }
            if (null != connection) {
                connection.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        try {
            modifyData("person", "Score", "Math", "100");
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
