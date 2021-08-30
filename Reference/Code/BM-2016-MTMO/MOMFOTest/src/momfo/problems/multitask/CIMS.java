package momfo.problems.multitask;

import java.io.IOException;

import momfo.problems.core.GFunctions;
import momfo.problems.core.IO;
import momfo.problems.core.MOMFOProblem;

public class CIMS extends MOMFOProblem {
	
	private double[] scm2;
	private double[][] mcm2;
	
	public CIMS() throws IOException {
		n1 = n2 = 10;
		nobj1 = nobj2 = 2;
		m = 1;
		
		lowerLimit1 = new double[n1];
		upperLimit1 = new double[n1];
		lowerLimit2 = new double[n2];
		upperLimit2 = new double[n2];
		
		lowerLimit1[0] = 0;
		upperLimit1[0] = 1;
		lowerLimit2[0] = 0;
		upperLimit2[0] = 1;
		
		for (int i = 1; i < n1; i++) {
			lowerLimit1[i] = -5;
			upperLimit1[i] = 5;
		}
		
		for (int i = 1; i < n2; i++) {
			lowerLimit2[i] = -5;
			upperLimit2[i] = 5;
		}
		
		
		scm2 = IO.readShiftVector("SVData/S_CIMS_2.txt");
		mcm2 = IO.readRotationMatrix("MData/M_CIMS_2.txt");
	}

	@Override
	public double[] evaluate_T1(double[] x) {
		double[] f = new double[nobj1];
		
		double q = GFunctions.getRosenbrock(x, m, n1 - 1);
		
		f[0] = x[0];
		f[1] = q * (1 - (x[0] / q) * (x[0] / q));
		return f;
	}

	@Override
	public double[] evaluate_T2(double[] x) {
		double[] f = new double[nobj1];
		double[] z = new double[n2 - m];
		
		for (int i = 0; i < n2 - m; i++) {
			double sum = 0;
			for (int j = 0; j < n2 - m; j++) 
				sum += mcm2[i][j] * (x[j + m] - scm2[j]);
			z[i] = sum;
		}
		
		double q = GFunctions.getMean(z, 0, z.length - 1);
		
		f[0] = q * Math.cos(0.5 * Math.PI * x[0]);
		f[1] = q * Math.sin(0.5 * Math.PI * x[0]);
		return f;
	}
}
