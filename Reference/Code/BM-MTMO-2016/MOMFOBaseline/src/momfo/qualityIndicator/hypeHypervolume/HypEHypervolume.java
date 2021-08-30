package momfo.qualityIndicator.hypeHypervolume;

import momfo.core.Solution;
import momfo.core.SolutionSet;
import momfo.qualityIndicator.fastHypervolume.wfg.Front;
import momfo.qualityIndicator.fastHypervolume.wfg.WFGHV;
import momfo.util.comparators.ObjectiveComparator;

public class HypEHypervolume {

	Solution referencePoint_;
	double offset_ = 20.0;

	int nrOfSamples_ = 10000;

	public HypEHypervolume() {

	}

	public HypEHypervolume(double offset, int nrOfSamples) {
		referencePoint_ = null;
		offset_ = offset;
		nrOfSamples_ = nrOfSamples;
	}

	public double computeHypervolume(SolutionSet solutionSet, Solution referencePoint) {
		HypEFitness hy = new HypEFitness();

		int objs = referencePoint.getNumberOfObjectives();

		int size = solutionSet.size();

		double[][] points = new double[size + 1][objs + 1];
		for (int i = 1; i <= size; i++) {
			for (int j = 1; j <= objs; j++)
				points[i][j] = solutionSet.get(i - 1).getObjective(j - 1);
		}

		double[] bounds = new double[objs + 1];
		for (int i = 1; i <= objs; i++)
			bounds[i] = referencePoint.getObjective(i - 1);

		double[] result = hy.hypeIndicatorExact(points, bounds, size);

		double sum = 0;

		for (int i = 1; i <= size; i++)
			sum += result[i];

		return sum;
	}

	public double estimateHypervolume(SolutionSet solutionSet, Solution referencePoint, int nrOfSamples) {
		HypEFitness hy = new HypEFitness();

		int objs = referencePoint.getNumberOfObjectives();

		int size = solutionSet.size();

		double[][] points = new double[size][objs];
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < objs; j++)
				points[i][j] = solutionSet.get(i).getObjective(j);
		}

		double lowerbound = 0;
		double upperbound = referencePoint.getObjective(0);

		double[] result = hy.hypeIndicatorSampled(points, lowerbound, upperbound, size, nrOfSamples);

		double sum = 0;

		for (int i = 0; i < size; i++)
			sum += result[i];

		return sum;

	}

	// used by SMSEMOA
	public void getHVContributions(SolutionSet solutionSet) {
		double[] contributions = new double[solutionSet.size()];
		double solutionSetHV = 0;

		int objs = solutionSet.get(0).getNumberOfObjectives();

		solutionSetHV = getHypervolume(solutionSet);

		for (int i = 0; i < solutionSet.size(); i++) {
			Solution currentPoint = solutionSet.get(i);
			solutionSet.remove(i);
			double hv;
			if (objs <= 3) {
				hv = computeHypervolume(solutionSet, referencePoint_);
			} else {
				hv = estimateHypervolume(solutionSet, referencePoint_, nrOfSamples_);
			}

			contributions[i] = solutionSetHV - hv;
			solutionSet.add(i, currentPoint);
		}

		for (int i = 0; i < solutionSet.size(); i++) {
			solutionSet.get(i).setCrowdingDistance(contributions[i]);
		}
	}

	// for SMS-EMOA
	public double getHypervolume(SolutionSet solutionSet) {
		double hv;
		if (solutionSet.size() == 0)
			hv = 0.0;
		else {
			int objs = solutionSet.get(0).getNumberOfObjectives();
			referencePoint_ = new Solution(objs);
			updateReferencePoint(solutionSet);

			if (objs <= 3) {
				hv = computeHypervolume(solutionSet, referencePoint_);
			} else {
				hv = estimateHypervolume(solutionSet, referencePoint_, nrOfSamples_);
			}

		}

		return hv;
	}

	void updateReferencePoint(SolutionSet solutionSet) {
		int numberOfObjectives_ = solutionSet.get(0).getNumberOfObjectives();
		double[] maxObjectives = new double[numberOfObjectives_];
		for (int i = 0; i < numberOfObjectives_; i++)
			maxObjectives[i] = 0;

		for (int i = 0; i < solutionSet.size(); i++)
			for (int j = 0; j < numberOfObjectives_; j++)
				if (maxObjectives[j] < solutionSet.get(i).getObjective(j))
					maxObjectives[j] = solutionSet.get(i).getObjective(j);

		for (int i = 0; i < referencePoint_.getNumberOfObjectives(); i++) {
			referencePoint_.setObjective(i, maxObjectives[i] + offset_);
		}
	}
}
