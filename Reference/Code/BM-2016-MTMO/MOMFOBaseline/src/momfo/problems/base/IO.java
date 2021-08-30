package momfo.problems.base;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.List;

import momfo.util.PseudoRandom;

public class IO {
	
	public static void main(String args[]) throws IOException {
		DecimalFormat df = new DecimalFormat("0.00");
		double[][] matrix = IO.readMatrixFromFile("COM_2.txt");
		for (int i = 0; i < matrix.length; i++) {
			for (int j = 0; j < matrix[i].length; j++) {
				double value = matrix[i][j];
				matrix[i][j] = Double.parseDouble(df.format(value));
			}
		}
		IO.printMatrixToFile(matrix, "COM_2_new.txt");
	}
/*	public static double[][] getRandomRotationMatrix(int m, int n, double low, double up) {
		double matrix[][] = new double[m][n];
		
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				matrix[i][j] = PseudoRandom.randDouble(low, up);
			}
		}
		return matrix;
	}*/
	public static double[][] getRandomRotationMatrix(int m, int n, double low, double up) {
		double matrix[][] = new double[m][n];
		DecimalFormat df = new DecimalFormat("0.00");
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				double value = PseudoRandom.randDouble(low, up);
				matrix[i][j] = Double.parseDouble(df.format(value));
			}
		}
		return matrix;
	}
	
	
	public static double[] getShiftValues(int m, int n, double shift) {
		double[] shiftvalues = new double[m];
		for (int i = 0; i < m; i++) {
			if (i >= n)
				shiftvalues[i] = shift;
			else
				shiftvalues[i] = 0;
		}
		
		return shiftvalues;
	}
	
	public static void printMatrixToFile(double[][] matrix, String path) throws FileNotFoundException {
		File file = new File(path);
		PrintWriter out = new PrintWriter(new OutputStreamWriter(
				new FileOutputStream(file, false)));
		
		for (int i = 0; i < matrix.length; i++) {
			for (int j = 0; j < matrix[i].length; j++)
				out.print(matrix[i][j] + " ");
			out.println();
		}
		out.close();
	}
	
	
	public static double[][] readMatrixFromFile(String path) throws IOException {
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
	
	
	public static void printShiftValuesToFile(double[] shiftvalues,String path) throws FileNotFoundException {
		File file = new File(path);
		PrintWriter out = new PrintWriter(new OutputStreamWriter(
				new FileOutputStream(file, false)));
		
		for (int i = 0; i < shiftvalues.length; i++)
			out.print(shiftvalues[i] + " ");
		out.println();
		out.close();
	}
	
	public static double[] readShiftValuesFromFile(String path) throws IOException {
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
