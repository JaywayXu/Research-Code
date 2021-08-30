package momfo.problems.multitask;

import java.io.IOException;

import momfo.problems.core.GFunctions;
import momfo.problems.core.IO;
import momfo.problems.core.MOMFOProblem;

public class PIMS extends MOMFOProblem {
	
	private double[] spm1;
	private double[][] mpm1;
	
	private double[][] mpm2;
	
	public PIMS() throws IOException {
		n1 = n2 = 50;
		nobj1 = nobj2 = 2;
		m = 1;
		
		lowerLimit1 = new double[n1];
		upperLimit1 = new double[n1];
		lowerLimit2 = new double[n2];
		upperLimit2 = new double[n2];
		
		
		for (int i = 0; i < n1; i++) {
			lowerLimit1[i] = 0;
			upperLimit1[i] = 1;
		}
		
		for (int i = 0; i < n2; i++) {
			lowerLimit2[i] = 0;
			upperLimit2[i] = 1;
		}
		
		spm1 = IO.readShiftVector("SVData/S_PIMS_1.txt");
		mpm1 = IO.readRotationMatrix("MData/M_PIMS_1.txt");
		
		mpm2 = IO.readRotationMatrix("MData/M_PIMS_2.txt");
	}

	@Override
	public double[] evaluate_T1(double[] x) {
		double[] f = new double[nobj1];
		
		double[] z = new double[n2 - m];
		for (int i = 0; i < n2 - m; i++) {
			double sum = 0;
			for (int j = 0; j < n2 - m; j++) 
				sum += mpm1[i][j] * (x[j + m] - spm1[j]);
			z[i] = sum;
		}
		
		double q = GFunctions.getSphere(z, 0, z.length - 1);
		
		f[0] = q * Math.cos(0.5 * Math.PI * x[0]);
		f[1] = q * Math.sin(0.5 * Math.PI * x[0]);
		return f;
	}

	@Override
	public double[] evaluate_T2(double[] x) {
		double[] f = new double[nobj2];
		
		double[] z = new double[n2 - m];
		for (int i = 0; i < n2 - m; i++) {
			double sum = 0;
			for (int j = 0; j < n2 - m; j++) 
				sum += mpm2[i][j] * (x[j + m]);
			z[i] = sum;
		}
		
		double q = GFunctions.getRastrigin(z, 0, z.length - 1);
		
		f[0] = x[0];
		f[1] = q * (1 - (x[0] / q) * (x[0] / q));
		return f;
	}
}
