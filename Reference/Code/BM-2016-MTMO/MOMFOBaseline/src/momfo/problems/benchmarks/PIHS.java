package momfo.problems.benchmarks;

import java.io.IOException;

import momfo.core.Problem;
import momfo.core.ProblemSet;
import momfo.problems.base.*;


public class PIHS {

	public static ProblemSet getProblemSet() throws IOException {
		ProblemSet ps1 = getT1();
		ProblemSet ps2 = getT2();
		ProblemSet problemSet = new ProblemSet(2);

		problemSet.add(ps1.get(0));
		problemSet.add(ps2.get(0));
		return problemSet;

	}

	public static ProblemSet getT1() throws IOException {
		ProblemSet problemSet = new ProblemSet(1);
		
		MMZDT prob = new MMZDT(50, 1,  -100,100);
		prob.setGType("sphere");
		prob.setHType("convex");
		((Problem)prob).setName("PIHS1");
		
		problemSet.add(prob);
		return problemSet;
	}

	public static ProblemSet getT2() throws IOException {
		ProblemSet problemSet = new ProblemSet(1);
		
		MMZDT prob = new MMZDT(50, 1,  -100,100);
		prob.setGType("rastrigin");
		prob.setHType("convex");
		
		double[] shiftValues = IO.readShiftValuesFromFile("SVData/S_PIHS_2.txt");
		prob.setShiftValues(shiftValues);


		((Problem)prob).setName("PIHS2");
		
		problemSet.add(prob);
		return problemSet;
	}
}
