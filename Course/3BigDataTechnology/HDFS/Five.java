import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.*;
import java.io.*;
import java.text.SimpleDateFormat;

public class Five {
	/**
	 * 显示指定文件夹下所有文件的信息（递归）
	 */
	public static void lsDir(Configuration conf, String remoteDir)
			throws IOException {
		FileSystem fs = FileSystem.get(conf);
		Path dirPath = new Path(remoteDir);
		/* 递归获取目录下的所有文件 */
		RemoteIterator<LocatedFileStatus> remoteIterator = fs.listFiles(
				dirPath, true);
		/* 输出每个文件的信息 */
		while (remoteIterator.hasNext()) {
			FileStatus s = remoteIterator.next();
			System.out.println("路径: " + s.getPath().toString());
			System.out.println("权限: " + s.getPermission().toString());
			System.out.println("大小: " + s.getLen());
			/* 返回的是时间戳,转化为时间日期格式 */
			Long timeStamp = s.getModificationTime();
			SimpleDateFormat format = new SimpleDateFormat(
					"yyyy-MM-dd HH:mm:ss");
			String date = format.format(timeStamp);
			System.out.println("时间: " + date);
			System.out.println();
		}
		fs.close();
	}

	/**
	 * 主函数
	 */
	public static void main(String[] args) {
		Configuration conf = new Configuration();
		conf.set("fs.default.name", "hdfs://Master:9000");
		String remoteDir = "/user/hadoop/"; // HDFS路径

		try {
			System.out.println("(递归)读取目录下所有文件的信息: " + remoteDir);
			Five.lsDir(conf, remoteDir);
			System.out.println("读取完成");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}