import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.Cell;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.TableName;
import org.apache.hadoop.hbase.client.*;
import org.apache.hadoop.hbase.util.Bytes;

import java.io.IOException;

public class DeleteRow {

    public static long ts;
    public static Configuration configuration;
    public static Connection connection;
    public static Admin admin;

    public static void deleteRow(String tableName, String row) throws IOException {
        init();
        Table table = connection.getTable(TableName.valueOf(tableName));
        Delete delete=new Delete(row.getBytes());
        table.delete(delete);
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
            deleteRow("person", "Score");
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
