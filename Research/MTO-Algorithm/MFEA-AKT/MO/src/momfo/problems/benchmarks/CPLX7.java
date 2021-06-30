package momfo.problems.benchmarks;

import java.io.IOException;

import momfo.core.Problem;
import momfo.core.ProblemSet;
import momfo.problems.LZ09.*;


public class CPLX7 {
	
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
		
		LZ09_F4 prob = new LZ09_F4(2,30);
		
		((Problem)prob).setName("CPLX7-1");
		prob.setHType("LZ09_F4");		
		problemSet.add(prob);
		
		return problemSet;
	}
	
	
	public static ProblemSet getT2() throws IOException {
		ProblemSet problemSet = new ProblemSet(1);
		
		LZ09_F5 prob = new LZ09_F5(2,30);

		((Problem)prob).setName("CPLX7-2");
		prob.setHType("LZ09_F5");		
		problemSet.add(prob);
		
		return problemSet;
	}
}
