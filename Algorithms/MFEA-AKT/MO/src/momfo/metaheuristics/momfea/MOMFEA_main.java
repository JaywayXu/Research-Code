package momfo.metaheuristics.momfea;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.HashMap;

import momfo.util.comparators.LocationComparator;
import momfo.core.Algorithm;
import momfo.core.Operator;
import momfo.core.ProblemSet;
import momfo.core.Solution;
import momfo.core.SolutionSet;


import momfo.operators.crossover.CrossoverFactory;
import momfo.operators.mutation.MutationFactory;
import momfo.operators.selection.SelectionFactory;
import momfo.problems.benchmarks.*;
import momfo.qualityIndicator.QualityIndicator;
import momfo.util.JMException;
import momfo.util.Ranking;

public class MOMFEA_main {
	public static void main(String args[]) throws IOException, JMException, ClassNotFoundException {
		ProblemSet problemSet; // The problem to solve
		Algorithm algorithm; // The algorithm to use
		
		Operator crossover; // Crossover operator
		Operator crossover1;
		Operator mutation; // Mutation operator
		Operator selection;
		
		HashMap parameters; // Operator parameters	
					
	    int totalPro=9,totalcx=8;
	    int pCase,cxNum;	    
	    
	    for(cxNum=7;cxNum<totalcx;cxNum++){	    
			for(pCase=0;pCase<totalPro;pCase++){	
				switch(pCase){
				case 0:
				    problemSet = CIHS.getProblem();
					break;
				case 1:
					problemSet = CIMS.getProblem();    
					break;
				case 2:
				    problemSet = CILS.getProblem();  
					break;				
				case 3:
				    problemSet = PIHS.getProblem();  
					break;	
				case 4:
				    problemSet = PIMS.getProblem();  
					break;					
				case 5:
					problemSet = PILS.getProblem();    
					break;	
				case 6:
				    problemSet = NIHS.getProblem();    
					break;		
				case 7: 
				    problemSet = NIMS.getProblem(); 
					break;				
				case 8:
				    problemSet = NILS.getProblem();  
					break;						
				default:
					problemSet = CIHS.getProblem();			
				}
				
				String pf1 = "PF/" + problemSet.get(0).getHType() + ".pf";
				String pf2 = "PF/" + problemSet.get(1).getHType() + ".pf";		
				algorithm = new MOMFEA(problemSet);	
				
				algorithm.setInputParameter("populationSize",200);
				algorithm.setInputParameter("maxEvaluations",200 * 1000);
				algorithm.setInputParameter("rmp", 0.9);
		
				parameters = new HashMap();
				parameters.put("probability", 0.9);
				parameters.put("distributionIndex", 20.0);
				
				crossover = CrossoverFactory.getCrossoverOperator("SBXCrossover", parameters);		
				
				switch(cxNum){
				case 0:
					crossover1 = CrossoverFactory.getCrossoverOperator("SpCrossover", parameters);
					break;
				case 1:
					crossover1 = CrossoverFactory.getCrossoverOperator("TpCrossover", parameters); 
					break;
				case 2:
					crossover1 = CrossoverFactory.getCrossoverOperator("UfCrossover", parameters);
					break;				
				case 3:
					crossover1 = CrossoverFactory.getCrossoverOperator("AriCrossover", parameters);
					break;	
				case 4:
					crossover1 = CrossoverFactory.getCrossoverOperator("GeoCrossover", parameters);
					break;						
				case 5:
					crossover1 = CrossoverFactory.getCrossoverOperator("BLX03Crossover", parameters);
					break;					
				case 6:
					crossover1 = CrossoverFactory.getCrossoverOperator("SBXCrossover", parameters);
					break;	
				case 7:
					crossover1 = CrossoverFactory.getCrossoverOperator("NewCrossover", parameters);
					break;		
				default:
					crossover1 = CrossoverFactory.getCrossoverOperator("SBXCrossover", parameters);		
				}				
				
				
				// Mutation operator
				parameters = new HashMap();
				parameters.put("probability", 1.0 / problemSet.getMaxDimension());
				parameters.put("distributionIndex", 20.0);
				mutation = MutationFactory.getMutationOperator("PolynomialMutation", parameters);
		
				// Selection Operator
			    parameters = new HashMap() ; 
			    parameters.put("comparator", new LocationComparator()) ;
			    selection = SelectionFactory.getSelectionOperator("BinaryTournament",
						parameters);
				
				
				// Add the operators to the algorithm
			    algorithm.addOperator("crossover1", crossover1);
				algorithm.addOperator("crossover", crossover);
				algorithm.addOperator("mutation", mutation);
				algorithm.addOperator("selection", selection);
																
				String name1 = problemSet.get(0).getName();
				String name2 = problemSet.get(1).getName();
				DecimalFormat form = new DecimalFormat("#.####E0");
				
				System.out.println("RunID\t" + "IGD for " + name1 + "\t" + "IGD for " + name2);
				System.out.println(crossover1.getName());
				int times = 20;

				//===========================================================================================			
				
								
				double ave1 = 0;
				double ave2 = 0;
				
				for (int t = 1; t <= times; t++) {	
					SolutionSet population = algorithm.execute();
					
					SolutionSet[] resPopulation = new SolutionSet[problemSet.size()];
					for (int i = 0; i < problemSet.size(); i++)
						resPopulation[i] = new SolutionSet();
		
					for (int i = 0; i < population.size(); i++) {
						Solution sol = population.get(i);
		
						int pid = sol.getSkillFactor();
		
						int start = problemSet.get(pid).getStartObjPos();
						int end = problemSet.get(pid).getEndObjPos();
		
						Solution newSolution = new Solution(end - start + 1);
		
						for (int k = start; k <= end; k++)
							newSolution.setObjective(k - start, sol.getObjective(k));
		
						resPopulation[pid].add(newSolution);
					}
					
	
					
					QualityIndicator indicator1 = new QualityIndicator(problemSet.get(0), pf1);
					QualityIndicator indicator2 = new QualityIndicator(problemSet.get(1), pf2);
	
					double igd1 =  indicator1.getIGD(resPopulation[0]);
					double igd2 = indicator2.getIGD(resPopulation[1]);
					
					System.out.println(t + "\t" + form.format(igd1) + "\t" + form.format(igd2));
		
					ave1 += igd1;
					ave2 += igd2;
				}
				
				System.out.println();
				System.out.println("Average IGD for " + name1 + ": " + form.format(ave1 / times));
				System.out.println("Average IGD for " + name2 + ": " + form.format(ave2 / times));
				
						
			}
	    }
		
	}
}
