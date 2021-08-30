package momfo.util.vector;

public class OneLevelWeightVectorGenerator extends VectorGenerator {

	int divisions;
	int m;
	


	static int gn;
	


	public OneLevelWeightVectorGenerator(int divisions, int m){
		this.divisions = divisions;
		this.m = m;
		
		int N = getCombin(m + divisions - 1, divisions);
	//	System.out.println(N);
		
		lambda_ = new double[N][m];
		
		generateWeightVector(divisions, m);
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

	public void generateWeightVector(int divisions, int m) {

		int[] tr = new int[m];

		gn = 0;

		Traverse(lambda_, tr, m, 0, divisions);

		for (int i = 0; i < lambda_.length; i++) {
			for (int j = 0; j < lambda_[i].length; j++) {
				lambda_[i][j] = (double) lambda_[i][j] / divisions;
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

	
	
}
