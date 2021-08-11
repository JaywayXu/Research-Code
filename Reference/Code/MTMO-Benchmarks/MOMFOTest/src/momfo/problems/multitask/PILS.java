package momfo.problems.multitask;

import java.io.IOException;

import momfo.problems.core.GFunctions;
import momfo.problems.core.IO;
import momfo.problems.core.MOMFOProblem;

public class PILS extends MOMFOProblem {

	private double[] spl2;
	
	public PILS() throws IOException {
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
			lowerLimit1[i] = -50;
			upperLimit1[i] = 50;
		}
		
		for (int i = 1; i < n2; i++) {
			lowerLimit2[i] = -100;
			upperLimit2[i] = 100;
		}
		
		spl2 = IO.readShiftVector("SVData/S_PILS_2.txt");
	}
	@Override
	public double[] evaluate_T1(double[] x) {
		double[] f = new double[nobj1];
		double q = GFunctions.getGriewank(x, m, n1 - 1);
		
		f[0] = q * Math.cos(0.5 * Math.PI * x[0]);
		f[1] = q * Math.sin(0.5 * Math.PI * x[0]);
		return f;
	}

	@Override
	public double[] evaluate_T2(double[] x) {
		double[] f = new double[nobj1];
		
		double[] z = new double[n2 - m];
		for (int i = 0; i < n2 - m; i++) 
			z[i] = x[i + m] - spl2[i];
		
		double q = GFunctions.getAckley(z, 0, z.length - 1);
		
		f[0] = q * Math.cos(0.5 * Math.PI * x[0]);
		f[1] = q * Math.sin(0.5 * Math.PI * x[0]);
		return f;
	}

}
