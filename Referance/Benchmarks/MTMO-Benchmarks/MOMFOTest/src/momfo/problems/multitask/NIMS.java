package momfo.problems.multitask;

import java.io.IOException;

import momfo.problems.core.GFunctions;
import momfo.problems.core.IO;
import momfo.problems.core.MOMFOProblem;

public class NIMS extends MOMFOProblem {
	
	private double[][] mnm2;
	
	public NIMS() throws IOException {
		n1 = n2 = 20;
		nobj1 = 3;
		nobj2 = 2;
		m = 2;
		
		lowerLimit1 = new double[n1];
		upperLimit1 = new double[n1];
		lowerLimit2 = new double[n2];
		upperLimit2 = new double[n2];
		
		lowerLimit1[0] = lowerLimit1[1] = 0;
		upperLimit1[0] = upperLimit1[1] = 1;
		lowerLimit2[0] = lowerLimit2[1] = 0;
		upperLimit2[0] = upperLimit2[1] = 1;
		
		for (int i = 2; i < n1; i++) {
			lowerLimit1[i] = -20;
			upperLimit1[i] = 20;
		}
		
		for (int i = 2; i < n2; i++) {
			lowerLimit2[i] = -20;
			upperLimit2[i] = 20;
		}
	
		mnm2 = IO.readRotationMatrix("Mdata/M_NIMS_2.txt");
	}
	
	@Override
	public double[] evaluate_T1(double[] x) {
		double[] f = new double[nobj1];
		
		double q = GFunctions.getRosenbrock(x, m, n1 - 1);
		
		f[0] = q * Math.cos(0.5 * Math.PI * x[0]) * Math.cos(0.5 * Math.PI * x[1]);
		f[1] = q * Math.cos(0.5 * Math.PI * x[0]) * Math.sin(0.5 * Math.PI * x[1]);
		f[2] = q * Math.sin(0.5 * Math.PI * x[0]);
		return f;
	}

	@Override
	public double[] evaluate_T2(double[] x) {
		double[] f = new double[nobj2];
		
		double[] z = new double[n2 - m];
		for (int i = 0; i < n2 - m; i++) {
			double sum = 0;
			for (int j = 0; j < n2 - m; j++) 
				sum += mnm2[i][j] * (x[j + m]);
			z[i] = sum;
		}
		
		double q = GFunctions.getSphere(z, 0, z.length - 1);
		
		f[0] = 0.5 * (x[0] + x[1]);
		f[1] = q * (1 - (f[0] / q) * (f[0] / q));
		
		return f;
	}
	
}
