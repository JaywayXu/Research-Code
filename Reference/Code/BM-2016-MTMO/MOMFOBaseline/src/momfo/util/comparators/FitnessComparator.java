//  FitnessComparator.java
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

package momfo.util.comparators;

import momfo.core.Solution;

import java.util.Comparator;


public class FitnessComparator implements Comparator {


	private boolean ascendingOrder_;


	public FitnessComparator() {
		ascendingOrder_ = true;
	} 

	public FitnessComparator(boolean descendingOrder) {
		if (descendingOrder)
			ascendingOrder_ = false;
		else
			ascendingOrder_ = true;
	} 

	public int compare(Object o1, Object o2) {
		if (o1 == null)
			return 1;
		else if (o2 == null)
			return -1;

		double f1 = ((Solution) o1).getFitness();
		double f2 = ((Solution) o2).getFitness();
		if (ascendingOrder_) {
			if (f1 < f2) {
				return -1;
			} else if (f1 > f2) {
				return 1;
			} else {
				return 0;
			}
		} else {
			if (f1 < f2) {
				return 1;
			} else if (f1 > f2) {
				return -1;
			} else {
				return 0;
			}
		}
	} // compare
} 
