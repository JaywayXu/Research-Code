package momfo.test;

import java.io.IOException;
import java.text.DecimalFormat;
import java.util.HashMap;

import jmetal.core.Algorithm;
import jmetal.core.Operator;
import jmetal.core.Problem;
import jmetal.core.SolutionSet;
import jmetal.metaheuristics.nsgaII.NSGAII;
import jmetal.operators.crossover.CrossoverFactory;
import jmetal.operators.mutation.MutationFactory;
import jmetal.operators.selection.SelectionFactory;
import jmetal.qualityIndicator.QualityIndicator;
import jmetal.util.JMException;
import momfo.problems.singletask.*;



public class NSGAII_main {
	public static void main(String args[]) throws JMException, ClassNotFoundException, IOException {
		Problem problem; // The problem to solve
		Algorithm algorithm; // The algorithm to use
		Operator crossover; // Crossover operator
		Operator mutation; // Mutation operator
		Operator selection; // Selection operator

		HashMap parameters;// Operator parameters

		problem = new PIHS1("Real");
		
		System.out.println(problem.getName());
		
		algorithm = new NSGAII(problem);
		// Algorithm parameters
		algorithm.setInputParameter("populationSize", 100);
		algorithm.setInputParameter("maxEvaluations", 100 * 1000);

		// Mutation and Crossover for Real codification
		parameters = new HashMap();
		parameters.put("probability", 0.9);
		parameters.put("distributionIndex", 20.0);
		crossover = CrossoverFactory.getCrossoverOperator("SBXCrossover", parameters);

		parameters = new HashMap();
		parameters.put("probability", 1.0 / problem.getNumberOfVariables());
		parameters.put("distributionIndex", 20.0);
		mutation = MutationFactory.getMutationOperator("PolynomialMutation", parameters);

		// Selection Operator
		parameters = null;
		selection = SelectionFactory.getSelectionOperator("BinaryTournament2", parameters);

		// Add the operators to the algorithm
		algorithm.addOperator("crossover", crossover);
		algorithm.addOperator("mutation", mutation);
		algorithm.addOperator("selection", selection);

		System.out.println("RunID\t" + "IGD for " + problem.getName());
		DecimalFormat form = new DecimalFormat("#.####E0");
		System.out.println(getPF(problem));
		QualityIndicator indicator = new QualityIndicator(problem, getPF(problem));
		
		
		int times = 30;
		double aveIGD = 0;
		for (int i = 1; i <= times; i++) {
			SolutionSet population = algorithm.execute();
			population.printObjectivesToFile("1.txt");
			double igd = indicator.getIGD(population);
			aveIGD += igd;
			System.out.println(i + "\t" + form.format(igd));;
		}
		
		System.out.println();
		System.out.println("Average IGD for " + problem.getName() + ": " + form.format(aveIGD / times));
	}
	
	
	public static String getPF(Problem problem) {
		String root = "PF/";
		String path = null;

		String probName = problem.getName();

		boolean isConvex = probName.equals("CILS2") || probName.equals("PIHS1") || probName.equals("PIHS2")
				|| probName.equals("NIHS2");
		
		boolean isConcave = probName.equals("CIHS2") || probName.equals("CIMS1") || probName.equals("PIMS2")
				|| probName.equals("NIMS2") || probName.equals("NILS2");
		
		boolean isCircle = probName.equals("CIHS1") || probName.equals("CIMS2") || probName.equals("CILS1")
				|| probName.equals("PIMS1") || probName.equals("PILS1") || probName.equals("PILS2")
				|| probName.equals("NIHS1");

		boolean isSphere = probName.equals("NIMS1") || probName.equals("NILS1");

		if (isConvex)
			path = root + "convex.pf";
		else if (isConcave)
			path = root + "concave.pf";
		else if (isCircle)
			path = root + "circle.pf";
		else if (isSphere)
			path = root + "sphere.pf";
		else {
			System.out.println("Error: problem type " + probName + " invalid");
			System.exit(-1);
		}
		return path;
	}

}
