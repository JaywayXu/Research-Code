package momfo.problems.singletask;

import java.io.IOException;

import jmetal.core.Problem;
import jmetal.core.Solution;
import jmetal.core.Variable;
import jmetal.encodings.solutionType.BinaryRealSolutionType;
import jmetal.encodings.solutionType.RealSolutionType;
import jmetal.util.JMException;
import momfo.problems.core.GFunctions;
import momfo.problems.core.IO;

public class NILS1 extends Problem {
	double[] snl1;
	
	public NILS1(String solutionType) throws IOException {
		numberOfVariables_ = 25;
		numberOfObjectives_ = 3;
		numberOfConstraints_ = 0;
		problemName_ = "NILS1";

		lowerLimit_ = new double[numberOfVariables_];
		upperLimit_ = new double[numberOfVariables_];
		
		
		lowerLimit_[0] = lowerLimit_[1] = 0;
		upperLimit_[0] = upperLimit_[1] = 1;
		
		for (int i = 2; i < numberOfVariables_; i++) {
			lowerLimit_[i] = -50;
			upperLimit_[i] = 50;
		}


		snl1 = IO.readShiftVector("SVdata/S_NILS_1.txt");
		
		if (solutionType.compareTo("BinaryReal") == 0)
			solutionType_ = new BinaryRealSolutionType(this);
		else if (solutionType.compareTo("Real") == 0)
			solutionType_ = new RealSolutionType(this);
		else {
			System.out.println("Error: solution type " + solutionType + " invalid");
			System.exit(-1);
		}
	} // NILS1
	
	@Override
	public void evaluate(Solution solution) throws JMException {
		Variable[] decisionVariables = solution.getDecisionVariables();

		double[] f = new double[numberOfObjectives_]; 
		double[] x = new double[numberOfVariables_]; 

		for (int i = 0; i < numberOfVariables_; i++)
			x[i] = decisionVariables[i].getValue();
		
		double[] z = new double[numberOfVariables_ - 2];
		for (int i = 0; i < numberOfVariables_ - 2; i++) 
			z[i] = x[i + 2] - snl1[i];
		
		double q = GFunctions.getGriewank(z, 0, z.length - 1);
		
		f[0] = q * Math.cos(0.5 * Math.PI * x[0]) * Math.cos(0.5 * Math.PI * x[1]);
		f[1] = q * Math.cos(0.5 * Math.PI * x[0]) * Math.sin(0.5 * Math.PI * x[1]);
		f[2] = q * Math.sin(0.5 * Math.PI * x[0]);
		
		solution.setObjective(0, f[0]);
		solution.setObjective(1, f[1]);
		solution.setObjective(2, f[2]);
		
	}

}
