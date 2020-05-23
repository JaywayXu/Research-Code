import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.HColumnDescriptor;
import org.apache.hadoop.hbase.HTableDescriptor;
import org.apache.hadoop.hbase.TableName;
import org.apache.hadoop.hbase.client.Admin;
import org.apache.hadoop.hbase.client.Connection;
import org.apache.hadoop.hbase.client.ConnectionFactory;

import java.io.IOException;

public class CreateTable {
    public static Configuration configuration;
    public static Connection connection;
    public static Admin admin;

    public static void createTable(String tableName, String[] fields) throws IOException {
        init();
        TableName tablename = TableName.valueOf(tableName);
        if (admin.tableExists(tablename)) {
            System.out.println("table is exists!");
            admin.disableTable(tablename);
            admin.deleteTable(tablename);
        }
        HTableDescriptor hTableDescriptor = new HTableDescriptor(tablename);
        for (String str : fields) {
            HColumnDescriptor hColumnDescriptor = new HColumnDescriptor(str);
            hTableDescriptor.addFamily(hColumnDescriptor);
        }
        admin.createTable(hTableDescriptor);
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
        String[] fields = {"Score"};
        try {
            createTable("person", fields);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
