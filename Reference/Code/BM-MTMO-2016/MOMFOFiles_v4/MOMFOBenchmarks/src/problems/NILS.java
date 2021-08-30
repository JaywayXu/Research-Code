package problems;

import java.io.IOException;

import core.GFunctions;
import core.IO;
import core.Problem;

public class NILS extends Problem {
	private double[] snl1;
	
	public NILS() throws IOException {
		n1 = 25;
		n2 = 50;
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
			lowerLimit1[i] = -50;
			upperLimit1[i] = 50;
		}
		
		for (int i = 2; i < n2; i++) {
			lowerLimit2[i] = -100;
			upperLimit2[i] = 100;
		}
		
		snl1 = IO.readShiftVector("SVdata/S_NILS_1.txt");
	}
	
	@Override
	public double[] evaluate_T1(double[] x) {
		double[] f = new double[nobj1];
		
		double[] z = new double[n1 - m];
		for (int i = 0; i < n1 - m; i++) 
			z[i] = x[i + m] - snl1[i];
		
		double q = GFunctions.getGriewank(z, 0, z.length - 1);
		
		f[0] = q * Math.cos(0.5 * Math.PI * x[0]) * Math.cos(0.5 * Math.PI * x[1]);
		f[1] = q * Math.cos(0.5 * Math.PI * x[0]) * Math.sin(0.5 * Math.PI * x[1]);
		f[2] = q * Math.sin(0.5 * Math.PI * x[0]);
		
		return f;
	}

	@Override
	public double[] evaluate_T2(double[] x) {
		double[] f = new double[nobj2];
		
		double q = GFunctions.getAckley(x, m, n2 - 1);
		
		f[0] = 0.5 * (x[0] + x[1]);
		f[1] = q * (1 - (f[0] / q) * (f[0] / q));
		
		return f;
	}

}
