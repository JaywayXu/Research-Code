package core;

public abstract class Problem {
	protected int n1; // the number of decision variables in T1
	protected int nobj1; // the number of objectives in T1
	protected double[] lowerLimit1; // lower limit for each variable in T1
	protected double[] upperLimit1; // upper limit for each variable in T1

	protected int n2; // the number of decision variables in T2
	protected int nobj2; // the number of objectives in T2
	protected double[] lowerLimit2; // lower limit for each variable in T2
	protected double[] upperLimit2; // upper limit for each variable in T2

	/*
	 * the dimensionality of the first part (xI) of the decision variables
	 */
	protected int m;

	/*
	 * evaluate a solution on the task T1, x.length should be n1, return the
	 * objective values for T1
	 */
	public abstract double[] evaluate_T1(double[] x);

	/*
	 * evaluate a solution on the task T2, x.length should be n2, return the
	 * objective values for T2
	 */
	public abstract double[] evaluate_T2(double[] x);

	// return the number of decision variables in T1
	public int getNumberOfDecisionVariables_T1() {
		return n1;
	}

	// return the number of objectives in T1
	public int getNumberOfObjectives_T1() {
		return nobj1;
	}

	// return the upper limit in the i-th dimension of T1
	public double getUpperLimit_T1(int i) {
		return upperLimit1[i];
	}

	// return the lower limit in the i-th dimension of T1
	public double getLowerLimit_T1(int i) {
		return lowerLimit1[i];
	}

	// return the number of decision variables in T2
	public int getNumberOfDecisionVariables_T2() {
		return n2;
	}

	// return the number of objectives in T2
	public int getNumberOfObjectives_T2() {
		return nobj2;
	}

	// return the upper limit in the i-th dimension of T2
	public double getUpperLimit_T2(int i) {
		return upperLimit2[i];
	}

	// return the lower limit in the i-th dimension of T2
	public double getLowerLimit_T2(int i) {
		return lowerLimit2[i];
	}
}
