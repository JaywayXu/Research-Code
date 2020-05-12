import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.io.IOUtils;

public class FsUrl {
	static {
		URL.setURLStreamHandlerFactory(new FsUrlStreamHandlerFactory());
	}

	public static void cat(String remoteFilePath) throws IOException {
		InputStream in = null;
		try {
			in = new URL("hdfs", "Master", 9000, remoteFilePath)
					.openStream();
			IOUtils.copyBytes(in, System.out, 4096, false);
		} finally {
			IOUtils.closeStream(in);
		}
	}

	/**
	 * 主函数
	 */
	public static void main(String[] args) {
		String remoteFilePath = "/user/hadoop/a.txt"; // HDFS路径

		try {
			System.out.println("读取文件: " + remoteFilePath);
			FsUrl.cat(remoteFilePath);
			System.out.println("\n读取完成");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}