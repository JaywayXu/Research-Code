package problems;

import java.io.IOException;

import core.GFunctions;
import core.IO;
import core.Problem;

public class PIHS extends Problem {
	private double[] sph2;
	
	public PIHS() throws IOException {
		n1 = n2 = 50;
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
			lowerLimit1[i] = -100;
			upperLimit1[i] = 100;
		}
		
		for (int i = 1; i < n2; i++) {
			lowerLimit2[i] = -100;
			upperLimit2[i] = 100;
		}
		
		sph2 = IO.readShiftVector("SVData/S_PIHS_2.txt");
	}
	@Override
	public double[] evaluate_T1(double[] x) {
		double[] f = new double[nobj1];
		double q = GFunctions.getSphere(x, m, n1 - 1);
		
		f[0] = x[0];
		f[1] = q * (1 - Math.sqrt(x[0] / q));
		return f;
	}

	@Override
	public double[] evaluate_T2(double[] x) {
		double[] f = new double[nobj2];
		double[] z = new double[n2 - m];
		for (int i = 0; i < n2 - m; i++) 
			z[i] = x[i + m] - sph2[i];
		
		double q = GFunctions.getRastrigin(z, 0, z.length - 1);
		
		f[0] = x[0];
		f[1] = q * (1 - Math.sqrt(x[0] / q));
		return f;
	}
	
}
