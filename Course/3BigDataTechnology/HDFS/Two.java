import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.*;
import java.io.*;

public class Two {
	/**
	 * 下载文件到本地 判断本地路径是否已存在，若已存在，则自动进行重命名
	 */
	public static void copyToLocal(Configuration conf, String remoteFilePath,
			String localFilePath) throws IOException {
		FileSystem fs = FileSystem.get(conf);
		Path remotePath = new Path(remoteFilePath);
		File f = new File(localFilePath);
		/* 如果文件名存在，自动重命名(在文件名后面加上 _0, _1 ...) */
		if (f.exists()) {
			System.out.println(localFilePath + " 已存在.");
			Integer i = 0;
			while (true) {
				f = new File(localFilePath + "_" + i.toString());
				if (!f.exists()) {
					localFilePath = localFilePath + "_" + i.toString();
					break;
				}
			}
			System.out.println("将重新命名为: " + localFilePath);
		}
		// 下载文件到本地
		Path localPath = new Path(localFilePath);
		fs.copyToLocalFile(remotePath, localPath);
		fs.close();
	}

	/**
	 * 主函数
	 */
	public static void main(String[] args) {
		Configuration conf = new Configuration();
		conf.set("fs.default.name", "hdfs://Master:9000");
		String localFilePath = "/home/hadoop/a.txt"; // 本地路径
		String remoteFilePath = "/user/hadoop/a.txt"; // HDFS路径

		try {
			Two.copyToLocal(conf, remoteFilePath, localFilePath);
			System.out.println("下载完成");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}