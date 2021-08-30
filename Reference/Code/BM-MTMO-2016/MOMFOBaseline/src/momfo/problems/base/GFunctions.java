package momfo.problems.base;

public class GFunctions {
	public static double getSphere(double x[]) {
		double sum = 0;
		for (int i = 0; i < x.length; i++)
			sum += (x[i] * x[i]);
		return sum;
	}

	public static double getRosenbrock(double x[]) {
		double sum = 0;

		for (int i = 0; i < x.length - 1; i++) {
			double t = 100 * (x[i] * x[i] - x[i + 1]) * (x[i] * x[i] - x[i + 1]) + (1 - x[i]) * (1 - x[i]);
			sum += t;
		}

		return sum;
	}

	public static double getAckley(double x[]) {
		double sum1 = 0;
		double sum2 = 0;

		for (int i = 0; i < x.length; i++) {
			sum1 += ((x[i] * x[i]) / x.length);
			sum2 += (Math.cos(2 * Math.PI * x[i]) / x.length);
		}

		return -20 * Math.exp(-0.2 * Math.sqrt(sum1)) - Math.exp(sum2) + 20 + Math.E;

	}

	public static double getGriewank(double x[]) {
		int k = 1;

		double sum = 0;
		double prod = 1; 

		for (int i = 0; i < x.length; i++) {
			sum += (x[i] * x[i]);
			prod *= (k * Math.cos(x[i] / Math.sqrt(i + 1)));
		}

		return k + sum / 4000 - prod;

	}


	public static double getRastrigin(double x[]) {

		double result = 0.0;
		double a = 10.0;
		double w = 2 * Math.PI;

		for (int i = 0; i < x.length; i++) {
			result += x[i] * x[i] - a * Math.cos(w * x[i]);
		}
		result += a * x.length;

		return result;
	}


	public static double getMean(double x[]) {
		double mean = 0;
		for (int i = 0; i < x.length; i++)
			mean += Math.abs(x[i]);

		mean /= x.length;

		return 9 * mean;
	}

}
