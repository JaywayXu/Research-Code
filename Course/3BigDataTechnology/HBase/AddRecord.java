import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.TableName;
import org.apache.hadoop.hbase.client.*;

import java.io.IOException;

public class AddRecord {
    public static Configuration configuration;
    public static Connection connection;
    public static Admin admin;

    public static void addRecord(String tableName, String row, String[] fields, String[] values) throws IOException {
        init();
        Table table = connection.getTable(TableName.valueOf(tableName));
        for (int i = 0; i != fields.length; i++) {
            Put put = new Put(row.getBytes());
            String[] cols = fields[i].split(":");
            put.addColumn(cols[0].getBytes(), cols[1].getBytes(), values[i].getBytes());
            table.put(put);
        }
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
        String[] fields = {"Score:Math", "Score:Computer Science", "Score:English"};
        String[] values = {"99", "80", "100"};
        try {
            addRecord("person", "Score", fields, values);
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
