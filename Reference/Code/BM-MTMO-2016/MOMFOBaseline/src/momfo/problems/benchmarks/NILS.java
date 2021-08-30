package momfo.problems.benchmarks;

import java.io.IOException;

import momfo.core.Problem;
import momfo.core.ProblemSet;
import momfo.problems.base.*;


public class NILS {


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
		MMDTLZ prob = new MMDTLZ(3, 25, 1, -50,50);
		prob.setGType("griewank");

		
		double shiftValues[] = IO.readShiftValuesFromFile("SVData/S_NILS_1.txt");
		prob.setShiftValues(shiftValues);
				
		((Problem)prob).setName("NILS1");
		
		problemSet.add(prob);
		return problemSet;
	}

	public static ProblemSet getT2() throws IOException {
		ProblemSet problemSet = new ProblemSet(1);
		
		MMZDT prob = new MMZDT(50, 2,  -100,100);
		prob.setGType("ackley");
		prob.setHType("concave");
		
		((Problem)prob).setName("NILS2");

		problemSet.add(prob);
		return problemSet;
	}
}
