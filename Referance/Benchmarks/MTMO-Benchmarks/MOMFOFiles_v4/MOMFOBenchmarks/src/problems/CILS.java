package problems;

import core.GFunctions;
import core.Problem;

public class CILS extends Problem {
	
	public CILS() {
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
			lowerLimit1[i] = -2;
			upperLimit1[i] = 2;
		}
		
		for (int i = 1; i < n2; i++) {
			lowerLimit2[i] = -1;
			upperLimit2[i] = 1;
		}
	}
	
	@Override
	public double[] evaluate_T1(double[] x) {
		double[] f = new double[nobj1];
		double q = GFunctions.getRastrigin(x, m, n1 - 1);
		
		f[0] = q * Math.cos(0.5 * Math.PI * x[0]);
		f[1] = q * Math.sin(0.5 * Math.PI * x[0]);
		return f;
	}

	@Override
	public double[] evaluate_T2(double[] x) {
		double[] f = new double[nobj2];
		double q = GFunctions.getAckley(x, m, n2 - 1);
		
		f[0] = x[0];
		f[1] = q * (1 - Math.sqrt(x[0] / q));
		return f;
	}
	
}
