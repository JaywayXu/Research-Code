function population = update_population(population, OBJS1, Problem, NVARS, T, N)
    population.f = objective(population.x, Problem, T);
    [nSort, ~] = size(population.x);
    FrontNo = NDSort(population.f, nSort)';
    CrowdDis = CrowdingDistance(population.f, FrontNo)';
    X = [population.x, population.f, FrontNo, CrowdDis, population.sign];

    if T == 1
        X = sortrows(X, [(NVARS(1) + OBJS1 + 1), -(NVARS(1) + OBJS1 + 2)]);
        population.x = X(1:N, 1:NVARS(1));
        population.f = X(1:N, (NVARS(1) + 1):(NVARS(1) + OBJS1));
        population.rank = X(1:N, (NVARS(1) + OBJS1 + 1));
        population.sign = X(1:N, end);
    else
        X = sortrows(X, [(NVARS(2) + 2 + 1), -(NVARS(2) + 2 + 2)]);
        population.x = X(1:N, 1:NVARS(2));
        population.f = X(1:N, (NVARS(2) + 1):(NVARS(2) + 2));
        population.rank = X(1:N, (NVARS(2) + 2 + 1));
        population.sign = X(1:N, end);
    end

end
