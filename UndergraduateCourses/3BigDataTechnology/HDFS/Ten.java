import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.*;
import java.io.*;

public class Ten {
	/**
	 * 判断目录是否为空 true: 空，false: 非空
	 */
	public static boolean isDirEmpty(Configuration conf, String remoteDir)
			throws IOException {
		FileSystem fs = FileSystem.get(conf);
		Path dirPath = new Path(remoteDir);
		RemoteIterator<LocatedFileStatus> remoteIterator = fs.listFiles(
				dirPath, true);
		return !remoteIterator.hasNext();
	}

	/**
	 * 删除目录
	 */
	public static boolean rmDir(Configuration conf, String remoteDir,
			boolean recursive) throws IOException {
		FileSystem fs = FileSystem.get(conf);
		Path dirPath = new Path(remoteDir);
		/* 第二个参数表示是否递归删除所有文件 */
		boolean result = fs.delete(dirPath, recursive);
		fs.close();
		return result;
	}

	/**
	 * 主函数
	 */
	public static void main(String[] args) {
		Configuration conf = new Configuration();
		conf.set("fs.default.name", "hdfs://Master:9000");
		String remoteDir = "/user/hadoop/dir1/dir2"; // HDFS目录
		Boolean forceDelete = false; // 是否强制删除

		try {
			if (!Ten.isDirEmpty(conf, remoteDir) && !forceDelete) {
				System.out.println("目录不为空，不删除");
			} else {
				if (Ten.rmDir(conf, remoteDir, forceDelete)) {
					System.out.println("目录已删除: " + remoteDir);
				} else {
					System.out.println("操作失败");
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}