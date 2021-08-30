package momfo.core;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;


import momfo.core.Problem;
import momfo.core.SolutionType;
import momfo.encodings.solutionType.PermutationSolutionType;
import momfo.encodings.solutionType.RealSolutionType;
import momfo.util.Configuration;

public class ProblemSet {
	protected final List<Problem> problemsList_;

	protected List<Integer> accObjsList_;

	private int capacity_ = Integer.MAX_VALUE;

	private int maxDim_;

	private double unifiedLowerLimit_;

	private double unifiedUpperLimit_;

	private SolutionType solutionType_;

	public ProblemSet() {
		problemsList_ = new ArrayList<Problem>();
		accObjsList_ = new ArrayList<Integer>();
		maxDim_ = 0;

		// solutionType_ = null;

		solutionType_ = new RealSolutionType(this); // default: real

		unifiedLowerLimit_ = 0;
		unifiedUpperLimit_ = 1;
	} // SolutionSet

	public ProblemSet(int maximumSize) {
		problemsList_ = new ArrayList<Problem>();
		accObjsList_ = new ArrayList<Integer>();

		capacity_ = maximumSize;
		maxDim_ = 0;

		solutionType_ = new RealSolutionType(this); // default: real

		// solutionType_ = null;
		unifiedLowerLimit_ = 0;
		unifiedUpperLimit_ = 1;
	} // SolutionSet

	public ProblemSet(int maximumSize, double low, double up) {
		problemsList_ = new ArrayList<Problem>();
		accObjsList_ = new ArrayList<Integer>();

		capacity_ = maximumSize;
		maxDim_ = 0;

		solutionType_ = new RealSolutionType(this); // default: real

		// solutionType_ = null;
		unifiedLowerLimit_ = low;
		unifiedUpperLimit_ = up;
	}

	public ProblemSet(String solutionType) {
		problemsList_ = new ArrayList<Problem>();
		accObjsList_ = new ArrayList<Integer>();

		maxDim_ = 0;

		unifiedLowerLimit_ = 0;
		unifiedUpperLimit_ = 1;

		if (solutionType.compareTo("Real") == 0)
			solutionType_ = new RealSolutionType(this);
		else {
			System.out.println("solution type " + solutionType + " invalid");
			System.exit(-1);
		}

	} // SolutionSet

	public ProblemSet(int maximumSize, String solutionType) {
		problemsList_ = new ArrayList<Problem>();
		accObjsList_ = new ArrayList<Integer>();

		capacity_ = maximumSize;
		maxDim_ = 0;

		unifiedLowerLimit_ = 0;
		unifiedUpperLimit_ = 1;

		if (solutionType.compareTo("Real") == 0)
			solutionType_ = new RealSolutionType(this);
		else if (solutionType.compareTo("Permutation") == 0)
			solutionType_ = new PermutationSolutionType(this);
		else {
			System.out.println("solution type " + solutionType + " invalid");
			System.exit(-1);
		}

	} // SolutionSet

	public boolean add(Problem problem) {
		if (problemsList_.size() == capacity_) {
			Configuration.logger_.severe("The problem set is full");
			Configuration.logger_.severe("Capacity is : " + capacity_);
			Configuration.logger_.severe("\t Size is: " + this.size());
			return false;
		} // if

		problem.setProblemIndex(problemsList_.size());

		problemsList_.add(problem);

		if (accObjsList_.size() == 0) {
			accObjsList_.add(problem.getNumberOfObjectives());
			
			problem.setStartObjPos(0);
			problem.setEndObjPos(problem.getNumberOfObjectives() - 1);
		}
		
		else {
			int curObjs = accObjsList_.get(accObjsList_.size() - 1);
			int nobjs = curObjs  + problem.getNumberOfObjectives();
			accObjsList_.add(nobjs);
			
			problem.setStartObjPos(curObjs);
			problem.setEndObjPos(nobjs - 1);
		}

		if (problem.getNumberOfVariables() > maxDim_)
			maxDim_ = problem.getNumberOfVariables();

		return true;
	} // add

	public Problem get(int i) {
		if (i >= problemsList_.size()) {
			throw new IndexOutOfBoundsException("Index out of Bound " + i);
		}
		return problemsList_.get(i);
	} // get

	public int size() {
		return problemsList_.size();
	} // size

	public int getMaxSize() {
		return capacity_;
	} // getMaxSize

	public int getMaxDimension() {
		return maxDim_;
	}

	public void setUnifiedLowerLimit(double low) {
		unifiedLowerLimit_ = low;
	}

	public void setUnifiedUpperLimit(double up) {
		unifiedUpperLimit_ = up;
	}

	public double getUnifiedLowerLimit() {
		return unifiedLowerLimit_;
	}

	public double getUnifiedUpperLimit() {
		return unifiedUpperLimit_;
	}

	public SolutionType getSolutionType() {
		return solutionType_;
	}

	public void setSolutionType(SolutionType type) {
		solutionType_ = type;
	}

	public int getTotalNumberOfObjs() {
		return accObjsList_.get(accObjsList_.size() - 1);
	}

	public int getNumberOfObjs(int id) {
		if (id == 0)
			return accObjsList_.get(id);
		else 
			return accObjsList_.get(id) - accObjsList_.get(id - 1);
	}
	
	
	public int[] getRangeOfObjs(int id) {
		int[] range = new int[2];

		if (id == 0)
			range[0] = 0;
		else
			range[0] = accObjsList_.get(id - 1);

		range[1] = accObjsList_.get(id) - 1;
		return range;
	}
	
}
