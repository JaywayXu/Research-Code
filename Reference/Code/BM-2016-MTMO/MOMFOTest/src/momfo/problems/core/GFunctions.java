package momfo.problems.core;

public class GFunctions {

	public static double getSphere(double[] x, int startPos, int endPos) {
		double sum = 0;

		for (int i = startPos; i <= endPos; i++)
			sum += (x[i] * x[i]);

		return 1 + sum;
	}

	public static double getMean(double[] x, int startPos, int endPos) {
		int n = endPos - startPos + 1;
		double sum = 0;
		for (int i = startPos; i <= endPos; i++)
			sum += Math.abs(x[i]);

		return 1 + (sum * 9) / n;
	}

	public static double getAckley(double[] x, int startPos, int endPos) {
		int n = endPos - startPos + 1;

		double sum1 = 0;
		double sum2 = 0;

		for (int i = startPos; i <= endPos; i++) {
			sum1 += (x[i] * x[i]);
			sum2 += Math.cos(2 * Math.PI * x[i]);
		}

		return 21 + Math.E - 20 * Math.exp(-0.2 * Math.sqrt(sum1 / n)) - Math.exp(sum2 / n);
	}

	public static double getRastrigin(double[] x, int startPos, int endPos) {
		double sum = 0;
		for (int i = startPos; i <= endPos; i++) {
			double val = x[i] * x[i] - 10 * Math.cos(2 * Math.PI * x[i]) + 10;
			sum += val;
		}

		return 1 + sum;
	}

	public static double getGriewank(double[] x, int startPos, int endPos) {
		double sum = 0;
		double product = 1;

		for (int i = startPos; i <= endPos; i++) {
			sum += (x[i] * x[i]);
			product *= Math.cos(x[i] / Math.sqrt(i - startPos + 1));
		}

		return 2 + sum / 4000 - product;
	}

	public static double getRosenbrock(double[] x, int startPos, int endPos) {
		double sum = 0;
		for (int i = startPos; i < endPos; i++) {
			double val = 100 * (x[i] * x[i] - x[i + 1]) * (x[i] * x[i] - x[i + 1]) + (1 - x[i]) * (1 - x[i]);
			sum += val;
		}
		return 1 + sum;
	}
}
