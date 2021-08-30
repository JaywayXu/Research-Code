package momfo.util.vector;

import java.util.Scanner;

public class TwoLevelWeightVectorGenerator extends VectorGenerator {
	int div1;
	int div2;
	
	int m;
	
	static int gn;
	
	public TwoLevelWeightVectorGenerator(int div1, int div2, int m){
		this.div1 = div1;
		this.div2 = div2;
		this.m = m;
		
		int N1 = 0;
		int N2 = 0;
		if (div1 != 0){
			N1 = getCombin(m + div1 - 1, div1);
		}
		if (div2 != 0){
			N2 = getCombin(m + div2 - 1, div2);
		}
		
		double[][] z1 = null;
		double[][] z2 = null;
		
		if (N1 != 0)
			z1 = new double[N1][m];
		if (N2 != 0)
			z2 = new double[N2][m];
		
//		System.out.println(N1);
//		System.out.println(N2);
		if (N1 != 0)
			generateWeightVector(z1, div1, m);
		if (N2 != 0)
			generateWeightVector(z2, div2, m);
		
		
		double mid = 1.0 / m;
		
		
		for (int i = 0; i < N2; i++){
			for (int j = 0; j < m; j++){
				z2[i][j] = (z2[i][j] + mid) / 2;
			}
		}
		
		lambda_ = new double[N1 + N2][m];
		
		for (int i = 0; i < N1; i++){
			for (int j = 0; j < m; j++)
				lambda_[i][j] = z1[i][j];
		}
		
		
		for (int i = 0; i < N2; i++){
			for (int j = 0; j < m; j++)
				lambda_[i + N1][j] = z2[i][j];
		}

	}
	
	
	public static int getCombin(int n, int m) {
		if (m == 0)
			return 1;
		if (m > n / 2)
			m = n - m;
		int res = 1;
		for (int k = 1; k <= m; k++)
			res = (n - k + 1) * res / k;
		return res;
	}
	
	
	public void generateWeightVector(double[][] z, int divisions, int m) {

		int[] tr = new int[m];

		gn = 0;

		Traverse(z, tr, m, 0, divisions);

		for (int i = 0; i < z.length; i++) {
			for (int j = 0; j < z[i].length; j++) {
				z[i][j] = (double) z[i][j] / divisions;
			}
		}


	}

	static void Traverse(double[][] z, int[] tr, int m, int i, int divisions) {
		if (i == (m - 1)) {
			tr[i] = divisions;
			for (int k = 0; k < m; k++) {
				z[gn][k] = tr[k];
			}
			gn++;
			return;
		}

		for (int k = 0; k <= divisions; k++) {
			tr[i] = k;
			Traverse(z, tr, m, i + 1, divisions - k);
		}

	}
	
	
	public static void main(String args[]){
/*		WeightVectorGeneratorV3 wv = new WeightVectorGeneratorV3(8, 0, 8);
		
		System.out.println(wv.lambda_.length);
		
		
		double[][] lambda = wv.lambda_;
		
		System.out.println(lambda.length);
		for (int i = 0; i < lambda.length; i++){
			if (lambda[i][0] == 0  || lambda[i][1] == 0
					|| lambda[i][2] == 0 || lambda[i][3] == 0 
					|| lambda[i][4] == 0 || lambda[i][5] == 0
					|| lambda[i][6] == 0 || lambda[i][7] == 0)
				continue;
			for (int j = 0; j < lambda[i].length; j++){
				System.out.print(lambda[i][j] + "\t");
			}

		//	System.out.println();
			System.out.println();
		}*/
		
		
		System.out.println(String.format("%E", Math.pow(10, -1)));
		
	}
}
