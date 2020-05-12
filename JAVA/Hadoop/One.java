import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.*;
import java.io.*;

public class One {
	/**
	 * 判断路径是否存在
	 */
	public static boolean test(Configuration conf, String path)
			throws IOException {
		FileSystem fs = FileSystem.get(conf);
		return fs.exists(new Path(path));
	}

	/**
	 * 复制文件到指定路径 若路径已存在，则进行覆盖
	 */
	public static void copyFromLocalFile(Configuration conf,
			String localFilePath, String remoteFilePath) throws IOException {
		FileSystem fs = FileSystem.get(conf);
		Path localPath = new Path(localFilePath);
		Path remotePath = new Path(remoteFilePath);
		/* fs.copyFromLocalFile 第一个参数表示是否删除源文件，第二个参数表示是否覆盖 */
		fs.copyFromLocalFile(false, true, localPath, remotePath);
		fs.close();
	}

	/**
	 * 追加文件内容
	 */
	public static void appendToFile(Configuration conf, String localFilePath,
			String remoteFilePath) throws IOException {
		FileSystem fs = FileSystem.get(conf);
		Path remotePath = new Path(remoteFilePath);
		/* 创建一个文件读入流 */
		FileInputStream in = new FileInputStream(localFilePath);
		/* 创建一个文件输出流，输出的内容将追加到文件末尾 */
		FSDataOutputStream out = fs.append(remotePath);
		/* 读写文件内容 */
		byte[] data = new byte[1024];
		int read = -1;
		while ((read = in.read(data)) > 0) {
			out.write(data, 0, read);
		}
		out.close();
		in.close();
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
		String choice = "append"; // 若文件存在则追加到文件末尾
		// String choice = "overwrite"; // 若文件存在则覆盖

		try {
			/* 判断文件是否存在 */
			boolean fileExists = false;
			if (One.test(conf, remoteFilePath)) {
				fileExists = true;
				System.out.println(remoteFilePath + " 已存在.");
			} else {
				System.out.println(remoteFilePath + " 不存在.");
			}
			/* 进行处理 */
			if (!fileExists) { // 文件不存在，则上传
				One.copyFromLocalFile(conf, localFilePath, remoteFilePath);
				System.out.println(localFilePath + " 已上传至 " + remoteFilePath);
			} else if (choice.equals("overwrite")) { // 选择覆盖
				One.copyFromLocalFile(conf, localFilePath, remoteFilePath);
				System.out.println(localFilePath + " 已覆盖 " + remoteFilePath);
			} else if (choice.equals("append")) { // 选择追加
				One.appendToFile(conf, localFilePath, remoteFilePath);
				System.out.println(localFilePath + " 已追加至 " + remoteFilePath);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}