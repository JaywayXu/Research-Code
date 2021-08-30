package momfo.operators.mutation;

import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

import momfo.core.Solution;
import momfo.encodings.solutionType.PermutationSolutionType;
import momfo.util.Configuration;
import momfo.util.JMException;
import momfo.util.PseudoRandom;
import momfo.util.wrapper.XInt;

public class SwapMutation extends Mutation {

	private static final List VALID_TYPES = Arrays.asList(PermutationSolutionType.class);

	private Double mutationProbability_ = null;

	public SwapMutation(HashMap<String, Object> parameters) {
		super(parameters);
		if (parameters.get("probability") != null)
			mutationProbability_ = (Double) parameters.get("probability");
	}

	@Override
	public Object execute(Object object) throws JMException {
		Solution solution = (Solution) object;

		if (!VALID_TYPES.contains(solution.getType().getClass())) {
			Configuration.logger_.severe(
					"SwapMutation.execute: the solution " + "is not of the right type. The type should be 'Real', but "
							+ solution.getType() + " is obtained");

			Class cls = java.lang.String.class;
			String name = cls.getName();
			throw new JMException("Exception in " + name + ".execute()");
		} // if

		doMutation(mutationProbability_, solution);

		return solution;
	}

	public void doMutation(double probability, Solution solution) throws JMException {
		if (PseudoRandom.randDouble() <= probability) {
			XInt x = new XInt(solution);
			int numberOfVariables = x.getNumberOfDecisionVariables();
			int i = PseudoRandom.randInt(0, numberOfVariables - 1);
			int j;
			do {
				j = PseudoRandom.randInt(0, numberOfVariables - 1);
			} while (j == i);

			int temp = x.getValue(i);
			x.setValue(i, x.getValue(j));
			x.setValue(j, temp);
		}

	} // doMutation

}
