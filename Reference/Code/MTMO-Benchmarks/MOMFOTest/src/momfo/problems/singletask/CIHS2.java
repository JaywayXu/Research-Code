package momfo.problems.singletask;

import jmetal.core.Problem;
import jmetal.core.Solution;
import jmetal.core.Variable;
import jmetal.encodings.solutionType.BinaryRealSolutionType;
import jmetal.encodings.solutionType.RealSolutionType;
import jmetal.util.JMException;
import momfo.problems.core.GFunctions;

public class CIHS2 extends Problem {
	public CIHS2(String solutionType) {
		numberOfVariables_ = 50;
		numberOfObjectives_ = 2;
		numberOfConstraints_ = 0;
		problemName_ = "CIHS2";

		lowerLimit_ = new double[numberOfVariables_];
		upperLimit_ = new double[numberOfVariables_];
		
		
		lowerLimit_[0] = 0;
		upperLimit_[0] = 1;
		
		for (int i = 1; i < numberOfVariables_; i++) {
			lowerLimit_[i] = -100;
			upperLimit_[i] = 100;
		}


		if (solutionType.compareTo("BinaryReal") == 0)
			solutionType_ = new BinaryRealSolutionType(this);
		else if (solutionType.compareTo("Real") == 0)
			solutionType_ = new RealSolutionType(this);
		else {
			System.out.println("Error: solution type " + solutionType + " invalid");
			System.exit(-1);
		}
	} // CIHS1
	@Override
	public void evaluate(Solution solution) throws JMException {
		Variable[] decisionVariables = solution.getDecisionVariables();

		double[] f = new double[numberOfObjectives_]; 
		double[] x = new double[numberOfVariables_]; 

		for (int i = 0; i < numberOfVariables_; i++)
			x[i] = decisionVariables[i].getValue();

		double q = GFunctions.getMean(x, 1, numberOfVariables_ - 1);
		
		f[0] = x[0];
		f[1] = q * (1 - (x[0] / q) * (x[0] / q));
		
		solution.setObjective(0, f[0]);
		solution.setObjective(1, f[1]);
	}

}
