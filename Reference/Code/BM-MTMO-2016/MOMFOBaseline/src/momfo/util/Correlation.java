package momfo.util;

import java.util.*;

import momfo.core.Problem;
import momfo.core.ProblemSet;
import momfo.core.Solution;

// Various correlation coefficients
public class Correlation {

	public static double getSimilarity(int i, int j, int N, ProblemSet problemSet) throws ClassNotFoundException, JMException {
		Problem p1 = problemSet.get(i);
		Problem p2 = problemSet.get(j);

		double x[] = new double[N];
		double y[] = new double[N];

		for (int k = 0; k < N; k++) {
			Solution sol = new Solution(problemSet);

			p1.evaluate(sol);
			x[k] = sol.getGFunValue();

			p2.evaluate(sol);
			y[k] = sol.getGFunValue();
		}

		return spearman(x, y);
	}

	public static double rankKendallTauBeta(double[] x, double[] y) {
		assert x.length == y.length;
		int x_n = x.length;
		int y_n = y.length;
		double[] x_rank = new double[x_n];
		double[] y_rank = new double[y_n];

		TreeMap<Double, HashSet<Integer>> sorted = new TreeMap<Double, HashSet<Integer>>();
		for (int i = 0; i < x_n; i++) {
			double v = x[i];
			if (sorted.containsKey(v) == false)
				sorted.put(v, new HashSet<Integer>());
			sorted.get(v).add(i);
		}

		int c = 1;
		for (double v : sorted.descendingKeySet()) {
			double r = 0;
			for (int i : sorted.get(v)) {
				r += c;
				c++;
			}

			r /= sorted.get(v).size();

			for (int i : sorted.get(v)) {
				x_rank[i] = r;
			}
		}

		sorted.clear();
		for (int i = 0; i < y_n; i++) {
			double v = y[i];
			if (sorted.containsKey(v) == false)
				sorted.put(v, new HashSet<Integer>());
			sorted.get(v).add(i);
		}

		c = 1;
		for (double v : sorted.descendingKeySet()) {
			double r = 0;
			for (int i : sorted.get(v)) {
				r += c;
				c++;
			}

			r /= sorted.get(v).size();

			for (int i : sorted.get(v)) {
				y_rank[i] = r;
			}
		}

		return kendallTauBeta(x_rank, y_rank);
	}

	public static double kendallTauBeta(double[] x, double[] y) {
		assert x.length == y.length;

		int c = 0;
		int d = 0;
		HashMap<Double, HashSet<Integer>> xTies = new HashMap<Double, HashSet<Integer>>();
		HashMap<Double, HashSet<Integer>> yTies = new HashMap<Double, HashSet<Integer>>();

		for (int i = 0; i < x.length - 1; i++) {
			for (int j = i + 1; j < x.length; j++) {
				if (x[i] > x[j] && y[i] > y[j]) {
					c++;
				} else if (x[i] < x[j] && y[i] < y[j]) {
					c++;
				} else if (x[i] > x[j] && y[i] < y[j]) {
					d++;
				} else if (x[i] < x[j] && y[i] > y[j]) {
					d++;
				} else {
					if (x[i] == x[j]) {
						if (xTies.containsKey(x[i]) == false)
							xTies.put(x[i], new HashSet<Integer>());
						xTies.get(x[i]).add(i);
						xTies.get(x[i]).add(j);
					}

					if (y[i] == y[j]) {
						if (yTies.containsKey(y[i]) == false)
							yTies.put(y[i], new HashSet<Integer>());
						yTies.get(y[i]).add(i);
						yTies.get(y[i]).add(j);
					}
				}
			}
		}

		int diff = c - d;
		double denom = 0;

		double n0 = (x.length * (x.length - 1)) / 2.0;
		double n1 = 0;
		double n2 = 0;

		for (double t : xTies.keySet()) {
			double s = xTies.get(t).size();
			n1 += (s * (s - 1)) / 2;
		}

		for (double t : yTies.keySet()) {
			double s = yTies.get(t).size();
			n2 += (s * (s - 1)) / 2;
		}

		denom = Math.sqrt((n0 - n1) * (n0 - n2));

		double t = diff / denom;

		assert t >= -1 && t <= 1 : t;

		return t;
	}

	public static double pearson(double[] x, double[] y) {
		assert x.length == y.length;
		double mean_x = 0;
		double mean_y = 0;
		int n_x = x.length;
		int n_y = y.length;
		for (int i = 0; i < n_x; i++) {
			mean_x += x[i];
			mean_y += y[i];
		}
		mean_x /= n_x;
		mean_y /= n_y;

		double cov = 0;
		double sd_x = 0;
		double sd_y = 0;

		for (int i = 0; i < n_x; i++) {
			cov += (x[i] - mean_x) * (y[i] - mean_y);
			sd_x += (x[i] - mean_x) * (x[i] - mean_x);
			sd_y += (y[i] - mean_y) * (y[i] - mean_y);
		}

		if (cov == 0) {
			return 0;
		} else {
			double r = cov / (Math.sqrt(sd_x) * Math.sqrt(sd_y));
			assert r >= -1 && r <= 1 : r + "\n" + printArray(x) + printArray(y) + "Mean x = " + mean_x + ", Mean y = "
					+ mean_y + ", Cov = " + cov + ", SD x = " + sd_x + ", SD y = " + sd_y + "\n";
			return r;
		}
	}

	private static String printArray(double[] a) {
		String ret = "";
		for (double d : a) {
			ret = ret + d + " ";
		}
		ret = ret + "\n";
		return ret;
	}

	public static double spearman(double[] x, double[] y) {
		assert x.length == y.length;
		int x_n = x.length;
		int y_n = y.length;
		double[] x_rank = new double[x_n];
		double[] y_rank = new double[y_n];

		TreeMap<Double, HashSet<Integer>> sorted = new TreeMap<Double, HashSet<Integer>>();
		for (int i = 0; i < x_n; i++) {
			double v = x[i];
			if (sorted.containsKey(v) == false)
				sorted.put(v, new HashSet<Integer>());
			sorted.get(v).add(i);
		}

		int c = 1;
		for (double v : sorted.descendingKeySet()) {
			double r = 0;
			for (int i : sorted.get(v)) {
				r += c;
				c++;
			}

			r /= sorted.get(v).size();

			for (int i : sorted.get(v)) {
				x_rank[i] = r;
			}
		}

		sorted.clear();
		for (int i = 0; i < y_n; i++) {
			double v = y[i];
			if (sorted.containsKey(v) == false)
				sorted.put(v, new HashSet<Integer>());
			sorted.get(v).add(i);
		}

		c = 1;
		for (double v : sorted.descendingKeySet()) {
			double r = 0;
			for (int i : sorted.get(v)) {
				r += c;
				c++;
			}

			r /= sorted.get(v).size();

			for (int i : sorted.get(v)) {
				y_rank[i] = r;
			}
		}

		return pearson(x_rank, y_rank);
	}

	public static void main(String[] args) {
		double[] x = { 0.5, 0.7, 0, 0.3, 0, 0.3, 0.9 };
		double[] y = { 0, 0.3, 0, 0.4, 0, 0.1, 0.6 };
		System.out.println("Pearson's r: " + pearson(x, y));
		System.out.println("Spearman's rho: " + spearman(x, y));
		System.out.println("Kendall's tau: " + rankKendallTauBeta(x, y));
	}

}