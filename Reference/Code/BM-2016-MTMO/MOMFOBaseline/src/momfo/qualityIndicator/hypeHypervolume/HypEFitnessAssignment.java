package momfo.qualityIndicator.hypeHypervolume;

import momfo.core.ProblemSet;
import momfo.core.Solution;
import momfo.core.SolutionSet;

public class HypEFitnessAssignment {

	public void setHypEFitness(SolutionSet population, double bound, int k, int nrOfSamples, int taskId) {
		int objs = population.get(0).getProblemSet().getNumberOfObjs(taskId);
		if (objs <= 3)
			setExactHypEFitness(population, bound, k, taskId);
		else
			setEstimatedHypEFitness(population, bound, k, nrOfSamples, taskId);
	}

	void setExactHypEFitness(SolutionSet population, double bound, int k, int taskId) {
		SolutionSet mp = new SolutionSet();
		SolutionSet op = new SolutionSet();
		ProblemSet problemSet = population.get(0).getProblemSet();
		for (int i = 0; i < population.size(); i++) {
			if (population.get(i).getSkillFactor() == taskId)
				mp.add(population.get(i));
			else
				op.add(population.get(i));
		}

		int size = mp.size();
		int objs = problemSet.getNumberOfObjs(taskId);
		int start = problemSet.get(taskId).getStartObjPos();

		double[][] points = new double[size + 1][objs + 1];

		for (int i = 1; i <= size; i++) {
			for (int j = 1; j <= objs; j++)
				points[i][j] = mp.get(i - 1).getObjective(start + j - 1);
		}

		double[] bounds = new double[objs + 1];
		for (int i = 1; i <= objs; i++)
			bounds[i] = bound;

		HypEFitness hy = new HypEFitness();
		double[] result = hy.hypeIndicatorExact(points, bounds, k);

		for (int i = 1; i <= size; i++) {
			mp.get(i - 1).setFitness(result[i]);
		}

		for (int i = 0; i < op.size(); i++)
			op.get(i).setFitness(0);
	}

	void setEstimatedHypEFitness(SolutionSet population, double bound, int k, int nrOfSamples, int taskId) {
		SolutionSet mp = new SolutionSet();
		SolutionSet op = new SolutionSet();
		ProblemSet problemSet = population.get(0).getProblemSet();
		for (int i = 0; i < population.size(); i++) {
			if (population.get(i).getSkillFactor() == taskId)
				mp.add(population.get(i));
			else
				op.add(population.get(i));
		}

		int size = mp.size();
		int objs = problemSet.getNumberOfObjs(taskId);
		int start = problemSet.get(taskId).getStartObjPos();

		double[][] points = new double[size + 1][objs + 1];

		for (int i = 1; i <= size; i++) {
			for (int j = 1; j <= objs; j++)
				points[i][j] = mp.get(i - 1).getObjective(start + j - 1);
		}

		double[] bounds = new double[objs + 1];
		for (int i = 1; i <= objs; i++)
			bounds[i] = bound;

		HypEFitness hy = new HypEFitness();

		double lowerbound = 0;
		double upperbound = bound;

		double[] result = hy.hypeIndicatorSampled(points, lowerbound, upperbound, k, nrOfSamples);

		for (int i = 1; i <= size; i++) {
			mp.get(i - 1).setFitness(result[i]);
		}

		for (int i = 0; i < op.size(); i++)
			op.get(i).setFitness(0);
	}

	
	
	/************************************************/
	public void setHypEFitness(SolutionSet population, Solution reference, int k, int nrOfSamples) {
		if (reference.getNumberOfObjectives() <= 3)
			setExactHypEFitness(population, reference, k);
		else
			setEstimatedHypEFitness(population, reference, k, nrOfSamples);
	}

	void setExactHypEFitness(SolutionSet population, Solution reference, int k) {
		HypEFitness hy = new HypEFitness();

		int objs = reference.getNumberOfObjectives();

		int size = population.size();

		double[][] points = new double[size + 1][objs + 1];

		for (int i = 1; i <= size; i++) {
			for (int j = 1; j <= objs; j++)
				points[i][j] = population.get(i - 1).getObjective(j - 1);
		}

		double[] bounds = new double[objs + 1];
		for (int i = 1; i <= objs; i++)
			bounds[i] = reference.getObjective(i - 1);

		double[] result = hy.hypeIndicatorExact(points, bounds, k);

		for (int i = 1; i <= size; i++) {
			population.get(i - 1).setFitness(result[i]);
		}

	}

	void setEstimatedHypEFitness(SolutionSet population, Solution reference, int k, int nrOfSamples) {

		HypEFitness hy = new HypEFitness();

		int objs = reference.getNumberOfObjectives();

		int size = population.size();

		double[][] points = new double[size][objs];
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < objs; j++)
				points[i][j] = population.get(i).getObjective(j);
		}

		double lowerbound = 0;
		double upperbound = reference.getObjective(0);

		double[] result = hy.hypeIndicatorSampled(points, lowerbound, upperbound, k, nrOfSamples);

		for (int i = 0; i < size; i++) {
			population.get(i).setFitness(result[i]);
		}

	}

}
