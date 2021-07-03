package momfo.metaheuristics.momfea;

import java.io.FileWriter;
import java.io.IOException;

import momfo.core.Algorithm;
import momfo.core.Operator;
import momfo.core.ProblemSet;
import momfo.core.Solution;
import momfo.core.SolutionSet;
import momfo.core.Variable;
import momfo.qualityIndicator.QualityIndicator;
import momfo.qualityIndicator.fastHypervolume.FastHypervolume;
import momfo.util.Distance;
import momfo.util.JMException;
import momfo.util.PORanking;
import momfo.util.PseudoRandom;
import momfo.util.Ranking;
import momfo.util.comparators.CrowdingComparator;
import momfo.util.comparators.CrowdingDistanceComparator;
import momfo.util.comparators.LocationComparator;
import momfo.util.comparators.ObjectiveComparator;
import momfo.util.comparators.cobjComparator;
import momfo.util.wrapper.XReal;

//Improvement-based

public class MOMFEA extends Algorithm {

	private int populationSize;
	
	private SolutionSet population;
	private SolutionSet offspringPopulation;
	private SolutionSet union;
	
	int evaluations;
	int maxEvaluations;
	
	int[] cfbRecord;
	int[][] cfRecord;
	int number_cx = 6;
	int alpha, maxG, ginterval;
	
	Operator crossover;
	Operator crossover1;
	Operator mutation;
	Operator selection;
	
	double rmp;

	Distance distance = new Distance();
	
	public MOMFEA(ProblemSet problemSet) {
		super(problemSet);
		// TODO Auto-generated constructor stub
	}

	@Override
	public SolutionSet execute() throws JMException, ClassNotFoundException {
		populationSize = ((Integer) getInputParameter("populationSize")).intValue();
		maxEvaluations = ((Integer) getInputParameter("maxEvaluations")).intValue();
		rmp =  ((Double) getInputParameter("rmp")).doubleValue();
		
		maxG =maxEvaluations/populationSize;
		ginterval = 20;
		cfbRecord=new int[maxG];
		cfRecord=new int[maxG][number_cx];
		
		crossover = operators_.get("crossover"); 
		crossover1 = operators_.get("crossover1"); 
		mutation = operators_.get("mutation"); 
		selection = operators_.get("selection");

		evaluations = 0;	
	
		initPopulation();			
		
		String pf0 = "PF/" + problemSet_.get(0).getHType() + ".pf";
		String pf1 = "PF/" + problemSet_.get(1).getHType() + ".pf";
		
	    
		
		while (evaluations < maxEvaluations) {					
			
			createOffspringPopulation();
			getNextPopulation();
		}				    
	
		return population;
	}
	
	
	void initPopulation() throws JMException, ClassNotFoundException {
		population = new SolutionSet(populationSize);
		for (int i = 0; i < populationSize; i++) {
			Solution newSolution = new Solution(problemSet_);
			int id = PseudoRandom.randInt(0, problemSet_.size() - 1);
			problemSet_.get(id).evaluate(newSolution);
			problemSet_.get(id).evaluateConstraints(newSolution);
			evaluations++;
			
			newSolution.setSkillFactor(id);
			population.add(newSolution);
			
		} // for
		assignFitness(population);
	} // initPopulation
	
	
	
	void getNextPopulation() {
		
		double[] impNum=new double[number_cx];
		
		union = population.union(offspringPopulation);
		assignFitness(union);
		union.sort(new LocationComparator());
		
		int cfc,pfc;
		for (int i = 0; i < union.size(); i++){
			if(union.get(i).getParent()!=null){
				cfc=union.get(i).getLocation();
				pfc=union.get(i).getParent().getLocation();
				if((pfc-cfc)*1.0/(pfc+1)>impNum[union.get(i).getCxFactor()])
					impNum[union.get(i).getCxFactor()]=(pfc-cfc)*1.0/(pfc+1); 
			}
		}	
		
		double maximp=0;
		int maxInd=0;
		int maxPrCount=0;
		boolean impTest=false;

		int[] prCFb_count=new int[number_cx];
		
		for(int i=0;i<number_cx;i++) {
			if(impNum[i]>0) {
				impTest=true;
				break;
			}			
		}
				
		if(impTest) {
			for(int i=0;i<number_cx;i++){
				if(impNum[i]>maximp){
					maximp=impNum[i];
					maxInd=i;
				}
			}
		}
		else {
			if(evaluations/populationSize<=ginterval) {
				for(int i=1;i<=evaluations/populationSize-1;i++)
					prCFb_count[cfbRecord[i]]+=1;
			}
			else {
				for(int i=evaluations/populationSize-ginterval;i<=evaluations/populationSize-1;i++)
					prCFb_count[cfbRecord[i]]+=1;
			}
			for(int i=0;i<6;i++){
				if(prCFb_count[i]>maxPrCount) {
					maxPrCount=prCFb_count[i];
					maxInd=i;
				}
			}									
		}
		
		cfbRecord[evaluations/populationSize-1]=maxInd;	
		
		
		for (int i = 0; i < union.size(); i++){
			if(union.get(i).getParent()!=null){
				cfc=union.get(i).getLocation();
				pfc=union.get(i).getParent().getLocation();
				if((pfc-cfc)*1.0/(pfc+1)<impNum[union.get(i).getCxFactor()]) 
					union.get(i).setCxFactor(maxInd);
			}
			else{
					if(PseudoRandom.randDouble()<0.5)
						union.get(i).setCxFactor(maxInd);
					else
						union.get(i).setCxFactor(PseudoRandom.randInt(0, 5));
			}
		}			
		
		population.clear();
		
		for (int i = 0; i < populationSize; i++){
			population.add(union.get(i));
			population.get(i).setParent(null);
            population.get(i).setIsTran(0);
		}
	
		
	}
	
