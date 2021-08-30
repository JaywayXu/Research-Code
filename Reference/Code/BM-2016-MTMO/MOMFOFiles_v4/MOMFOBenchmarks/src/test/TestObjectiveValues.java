package test;

import java.io.IOException;

import core.Problem;
import momfo.util.wrapper.XReal;
import momfo.core.ProblemSet;
import momfo.core.Solution;
import momfo.findproblems.*;
import momfo.util.JMException;
import problems.*;

public class TestObjectiveValues {
	public static void main(String[] args) throws IOException, ClassNotFoundException, JMException {
		ProblemSet problemSet = FindPOL.getProblem_POL_1();
		Solution sol = new Solution(problemSet);
		
		XReal vars = new XReal(sol) ;
		
		double x[] = new double[sol.numberOfVariables()];
		
		for (int i = 0; i < sol.numberOfVariables(); i++) {
			double slow = vars.getLowerBound(i);
			double sup = vars.getUpperBound(i);
			
			double plow = problemSet.get(0).getLowerLimit(i);
			double pup = problemSet.get(0).getUpperLimit(i);
			
			double val = vars.getValue(i);
			
			x[i] = plow + ((val - slow) * (pup - plow)) /  (sup - slow);
		}
		
		problemSet.get(0).evaluate(sol);
		
		for (int i = 0; i < sol.getNumberOfObjectives(); i++) 
			System.out.println(sol.getObjective(i));
		
		
		System.out.println("***************************");
		
		
		double f[] = new PILS().evaluate_T1(x);
		for (int i = 0; i < f.length; i++) {
			System.out.println(f[i]);
		}
		
	}
	
}
