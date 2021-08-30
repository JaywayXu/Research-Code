package momfo.metaheuristics.nsgaII;

import java.io.IOException;
import java.text.DecimalFormat;
import java.util.HashMap;

import momfo.core.*;
import momfo.operators.crossover.CrossoverFactory;
import momfo.operators.mutation.MutationFactory;
import momfo.operators.selection.SelectionFactory;
import momfo.problems.benchmarks.*;
import momfo.qualityIndicator.QualityIndicator;
import momfo.util.JMException;
import momfo.util.Ranking;

public class NSGAII_main {
	public static void main(String args[]) throws IOException, JMException, ClassNotFoundException {
		ProblemSet problemSet; // The problem to solve
		Algorithm algorithm; // The algorithm to use
		Operator crossover; // Crossover operator
		Operator mutation; // Mutation operator
		Operator selection;


		HashMap parameters; // Operator parameters

		problemSet = CIHS.getT1();
		
		problemSet.setUnifiedLowerLimit(-50);
		problemSet.setUnifiedUpperLimit(50);
		
		algorithm = new NSGAII(problemSet);

		
		String pf = "PF/" + problemSet.get(0).getHType() + ".pf";
	//	System.out.println(pf);

		algorithm.setInputParameter("populationSize", 100);
		algorithm.setInputParameter("maxEvaluations", 100 * 1000);

		parameters = new HashMap();
		parameters.put("probability", 0.9);
		parameters.put("distributionIndex", 20.0);
		crossover = CrossoverFactory.getCrossoverOperator("SBXCrossover", parameters);

		// Mutation operator
		parameters = new HashMap();
		parameters.put("probability", 1.0 / problemSet.getMaxDimension());
		parameters.put("distributionIndex", 20.0);
		mutation = MutationFactory.getMutationOperator("PolynomialMutation", parameters);

		// Selection Operator
	    parameters = null ;
	    selection = SelectionFactory.getSelectionOperator("BinaryTournament2", parameters) ;  
	    
	    
		// Add the operators to the algorithm
		algorithm.addOperator("crossover", crossover);
		algorithm.addOperator("mutation", mutation);
		algorithm.addOperator("selection", selection);

		System.out.println("RunID\t" + "IGD for " + problemSet.get(0).getName());
		DecimalFormat form = new DecimalFormat("#.####E0");
		QualityIndicator indicator = new QualityIndicator(problemSet.get(0), pf);
		
		int times = 30;
		double aveIGD = 0;
		for (int i = 1; i <= times; i++) {
			SolutionSet population = algorithm.execute();
			Ranking ranking = new Ranking(population);
			population = ranking.getSubfront(0);
			double igd = indicator.getIGD(population);
			aveIGD += igd;
			System.out.println(i + "\t" + form.format(igd));;
		}
		
		System.out.println();
		System.out.println("Average IGD for " + problemSet.get(0).getName() + ": " + form.format(aveIGD / times));

	}
}
