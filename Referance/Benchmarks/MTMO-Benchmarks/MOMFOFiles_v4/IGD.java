
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class IGD {
	
	static final double pow_ = 2.0; // pow. This is the pow used for the distances
	
	
	//Example: how to compute the IGD for a set of nondominated objective vectors saved in the file
	public static void main(String args[]) {
		System.out.println("The first parmater: the file path of the true Pareto front");
		System.out.println("The second parmater: the file path of the nondominated objective vectors obtained");
		System.out.println("The third parmater: the number of objectives");
		System.out.println("********************************************************************************************");
		System.out.println();
		if (args.length < 3) {
			System.out.println("Error: The number of parameters should be 3");
			return;
		}
		
		double[][] trueParetoFront = readFront(args[0]);
		double[][] front = readFront(args[1]);
		int numberOfObjectives = Integer.parseInt(args[2]);
		
		double igd = invertedGenerationalDistance(front, trueParetoFront, numberOfObjectives);
		System.out.println("IGD: " + igd);
	}
	
	
	
	/**
	 * This method reads a Pareto Front for a file.
	 * 
	 * @param path
	 *            The path to the file that contains the pareto front
	 * @return double [][] whit the pareto front
	 **/
	public static double invertedGenerationalDistance(double[][] front, double[][] trueParetoFront, int numberOfObjectives) {

		/**
		 * Stores the maximum values of true pareto front.
		 */
		double[] maximumValue;

		/**
		 * Stores the minimum values of the true pareto front.
		 */
		double[] minimumValue;

		/**
		 * Stores the normalized front.
		 */
		double[][] normalizedFront;

		/**
		 * Stores the normalized true Pareto front.
		 */
		double[][] normalizedParetoFront;

		// STEP 1. Obtain the maximum and minimum values of the Pareto front
		maximumValue = getMaximumValues(trueParetoFront, numberOfObjectives);
		minimumValue = getMinimumValues(trueParetoFront, numberOfObjectives);

		// STEP 2. Get the normalized front and true Pareto fronts
		normalizedFront = getNormalizedFront(front, maximumValue, minimumValue);
		normalizedParetoFront = getNormalizedFront(trueParetoFront, maximumValue, minimumValue);

		// STEP 3. Sum the distances between each point of the true Pareto front
		// and
		// the nearest point in the true Pareto front
		double sum = 0.0;
		for (double[] aNormalizedParetoFront : normalizedParetoFront)
			sum += Math.pow(distanceToClosedPoint(aNormalizedParetoFront, normalizedFront), pow_);

		// STEP 4. Obtain the sqrt of the sum
		sum = Math.pow(sum, 1.0 / pow_);

		// STEP 5. Divide the sum by the maximum number of points of the front
		double generationalDistance = sum / normalizedParetoFront.length;

		return generationalDistance;
	} // generationalDistance
	
	
	
	public static double[][] readFront(String path) {
		try {
			// Open the file
			FileInputStream fis = new FileInputStream(path);
			InputStreamReader isr = new InputStreamReader(fis);
			BufferedReader br = new BufferedReader(isr);

			List<double[]> list = new ArrayList<double[]>();
			int numberOfObjectives = 0;
			String aux = br.readLine();
			while (aux != null) {
				StringTokenizer st = new StringTokenizer(aux);
				int i = 0;
				numberOfObjectives = st.countTokens();
				double[] vector = new double[st.countTokens()];
				while (st.hasMoreTokens()) {
					double value = new Double(st.nextToken());
					vector[i] = value;
					i++;
				}
				list.add(vector);
				aux = br.readLine();
			}

			br.close();

			double[][] front = new double[list.size()][numberOfObjectives];
			for (int i = 0; i < list.size(); i++) {
				front[i] = list.get(i);
			}
			return front;

		} catch (Exception e) {
			System.out.println("InputFacilities crashed reading for file: " + path);
			e.printStackTrace();
		}
		return null;
	} // readFront

	/**
	 * Gets the maximum values for each objectives in a given pareto front
	 * 
	 * @param front
	 *            The pareto front
	 * @param noObjectives
	 *            Number of objectives in the pareto front
	 * @return double [] An array of noOjectives values whit the maximun values
	 *         for each objective
	 **/
	static double[] getMaximumValues(double[][] front, int noObjectives) {
		double[] maximumValue = new double[noObjectives];
		for (int i = 0; i < noObjectives; i++)
			maximumValue[i] = Double.NEGATIVE_INFINITY;

		for (double[] aFront : front) {
			for (int j = 0; j < aFront.length; j++) {
				if (aFront[j] > maximumValue[j])
					maximumValue[j] = aFront[j];
			}
		}

		return maximumValue;
	} // getMaximumValues

	/**
	 * Gets the minimum values for each objectives in a given pareto front
	 * 
	 * @param front
	 *            The pareto front
	 * @param noObjectives
	 *            Number of objectives in the pareto front
	 * @return double [] An array of noOjectives values whit the minimum values
	 *         for each objective
	 **/
	static double[] getMinimumValues(double[][] front, int noObjectives) {
		double[] minimumValue = new double[noObjectives];
		for (int i = 0; i < noObjectives; i++)
			minimumValue[i] = Double.MAX_VALUE;

		for (double[] aFront : front) {
			for (int j = 0; j < aFront.length; j++) {
				if (aFront[j] < minimumValue[j])
					minimumValue[j] = aFront[j];
			}
		}
		return minimumValue;
	} // getMinimumValues

	/**
	 * This method returns the distance (taken the euclidean distance) between
	 * two points given as <code>double []</code>
	 * 
	 * @param a
	 *            A point
	 * @param b
	 *            A point
	 * @return The euclidean distance between the points
	 **/
	static double distance(double[] a, double[] b) {
		double distance = 0.0;

		for (int i = 0; i < a.length; i++) {
			distance += Math.pow(a[i] - b[i], 2.0);
		}
		return Math.sqrt(distance);
	} // distance

	/**
	 * Gets the distance between a point and the nearest one in a given front
	 * (the front is given as <code>double [][]</code>)
	 * 
	 * @param point
	 *            The point
	 * @param front
	 *            The front that contains the other points to calculate the
	 *            distances
	 * @return The minimun distance between the point and the front
	 **/
	static double distanceToClosedPoint(double[] point, double[][] front) {
		double minDistance = distance(point, front[0]);

		for (int i = 1; i < front.length; i++) {
			double aux = distance(point, front[i]);
			if (aux < minDistance) {
				minDistance = aux;
			}
		}

		return minDistance;
	} // distanceToClosedPoint

	/**
	 * Gets the distance between a point and the nearest one in a given front,
	 * and this distance is greater than 0.0
	 * 
	 * @param point
	 *            The point
	 * @param front
	 *            The front that contains the other points to calculate the
	 *            distances
	 * @return The minimun distances greater than zero between the point and the
	 *         front
	 */
	static double distanceToNearestPoint(double[] point, double[][] front) {
		double minDistance = Double.MAX_VALUE;

		for (double[] aFront : front) {
			double aux = distance(point, aFront);
			if ((aux < minDistance) && (aux > 0.0)) {
				minDistance = aux;
			}
		}

		return minDistance;
	} // distanceToNearestPoint

	/**
	 * This method receives a pareto front and two points, one whit maximum
	 * values and the other with minimum values allowed, and returns a the
	 * normalized Pareto front.
	 * 
	 * @param front
	 *            A pareto front.
	 * @param maximumValue
	 *            The maximum values allowed
	 * @param minimumValue
	 *            The minimum values allowed
	 * @return the normalized pareto front
	 **/
	static double[][] getNormalizedFront(double[][] front, double[] maximumValue, double[] minimumValue) {

		double[][] normalizedFront = new double[front.length][];

		for (int i = 0; i < front.length; i++) {
			normalizedFront[i] = new double[front[i].length];
			for (int j = 0; j < front[i].length; j++) {
				normalizedFront[i][j] = (front[i][j] - minimumValue[j]) / (maximumValue[j] - minimumValue[j]);
			}
		}
		return normalizedFront;
	} // getNormalizedFront

	/**
	 * This method receives a normalized pareto front and return the inverted
	 * one. This operation needed for minimization problems
	 * 
	 * @param front
	 *            The pareto front to inverse
	 * @return The inverted pareto front
	 **/
	static double[][] invertedFront(double[][] front) {
		double[][] invertedFront = new double[front.length][];

		for (int i = 0; i < front.length; i++) {
			invertedFront[i] = new double[front[i].length];
			for (int j = 0; j < front[i].length; j++) {
				if (front[i][j] <= 1.0 && front[i][j] >= 0.0) {
					invertedFront[i][j] = 1.0 - front[i][j];
				} else if (front[i][j] > 1.0) {
					invertedFront[i][j] = 0.0;
				} else if (front[i][j] < 0.0) {
					invertedFront[i][j] = 1.0;
				}
			}
		}
		return invertedFront;
	} // invertedFront
	
}
