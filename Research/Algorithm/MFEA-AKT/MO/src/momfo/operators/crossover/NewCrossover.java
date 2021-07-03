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

import momfo.core.Operator;
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
public class NewCrossover extends Crossover {
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
	
	private String name = "Adaptive";	
	public NewCrossover(HashMap<String, Object> parameters) {
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
	public Solution[] doCrossover(double probability, Solution[] parents,ProblemSet problemSet, int alpha) throws JMException {

		Solution[] offSpring = new Solution[2];
		Operator crossover; // Crossover operator		
		HashMap parameters; // Operator parameters	
		
		parameters = new HashMap();
		parameters.put("probability", 0.9);
		parameters.put("distributionIndex", 20.0);		
		
		switch(alpha){
			case 0:
				crossover = CrossoverFactory.getCrossoverOperator("BLX03Crossover", parameters); 
				break;
			case 1:
				crossover = CrossoverFactory.getCrossoverOperator("UfCrossover", parameters);
				break;				
			case 2:
				crossover = CrossoverFactory.getCrossoverOperator("AriCrossover", parameters);
				break;	
			case 3:
				crossover = CrossoverFactory.getCrossoverOperator("GeoCrossover", parameters);
				break;				
			case 4:
				crossover = CrossoverFactory.getCrossoverOperator("TpCrossover", parameters);
				break;					
			case 5:
				crossover = CrossoverFactory.getCrossoverOperator("SBXCrossover", parameters);
				break;	
			default:
				crossover = CrossoverFactory.getCrossoverOperator("SBXCrossover", parameters);					
		}		
		
		offSpring = (Solution[]) crossover.execute(parents,problemSet,0);		

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
		offSpring = doCrossover(crossoverProbability_, parents, problemSet,alpha);

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
