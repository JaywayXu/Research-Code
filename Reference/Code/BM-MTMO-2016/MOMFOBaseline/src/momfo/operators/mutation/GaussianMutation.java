package momfo.operators.mutation;

import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Random;

import momfo.core.Solution;
import momfo.encodings.solutionType.RealSolutionType;
import momfo.util.Configuration;
import momfo.util.JMException;
import momfo.util.PseudoRandom;
import momfo.util.wrapper.XReal;

public class GaussianMutation extends Mutation {

	private static final List VALID_TYPES = Arrays.asList(RealSolutionType.class);

	private Double mutationProbability_ = null;

	private Double sigma_ = null;

	public GaussianMutation(HashMap<String, Object> parameters) {
		super(parameters);
		if (parameters.get("probability") != null)
			mutationProbability_ = (Double) parameters.get("probability");
		if (parameters.get("sigma") != null)
			sigma_ = (Double) parameters.get("sigma");
	}

	public void doMutation(double probability, Solution solution) throws JMException {
		XReal x = new XReal(solution);
		Random rand = new Random();

		for (int var = 0; var < solution.getDecisionVariables().length; var++) {
			if (PseudoRandom.randDouble() < probability) {
				double tmp = rand.nextGaussian() * sigma_;
				tmp += x.getValue(var);

				if (tmp < x.getLowerBound(var))
					tmp = x.getLowerBound(var);
				else if (tmp > x.getUpperBound(var))
					tmp = x.getUpperBound(var);

				x.setValue(var, tmp);
			} // if
		} // for
	} // doMutation

	public Object execute(Object object) throws JMException {
		Solution solution = (Solution) object;

		if (!VALID_TYPES.contains(solution.getType().getClass())) {
			Configuration.logger_.severe("GaussianMutation.execute: the solution "
					+ "is not of the right type. The type should be 'Real', but " + solution.getType()
					+ " is obtained");

			Class cls = java.lang.String.class;
			String name = cls.getName();
			throw new JMException("Exception in " + name + ".execute()");
		} // if

		doMutation(mutationProbability_, solution);

		return solution;
	} // execute

}
