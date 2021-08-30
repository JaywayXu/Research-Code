package momfo.problems.benchmarks;

import java.io.IOException;

import momfo.core.Problem;
import momfo.core.ProblemSet;
import momfo.problems.base.*;

public class PIMS {

	public static ProblemSet getProblem() throws IOException {
		ProblemSet ps1 = getT1();
		ProblemSet ps2 = getT2();
		ProblemSet problemSet = new ProblemSet(2);

		problemSet.add(ps1.get(0));
		problemSet.add(ps2.get(0));

		return problemSet;

	}

	public static ProblemSet getT1() throws IOException {
		ProblemSet problemSet = new ProblemSet(1);

		MMDTLZ prob = new MMDTLZ(2, 50, 1, 0,1);
		prob.setGType("sphere");

		
		double[] shiftValues= IO.readShiftValuesFromFile("SVData/S_PIMS_1.txt");
		prob.setShiftValues(shiftValues);
	
		
		double[][] matrix = IO.readMatrixFromFile("MData/M_PIMS_1.txt");
		prob.setRotationMatrix(matrix);
		
		((Problem)prob).setName("PIMS1");
		
		problemSet.add(prob);

		return problemSet;
	}

	public static ProblemSet getT2() throws IOException {
		ProblemSet problemSet = new ProblemSet(1);

		
		MMZDT prob = new MMZDT(50, 1,  0,1);
		prob.setGType("rastrigin");
		prob.setHType("concave");
		
		
		double[][] matrix = IO.readMatrixFromFile("MData/M_PIMS_2.txt");
		prob.setRotationMatrix(matrix);
		
		((Problem)prob).setName("PIMS2");
		
		problemSet.add(prob);
		
		return problemSet;
	}
}
