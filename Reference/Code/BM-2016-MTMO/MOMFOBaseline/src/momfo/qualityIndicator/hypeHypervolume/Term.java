package momfo.qualityIndicator.hypeHypervolume;

public class Term implements Comparable<Term> {

	public static int loc = 1;

	public double[] data;
	public int index;

	public Term(double[] data, int index) {
		this.data = data;
		this.index = index;
	}

	@Override
	public int compareTo(Term arg0) {
		double v1 = data[loc];
		double v2 = arg0.data[loc];

		if (v1 < v2)
			return -1;
		else if (v1 > v2)
			return 1;
		else
			return 0;
	}
}
