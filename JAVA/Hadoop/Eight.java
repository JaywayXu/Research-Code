import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.*;
import java.io.*;

public class Eight {
	/**
	 * 判断路径是否存在
	 */
	public static boolean test(Configuration conf, String path)
			throws IOException {
		FileSystem fs = FileSystem.get(conf);
		return fs.exists(new Path(path));
	}

	/**
	 * 追加文本内容
	 */
	public static void appendContentToFile(Configuration conf, String content,
			String remoteFilePath) throws IOException {
		FileSystem fs = FileSystem.get(conf);
		Path remotePath = new Path(remoteFilePath);
		/* 创建一个文件输出流，输出的内容将追加到文件末尾 */
		FSDataOutputStream out = fs.append(remotePath);
		out.write(content.getBytes());
		out.close();
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
	 * 移动文件到本地 移动后，删除源文件
	 */
	public static void moveToLocalFile(Configuration conf,
			String remoteFilePath, String localFilePath) throws IOException {
		FileSystem fs = FileSystem.get(conf);
		Path remotePath = new Path(remoteFilePath);
		Path localPath = new Path(localFilePath);
		fs.moveToLocalFile(remotePath, localPath);
	}

	/**
	 * 创建文件
	 */
	public static void touchz(Configuration conf, String remoteFilePath)
			throws IOException {
		FileSystem fs = FileSystem.get(conf);
		Path remotePath = new Path(remoteFilePath);
		FSDataOutputStream outputStream = fs.create(remotePath);
		outputStream.close();
		fs.close();
	}

	/**
	 * 主函数
	 */
	public static void main(String[] args) {
		Configuration conf = new Configuration();
		conf.set("fs.default.name", "hdfs://Master:9000");
		String remoteFilePath = "/user/hadoop/a.txt"; // HDFS文件
		String content = "新追加的内容\n";
		String choice = "after"; // 追加到文件末尾
		// String choice = "before"; // 追加到文件开头

		try {
			/* 判断文件是否存在 */
			if (!Eight.test(conf, remoteFilePath)) {
				System.out.println("文件不存在: " + remoteFilePath);
			} else {
				if (choice.equals("after")) { // 追加在文件末尾
					Eight.appendContentToFile(conf, content, remoteFilePath);
					System.out.println("已追加内容到文件末尾" + remoteFilePath);
				} else if (choice.equals("before")) { // 追加到文件开头
					/* 没有相应的api可以直接操作，因此先把文件移动到本地，创建一个新的HDFS，再按顺序追加内容 */
					String localTmpPath = "/user/hadoop/tmp.txt";
					Eight.moveToLocalFile(conf, remoteFilePath, localTmpPath); // 移动到本地
					Eight.touchz(conf, remoteFilePath); // 创建一个新文件
					Eight.appendContentToFile(conf, content, remoteFilePath); // 先写入新内容
					Eight.appendToFile(conf, localTmpPath, remoteFilePath); // 再写入原来内容
					System.out.println("已追加内容到文件开头: " + remoteFilePath);
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}