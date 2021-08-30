package momfo.problems.base;

import momfo.core.Problem;
import momfo.core.Solution;
import momfo.util.JMException;

public class MMDTLZ extends Problem {
	String gType_;
	Integer alpha_;

	public MMDTLZ(int numberOfObjectives, int numberOfVariables, int alpha, double lg, double ug) {
		numberOfObjectives_ = numberOfObjectives;
		numberOfVariables_ = numberOfVariables;

		gType_ = "sphere";

		alpha_ = alpha;

		int num = numberOfVariables_ - numberOfObjectives_ + 1;

		// System.out.println(num);

		shiftValues_ = new double[num];
		rotationMatrix_ = new double[num][num];

		upperLimit_ = new double[numberOfVariables_];
		lowerLimit_ = new double[numberOfVariables_];

		for (int var = 0; var < numberOfObjectives_ - 1; var++) {
			lowerLimit_[var] = 0.0;
			upperLimit_[var] = 1.0;
		} // for

		for (int var = numberOfObjectives_ - 1; var < numberOfVariables; var++) {
			lowerLimit_[var] = lg;
			upperLimit_[var] = ug;
		}

		for (int i = 0; i < num; i++)
			shiftValues_[i] = 0;

		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {
				if (i != j)
					rotationMatrix_[i][j] = 0;
				else
					rotationMatrix_[i][j] = 1;
			}
		}

		if (numberOfObjectives == 2)
			hType_ = "circle";
		else
			hType_ = "sphere";
	}

	public MMDTLZ(int numberOfObjectives, int numberOfVariables, int alpha, double lg, double ug, String gType,
			double[] shiftValues, double[][] rotationMatrix) {
		numberOfObjectives_ = numberOfObjectives;
		numberOfVariables_ = numberOfVariables;

		alpha_ = alpha;
		gType_ = gType;
		shiftValues_ = shiftValues;
		rotationMatrix_ = rotationMatrix;

		upperLimit_ = new double[numberOfVariables_];
		lowerLimit_ = new double[numberOfVariables_];

		for (int var = 0; var < numberOfObjectives_ - 1; var++) {
			lowerLimit_[var] = 0.0;
			upperLimit_[var] = 1.0;
		} // for

		for (int var = numberOfObjectives_ - 1; var < numberOfVariables; var++) {
			lowerLimit_[var] = lg;
			upperLimit_[var] = ug;
		}
		if (numberOfObjectives == 2)
			hType_ = "circle";
		else
			hType_ = "sphere";
	}

	public void evaluate(Solution solution) throws JMException {
		double vars[] = scaleVariables(solution);

		double[] xI = new double[numberOfObjectives_ - 1];
		double[] xII = new double[numberOfVariables_ - numberOfObjectives_ + 1];

		for (int i = 0; i < numberOfObjectives_ - 1; i++)
			xI[i] = vars[i];

		for (int i = numberOfObjectives_ - 1; i < numberOfVariables_; i++)
			xII[i - numberOfObjectives_ + 1] = vars[i];
		xII = transformVariables(xII);

		double[] f = new double[numberOfObjectives_];

		double g = evalG(xII);

		for (int i = 0; i < numberOfObjectives_; i++)
			f[i] = 1 + g;

		solution.setGFunValue(1 + g);

		for (int i = 0; i < numberOfObjectives_; i++) {
			for (int j = 0; j < numberOfObjectives_ - (i + 1); j++)
				f[i] *= Math.cos(Math.pow(xI[j], alpha_) * 0.5 * Math.PI);
			if (i != 0) {
				int aux = numberOfObjectives_ - (i + 1);
				f[i] *= Math.sin(Math.pow(xI[aux], alpha_) * 0.5 * Math.PI);
			} // if
		} // for

		for (int i = 0; i < numberOfObjectives_; i++)
			solution.setObjective(startObjPos_ + i, f[i]);
	}

	double evalG(double[] xII) throws JMException {
		if (gType_.equalsIgnoreCase("sphere"))
			return GFunctions.getSphere(xII);
		else if (gType_.equalsIgnoreCase("rosenbrock"))
			return GFunctions.getRosenbrock(xII);
		else if (gType_.equalsIgnoreCase("ackley"))
			return GFunctions.getAckley(xII);
		else if (gType_.equalsIgnoreCase("griewank"))
			return GFunctions.getGriewank(xII);
		else if (gType_.equalsIgnoreCase("rastrigin"))
			return GFunctions.getRastrigin(xII);
		else if (gType_.equalsIgnoreCase("mean"))
			return GFunctions.getMean(xII);
		else {
			System.out.println("Error: g function type " + gType_ + " invalid");
			return Double.NaN;
		}
	}

	public void setGType(String gType) {
		gType_ = gType;
	}

	public String getHType() {
		return hType_;
	}

}
