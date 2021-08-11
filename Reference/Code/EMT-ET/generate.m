function offspring = generate(population, N, proc, disc, prom, dism, Problem, T, LBOUND, UBOUND)
    P = TournamentSelection(2, N, population.rank);
    offspring = struct('x', [], 'f', [], 'rank', [], 'sign', []);
    offspring.x = eareal(population.x(P, :), proc, disc, prom, dism, LBOUND, UBOUND);
    %offspring.x = DE(population.x(P,:));
    offspring.f = objective(offspring.x, Problem, T);
    offspring.sign = zeros(N, 1);
end
