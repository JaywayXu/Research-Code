//  PermutationSolutionType.java
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
 * Class representing the solution type of solutions composed of Permutation
 * variables
 */
public class PermutationSolutionType extends SolutionType {

	/**
	 * Constructor
	 * 
	 * @param problem
	 *            Problem to solve
	 */
	public PermutationSolutionType(ProblemSet problemSet) {
		super(problemSet);
	} // PermutationSolution

	/**
	 * Creates the variables of the solution
	 */
	public Variable[] createVariables() {
		int size = problemSet_.getMaxDimension();
		Variable[] variables = new Variable[size];
		int[] permutation = getPermutation(size);

		for (int i = 0; i < size; i++)
			variables[i] = new Int(permutation[i], 0, size - 1);

		return variables;
	} // createVariables

	int[] getPermutation(int size) {
		int vector[] = new int[size];

		java.util.ArrayList<Integer> randomSequence = new java.util.ArrayList<Integer>(size);

		for (int i = 0; i < size; i++)
			randomSequence.add(i);

		java.util.Collections.shuffle(randomSequence);

		for (int j = 0; j < randomSequence.size(); j++)
			vector[j] = randomSequence.get(j);

		return vector;
	} // Constructor
} // PermutationSolutionType
