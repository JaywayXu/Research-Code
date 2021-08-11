//  IntSolutionType.java
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

package momfo.encodings.solutionType;

import momfo.core.ProblemSet;
import momfo.core.SolutionType;
import momfo.core.Variable;
import momfo.encodings.variable.Int;

/**
 * Class representing the solution type of solutions composed of Int variables
 */
public class IntSolutionType extends SolutionType {

	/**
	 * Constructor
	 * 
	 * @param problem
	 *            Problem to solve
	 */
	public IntSolutionType(ProblemSet problemSet) {
		super(problemSet);
	} // Constructor

	/**
	 * Creates the variables of the solution
	 */
	public Variable[] createVariables() {
		Variable[] variables = new Variable[problemSet_.getMaxDimension()];

		for (int var = 0; var < problemSet_.getMaxDimension(); var++)
			variables[var] = new Int((int) problemSet_.getUnifiedLowerLimit(),
					(int) problemSet_.getUnifiedUpperLimit());

		return variables;
	} // createVariables
} // IntSolutionType