	void createOffspringPopulation() throws JMException {
		offspringPopulation = new SolutionSet(populationSize);
		Solution[] parents = new Solution[2];	
		
		for (int i = 0; i < (populationSize / 2); i++) {

			parents[0] = (Solution) selection.execute(population);
			parents[1] = (Solution) selection.execute(population);
			
			int[] sfs = new int[2];
			sfs[0] = parents[0].getSkillFactor();
			sfs[1] = parents[1].getSkillFactor();
			double rand = PseudoRandom.randDouble();

			Solution[] offSpring;
			if (sfs[0] == sfs[1] || rand < rmp) {
				if(sfs[0] == sfs[1]){
					offSpring = (Solution[]) crossover.execute(parents,problemSet_,0);	
					offSpring[0].setCxFactor(parents[0].getCxFactor());
					offSpring[1].setCxFactor(parents[1].getCxFactor());
					offSpring[0].setIsTran(0);
					offSpring[1].setIsTran(0);
				}
				else{
					if(PseudoRandom.randDouble()<0.5)
						alpha=parents[0].getCxFactor();
					else
						alpha=parents[1].getCxFactor();
					
					cfRecord[evaluations/populationSize][alpha]+=1;
					
					offSpring = (Solution[]) crossover1.execute(parents,problemSet_,alpha);	
					
					offSpring[0].setCxFactor(alpha);
					offSpring[1].setCxFactor(alpha);
					
					offSpring[0].setIsTran(1);
					offSpring[1].setIsTran(1);	
					
				}
				mutation.execute(offSpring[0]);
				mutation.execute(offSpring[1]);
				
				int p0 = PseudoRandom.randInt(0, 1);
				int p1 = PseudoRandom.randInt(0, 1);

				offSpring[0].setSkillFactor(sfs[p0]);
				offSpring[1].setSkillFactor(sfs[p1]);
				if(offSpring[0].getIsTran()==1)
					offSpring[0].setParent(parents[p0]);
				if(offSpring[1].getIsTran()==1)
					offSpring[1].setParent(parents[p1]);				
				
				resetObjectives(offSpring[0]);
				resetObjectives(offSpring[1]);
				problemSet_.get(sfs[p0]).evaluate(offSpring[0]);
				problemSet_.get(sfs[p1]).evaluate(offSpring[1]);
				problemSet_.get(sfs[p0]).evaluateConstraints(offSpring[0]);
				problemSet_.get(sfs[p1]).evaluateConstraints(offSpring[1]);
				evaluations += 2;

			} else {
				offSpring = new Solution[2];
				offSpring[0] = new Solution(parents[0]);
				offSpring[1] = new Solution(parents[1]);
	
				mutation.execute(offSpring[0]);
				mutation.execute(offSpring[1]);

				offSpring[0].setSkillFactor(sfs[0]);
				offSpring[1].setSkillFactor(sfs[1]);							
	
				offSpring[0].setIsTran(0);
				offSpring[1].setIsTran(0);	
				
				offSpring[0].setCxFactor(parents[0].getCxFactor());
				offSpring[1].setCxFactor(parents[1].getCxFactor());				
				
				problemSet_.get(sfs[0]).evaluate(offSpring[0]);
				problemSet_.get(sfs[1]).evaluate(offSpring[1]);
				problemSet_.get(sfs[0]).evaluateConstraints(offSpring[0]);
				problemSet_.get(sfs[1]).evaluateConstraints(offSpring[1]);
				
				evaluations += 2;		
			}

			offspringPopulation.add(offSpring[0]);
			offspringPopulation.add(offSpring[1]);

		} // for
		       	
				
	}
	
	void assignFitness(SolutionSet pop) {
		for (int i = 0; i < pop.size(); i++)
			pop.get(i).setLocation(Integer.MAX_VALUE);
		for (int i = 0; i < problemSet_.size(); i++)
			rankSolutionOnTask(pop, i);
	}
	
	void rankSolutionOnTask(SolutionSet pop, int taskId) {
		int start = problemSet_.get(taskId).getStartObjPos();
		int end = problemSet_.get(taskId).getEndObjPos();
		
		boolean selec[] = new boolean[problemSet_.getTotalNumberOfObjs()];
		
		for (int i = 0; i < selec.length; i++) {
			if (i < start || i > end)
				selec[i] = false;
			else
				selec[i] = true;
		}
		
		PORanking pr = new PORanking(pop, selec);	
		int loc = 0;
		for (int i = 0; i < pr.getNumberOfSubfronts(); i++) {
			SolutionSet front = pr.getSubfront(i);
			distance.crowdingDistanceAssignment(front, problemSet_.getTotalNumberOfObjs(), selec);
			front.sort(new CrowdingComparator());
			for (int j = 0; j < front.size(); j++) {
				if (loc < front.get(j).getLocation())
					front.get(j).setLocation(loc);
				loc++;
			}
		}
	}

	void resetObjectives(Solution sol) {
		for (int i = 0; i < sol.getNumberOfObjectives(); i++)
			sol.setObjective(i, Double.POSITIVE_INFINITY);
	}
	
}
