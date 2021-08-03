package momfo.problems.singletask;

import jmetal.core.Problem;
import jmetal.core.Solution;
import jmetal.core.Variable;
import jmetal.encodings.solutionType.BinaryRealSolutionType;
import jmetal.encodings.solutionType.RealSolutionType;
import jmetal.util.JMException;
import momfo.problems.core.GFunctions;

public class NIMS1 extends Problem {
	public NIMS1(String solutionType) {
		numberOfVariables_ = 20;
		numberOfObjectives_ = 3;
		numberOfConstraints_ = 0;
		problemName_ = "NIMS1";

		lowerLimit_ = new double[numberOfVariables_];
		upperLimit_ = new double[numberOfVariables_];
		
		
		lowerLimit_[0] = lowerLimit_[1] = 0;
		upperLimit_[0] = upperLimit_[1] = 1;
		
		for (int i = 2; i < numberOfVariables_; i++) {
			lowerLimit_[i] = -20;
			upperLimit_[i] = 20;
		}


		if (solutionType.compareTo("BinaryReal") == 0)
			solutionType_ = new BinaryRealSolutionType(this);
		else if (solutionType.compareTo("Real") == 0)
			solutionType_ = new RealSolutionType(this);
		else {
			System.out.println("Error: solution type " + solutionType + " invalid");
			System.exit(-1);
		}
	} // NIHS1
	
	
	@Override
	public void evaluate(Solution solution) throws JMException {
		Variable[] decisionVariables = solution.getDecisionVariables();

		double[] f = new double[numberOfObjectives_]; 
		double[] x = new double[numberOfVariables_]; 

		for (int i = 0; i < numberOfVariables_; i++)
			x[i] = decisionVariables[i].getValue();

		double q = GFunctions.getRosenbrock(x, 2, numberOfVariables_ - 1);
		
		f[0] = q * Math.cos(0.5 * Math.PI * x[0]) * Math.cos(0.5 * Math.PI * x[1]);
		f[1] = q * Math.cos(0.5 * Math.PI * x[0]) * Math.sin(0.5 * Math.PI * x[1]);
		f[2] = q * Math.sin(0.5 * Math.PI * x[0]);
		
		solution.setObjective(0, f[0]);
		solution.setObjective(1, f[1]);
		solution.setObjective(2, f[2]);

	}

}
