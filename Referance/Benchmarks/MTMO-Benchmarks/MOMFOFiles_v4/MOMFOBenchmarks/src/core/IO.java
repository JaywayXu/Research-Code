package core;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class IO {

	// read the rotation matrix from the file
	public static double[][] readRotationMatrix(String path) throws IOException {
		FileReader fr = new FileReader(path);
		BufferedReader br = new BufferedReader(fr);

		String line = br.readLine();
		List<String> data = new ArrayList<String>();

		while (line != null) {
			data.add(line);
			line = br.readLine();
		}
		double[][] matrix = new double[data.size()][];
		for (int i = 0; i < matrix.length; i++) {
			String[] st = data.get(i).trim().split("\\s+");
			matrix[i] = new double[st.length];
			for (int j = 0; j < matrix[i].length; j++)
				matrix[i][j] = Double.parseDouble(st[j]);

		}
		br.close();
		return matrix;
	}

	// read the shift vector from the file
	public static double[] readShiftVector(String path) throws IOException {
		FileReader fr = new FileReader(path);
		BufferedReader br = new BufferedReader(fr);
		String line = br.readLine();
		String[] st = line.trim().split("\\s+");

		double[] shift = new double[st.length];

		for (int i = 0; i < shift.length; i++)
			shift[i] = Double.parseDouble(st[i]);

		br.close();
		return shift;
	}

}
