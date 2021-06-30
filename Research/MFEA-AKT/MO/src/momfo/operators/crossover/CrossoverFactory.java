//  CrossoverFactory.java
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

import java.util.HashMap;

import momfo.util.Configuration;
import momfo.util.JMException;

/**
 * Class implementing a factory for crossover operators.
 */
public class CrossoverFactory {

	/**
	 * Gets a crossover operator through its name.
	 * 
	 * @param name
	 *            Name of the operator
	 * @return The operator
	 */
	public static Crossover getCrossoverOperator(String name, HashMap parameters) throws JMException {
		if (name.equalsIgnoreCase("SBXCrossover"))
			return new SBXCrossover(parameters);
		else if (name.equalsIgnoreCase("PMXCrossover"))
			return new PMXCrossover(parameters);
		else if (name.equalsIgnoreCase("TwoPointsCrossover"))
			return new TwoPointsCrossover(parameters);
		else if (name.equalsIgnoreCase("DifferentialEvolutionCrossover"))
			return new DifferentialEvolutionCrossover(parameters);
		else if (name.equalsIgnoreCase("SpCrossover"))
			return new SpCrossover(parameters);		
		else if (name.equalsIgnoreCase("TpCrossover"))
			return new TpCrossover(parameters);	
		else if (name.equalsIgnoreCase("UfCrossover"))
			return new UfCrossover(parameters);	
		else if (name.equalsIgnoreCase("AriCrossover"))
			return new AriCrossover(parameters);	
		else if (name.equalsIgnoreCase("GeoCrossover"))
			return new GeoCrossover(parameters);			
		else if (name.equalsIgnoreCase("BLX03Crossover"))
			return new BLX03Crossover(parameters);		
		else if (name.equalsIgnoreCase("NewCrossover"))
			return new NewCrossover(parameters);		
		else {
			Configuration.logger_
					.severe("CrossoverFactory.getCrossoverOperator. " + "Operator '" + name + "' not found ");
			throw new JMException("Exception in " + name + ".getCrossoverOperator()");
		} // else
	} // getCrossoverOperator
} // CrossoverFactory
