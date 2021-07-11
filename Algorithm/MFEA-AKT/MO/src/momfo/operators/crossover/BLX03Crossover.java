//  SBXCrossover.java
//
//  Author:
//       Antonio J. Nebro <antonio@lcc.uma.es>
//       Juan J. Durillo <durillo@lcc.uma.es>
//
//  Copyright (c) 2011 Antonio J. Nebro, Juan J. Durillo
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
// 
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

package momfo.operators.crossover;

import momfo.core.Problem;
import momfo.core.ProblemSet;
import momfo.core.Solution;
import momfo.encodings.solutionType.RealSolutionType;
import momfo.util.Configuration;
import momfo.util.JMException;
import momfo.util.PseudoRandom;
import momfo.util.wrapper.XReal;

import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Random;

import jmetal.operators.selection.RandomSelection;

/**
 * This class allows to apply a SBX crossover operator using two parent
 * solutions.
 */
public class BLX03Crossover extends Crossover {
	/**
	 * EPS defines the minimum difference allowed between real values
	 */
	private static final double EPS = 1.0e-14;

	private static final double ETA_C_DEFAULT_ = 20.0;
	private Double crossoverProbability_ = 0.9;
	private double distributionIndex_ = ETA_C_DEFAULT_;

	/**
	 * Valid solution types to apply this operator
	 */
	private static final List VALID_TYPES = Arrays.asList(RealSolutionType.class);

	/**
	 * Constructor Create a new SBX crossover operator whit a default index
	 * given by <code>DEFAULT_INDEX_CROSSOVER</code>
	 */
	public BLX03Crossover(HashMap<String, Object> parameters) {
		super(parameters);

		if (parameters.get("probability") != null)
			crossoverProbability_ = (Double) parameters.get("probability");
		if (parameters.get("distributionIndex") != null)
			distributionIndex_ = (Double) parameters.get("distributionIndex");
	} // SBXCrossover

	/**
	 * Perform the crossover operation.
	 * 
	 * @param probability
	 *            Crossover probability
	 * @param parent1
	 *            The first parent
	 * @param parent2
	 *            The second parent
	 * @return An array containing the two offsprings
	 */
	protected String name="blx";
	
	public Solution[] doCrossover(double probability, Solution parent1, Solution parent2,ProblemSet problemSet) throws JMException {

		Solution[] offSpring = new Solution[2];

		offSpring[0] = new Solution(parent1);
		offSpring[1] = new Solution(parent2);

		int i;
		double rand;
		
		XReal x1 = new XReal(parent1);
		XReal x2 = new XReal(parent2);
		XReal offs1 = new XReal(offSpring[0]);
		XReal offs2 = new XReal(offSpring[1]);

		int dim=problemSet.getMaxDimension();
/*		int dem1=problemSet.get(parent1.getSkillFactor()).getNumberOfVariables();
		int dem2=problemSet.get(parent2.getSkillFactor()).getNumberOfVariables();*/
		
		
		if (PseudoRandom.randDouble() <= probability) {
	
			double cmin,cmax,I;
			double insertValue;
			double a=0.3;
			
			for(i=0;i<dim;i++){
				double yL = x1.getLowerBound(i);
				double yu = x1.getUpperBound(i);				
				
				if(x1.getValue(i)<x2.getValue(i)){
	                cmin=x1.getValue(i);
	                cmax=x2.getValue(i);										
				}
				else{
	                cmin=x2.getValue(i);
	                cmax=x1.getValue(i);											
				}
				I=cmax-cmin;
				

				rand=PseudoRandom.randDouble();
				insertValue=(cmin-I*a)+(I+2*I*a)*rand;
				if (insertValue < yL)
					insertValue = yL;

				if (insertValue > yu)
					insertValue = yu;				
				offs1.setValue(i,insertValue);
				
				rand=PseudoRandom.randDouble();
				insertValue=(cmin-I*a)+(I+2*I*a)*rand;
				if (insertValue < yL)
					insertValue = yL;

				if (insertValue > yu)
					insertValue = yu;					
				offs2.setValue(i,insertValue);
			}
				
			
		} // if

		return offSpring;
	} // doCrossover

	/**
	 * Executes the operation
	 * 
	 * @param object
	 *            An object containing an array of two parents
	 * @return An object containing the offSprings
	 */
	public Object execute(Object object, ProblemSet problemSet, int alpha) throws JMException {
		Solution[] parents = (Solution[]) object;

		if (parents.length != 2) {
			Configuration.logger_.severe("SBXCrossover.execute: operator needs two " + "parents");
			Class cls = java.lang.String.class;
			String name = cls.getName();
			throw new JMException("Exception in " + name + ".execute()");
		} // if

		if (!(VALID_TYPES.contains(parents[0].getType().getClass())
				&& VALID_TYPES.contains(parents[1].getType().getClass()))) {
			Configuration.logger_.severe("SBXCrossover.execute: the solutions " + "type " + parents[0].getType()
					+ " is not allowed with this operator");

			Class cls = java.lang.String.class;
			String name = cls.getName();
			throw new JMException("Exception in " + name + ".execute()");
		} // if

		Solution[] offSpring;
		offSpring = doCrossover(crossoverProbability_, parents[0], parents[1], problemSet);

		// for (int i = 0; i < offSpring.length; i++)
		// {
		// offSpring[i].setCrowdingDistance(0.0);
		// offSpring[i].setRank(0);
		// }
		return offSpring;
	} // execute

	@Override
	public Object execute(Object object) throws JMException {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Object execute(Object object, ProblemSet problemSet) throws JMException {
		// TODO Auto-generated method stub
		return null;
	}
	
	@Override	
	public String getName() {
		return name;
	}
	@Override
	public void setName(String name) {
		this.name = name;
	}	
	
} // SBXCrossover
