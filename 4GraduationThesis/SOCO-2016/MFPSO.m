function data_MFPSO = MFPSO(Tasks, pop, gen, eva_num, rmp, p_il, reps)
    %MFEA function: implementation of MFEA algorithm
    tic

    if mod(pop, 2) ~= 0
        pop = pop + 1;
    end

    no_of_tasks = length(Tasks);

    if no_of_tasks <= 1
        error('At least 2 tasks required for MFEA');
    end

    wmax = 0.9; % inertia weight
    wmin = 0.4; % inertia weight

    c1 = 0.2;
    c2 = 0.2;
    c3 = 0.2;
    w11 = gen;
    c11 = gen;
    c22 = gen;
    c33 = gen;

    D = zeros(1, no_of_tasks);

    for i = 1:no_of_tasks
        D(i) = Tasks(i).dims;
    end

    D_multitask = max(D);

    options = optimoptions(@fminunc, 'Display', 'off', 'Algorithm', 'quasi-newton', 'MaxIter', 2); % settings for individual learning

    fnceval_calls = zeros(1, reps);
    calls_per_individual = zeros(1, pop);
    % EvBestFitness = zeros(no_of_tasks * reps, gen); % best fitness found
    % TotalEvaluations = zeros(reps, gen); % total number of task evaluations so fer
    bestobj = Inf(1, no_of_tasks);

    for rep = 1:reps
        disp(['MFPSO: ', num2str(rep), ' test'])

        for i = 1:pop
            population(i) = Particle();
            population(i) = initialize(population(i), D_multitask);
            population(i).skill_factor = 0;
        end

        parfor i = 1:pop
            [population(i), calls_per_individual(i)] = evaluate(population(i), Tasks, p_il, no_of_tasks, options);
        end

        fnceval_calls(rep) = fnceval_calls(rep) + sum(calls_per_individual);
        TotalEvaluations(rep, 1) = fnceval_calls(rep);

        factorial_cost = zeros(1, pop);

        for i = 1:no_of_tasks

            for j = 1:pop
                factorial_cost(j) = population(j).factorial_costs(i);
            end

            [xxx, y] = sort(factorial_cost);
            population = population(y); % reorder the population according to factorial_cost of current task

            for j = 1:pop
                population(j).factorial_ranks(i) = j;
            end

            bestobj(i) = population(1).factorial_costs(i);
            gbest(i, :) = population(1).rnvec;
            EvBestFitness(i + no_of_tasks * (rep - 1), 1) = bestobj(i);
            bestInd_data(rep, i) = population(1);
        end

        for i = 1:pop
            [xxx, yyy] = min(population(i).factorial_ranks);
            x = find(population(i).factorial_ranks == xxx);
            equivalent_skills = length(x);

            if equivalent_skills > 1 % If having best fitness on multiple tasks, random choose one and set the factorial_costs of others as inf
                population(i).skill_factor = x(1 + round((equivalent_skills - 1) * rand(1)));
                tmp = population(i).factorial_costs(population(i).skill_factor);
                population(i).factorial_costs(1:no_of_tasks) = inf;
                population(i).factorial_costs(population(i).skill_factor) = tmp;
                population(i).pbestFitness = tmp;
            else % else, just set the skill_factor and set the factorial_costs of others as inf
                population(i).skill_factor = yyy;
                tmp = population(i).factorial_costs(population(i).skill_factor);
                population(i).factorial_costs(1:no_of_tasks) = inf;
                population(i).factorial_costs(population(i).skill_factor) = tmp;
                population(i).pbestFitness = tmp;
            end

        end

        ite = 1;
        noImpove = 0;

        while ite <= gen && TotalEvaluations(rep, ite) < eva_num
            w1 = wmax - (wmax - wmin) * ite / gen;

            if ~mod(ite, 10) && noImpove >= 20
                %restart
                for i = 1:pop
                    population(i) = velocityUpdate(population(i), gbest, rmp, w11, c11, c22, c33);
                end

            else

                for i = 1:pop
                    population(i) = velocityUpdate(population(i), gbest, rmp, w1, c1, c2, c3);
                end

            end

            for i = 1:pop
                population(i) = positionUpdate(population(i));
            end

            for i = 1:pop
                population(i) = pbestUpdate(population(i));
            end

            parfor i = 1:pop
                [population(i), calls_per_individual(i)] = evaluate(population(i), Tasks, p_il, no_of_tasks, options);
            end

            fnceval_calls(rep) = fnceval_calls(rep) + sum(calls_per_individual);
            TotalEvaluations(rep, ite + 1) = fnceval_calls(rep);

            factorial_cost = zeros(1, pop);

            for i = 1:no_of_tasks

                for j = 1:pop
                    factorial_cost(j) = population(j).factorial_costs(i);
                end

                [xxx, y] = sort(factorial_cost);
                population = population(y);

                for j = 1:pop
                    population(j).factorial_ranks(i) = j;
                end

                if population(1).factorial_costs(i) <= bestobj(i)
                    bestobj(i) = population(1).factorial_costs(i);
                    gbest(i, :) = population(1).rnvec;
                    bestInd_data(rep, i) = population(1);
                    noImpove = 0;
                else
                    noImpove = noImpove + 1;
                end

                EvBestFitness(i + no_of_tasks * (rep - 1), ite + 1) = bestobj(i);

            end

            % disp(['MFPSO iteration = ', num2str(ite), ' best factorial costs = ', num2str(bestobj)]);
            ite = ite + 1;
        end

    end

    data_MFPSO.wall_clock_time = toc;
    data_MFPSO.EvBestFitness = EvBestFitness;
    data_MFPSO.bestInd_data = bestInd_data;
    data_MFPSO.TotalEvaluations = TotalEvaluations;
end
