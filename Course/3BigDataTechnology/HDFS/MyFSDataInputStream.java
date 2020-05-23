import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.*;

public class MyFSDataInputStream extends FSDataInputStream {

	public MyFSDataInputStream(InputStream in) {
		super(in);
		// TODO Auto-generated constructor stub
	}

	public static String readline(Configuration conf, String remoteFilePath)
			throws IOException {
		FileSystem fs = FileSystem.get(conf);
		Path remotePath = new Path(remoteFilePath);
		FSDataInputStream in = fs.open(remotePath);
		BufferedReader d = new BufferedReader(new InputStreamReader(in));
		String line = null;
		if ((line = d.readLine()) != null) {
			d.close();
			in.close();
			fs.close();
			return line;
		} else {
			d.close();
			in.close();
			fs.close();
			return null;
		}
	}

	public static void main(String[] args) {
		Configuration conf = new Configuration();
		conf.set("fs.default.name", "hdfs://Master:9000");
		String remoteFilePath = "/user/hadoop/a.txt"; // HDFS路径

		try {
			System.out.println("读取文件: " + remoteFilePath);
			System.out.println(MyFSDataInputStream.readline(conf,
					remoteFilePath));
			System.out.println("\n读取完成");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}