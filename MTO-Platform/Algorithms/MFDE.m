classdef MFDE < Algorithm

    properties (SetAccess = private)
        rmp = 0.3
        selection_process = 'elitist'
        p_il = 0
        F = 0.5
        pCR = 0.9
    end

    methods

        function parameter = getParameter(obj)
            parameter = {'Random Mating Probability (rmp)', num2str(obj.rmp), ...
                        'elitist / roulette wheel', obj.selection_process, ...
                        'Local Search Probability (p_il)', num2str(obj.p_il), ...
                        'Mutation Factor (F)', num2str(obj.F), ...
                        'Crossover Probability (pCR)', num2str(obj.pCR)};
        end

        function obj = setParameter(obj, parameter_cell)
            obj.rmp = str2double(parameter_cell{1});
            obj.selection_process = parameter_cell{2};
            obj.p_il = str2double(parameter_cell{3});
            obj.F = str2double(parameter_cell{4});
            obj.pCR = str2double(parameter_cell{5});
        end

        function data = run(obj, Tasks, pre_run_list)
            obj.setPreRun(pre_run_list);

            rmp = obj.rmp;
            pop = obj.pop_size;
            gen = obj.iter_num;
            eva_num = obj.eva_num;
            selection_process = obj.selection_process;
            p_il = obj.p_il;
            F = obj.F;
            pCR = obj.pCR;

            tic

            if mod(pop, 2) ~= 0
                pop = pop + 1;
            end

            no_of_tasks = length(Tasks);

            if no_of_tasks <= 1
                error('At least 2 tasks required for MFDE');
            end

            D = zeros(1, no_of_tasks);

            for i = 1:no_of_tasks
                D(i) = Tasks(i).dims;
            end

            D_multitask = max(D);
            options = optimoptions(@fminunc, 'Display', 'off', 'Algorithm', 'quasi-newton', 'MaxIter', 2); % settings for individual learning

            fnceval_calls = zeros(1);
            calls_per_individual = zeros(1, pop);
            bestobj = Inf(1, no_of_tasks);
            bestFncErrorValue = zeros(100, 60);

            for i = 1:pop
                population(i) = Chromosome_MFDE();
                population(i) = initialize(population(i), D_multitask);
                population(i).skill_factor = 0;
            end

            parfor i = 1:pop
                [population(i), calls_per_individual(i)] = evaluate(population(i), Tasks, p_il, no_of_tasks, options);
            end

            fnceval_calls = fnceval_calls + sum(calls_per_individual);
            TotalEvaluations(1) = fnceval_calls;

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

                bestobj(i) = population(1).factorial_costs(i);
                EvBestFitness(i, 1) = bestobj(i);
                bestInd_data(i) = population(1);
            end

            for i = 1:pop
                [xxx, yyy] = min(population(i).factorial_ranks);
                x = find(population(i).factorial_ranks == xxx);
                equivalent_skills = length(x);

                if equivalent_skills > 1
                    population(i).skill_factor = x(1 + round((equivalent_skills - 1) * rand(1)));
                    tmp = population(i).factorial_costs(population(i).skill_factor);
                    population(i).factorial_costs(1:no_of_tasks) = inf;
                    population(i).factorial_costs(population(i).skill_factor) = tmp;
                else
                    population(i).skill_factor = yyy;
                    tmp = population(i).factorial_costs(population(i).skill_factor);
                    population(i).factorial_costs(1:no_of_tasks) = inf;
                    population(i).factorial_costs(population(i).skill_factor) = tmp;
                end

            end

            lb = zeros(1, D_multitask); % ����ȡֵ�½�
            ub = ones(1, D_multitask); % ����ȡֵ�Ͻ�
            generation = 1;

            while generation < gen && TotalEvaluations(generation) < eva_num
                generation = generation + 1;
                count = 1;

                asf = []; bsf = [];

                for j = 1:pop

                    if population(j).skill_factor == 1 % TODO
                        asf = [asf, j];
                    else
                        bsf = [bsf, j];
                    end

                end

                group = {asf, bsf};

                for i = 1:pop
                    x = population(i).rnvec; % ��ȡ���������

                    asf = cell2mat(group(population(i).skill_factor));
                    bsf = cell2mat(group(2 / population(i).skill_factor));

                    B = randperm(length(asf));
                    C = randperm(length(bsf));
                    asf = asf(B);
                    bsf = bsf(C);

                    childsf = 0;

                    for j = 1:length(asf)

                        if asf(j) == i
                            asf(j) = [];
                            break;
                        end

                    end

                    p1 = asf(1);

                    urmp = rand(1);

                    if urmp <= rmp
                        p2 = bsf(2);
                        p3 = bsf(3);
                        childsf = 1;
                    else
                        p2 = asf(2);
                        p3 = asf(3);
                    end

                    % ������� Mutation
                    y = population(p1).rnvec + F * (population(p2).rnvec - population(p3).rnvec); % �����м���
                    % ��ֹ�м���Խ��
                    y = max(y, lb);
                    y = min(y, ub);

                    z = zeros(size(x)); % ��ʼ��һ���¸���
                    j0 = randi([1, numel(x)]); % ����һ��α���������ѡȡ������ά�ȱ��

                    for j = 1:numel(x) % ����ÿ��ά��

                        if j == j0 || rand <= pCR % �����ǰά���Ǵ�����ά�Ȼ����������С�ڽ������
                            z(j) = y(j); % �¸��嵱ǰά��ֵ�����м����Ӧά��ֵ
                        else
                            z(j) = x(j); % �¸��嵱ǰά��ֵ���ڵ�ǰ�����Ӧά��ֵ
                        end

                    end

                    child(count) = Chromosome_MFDE();
                    child(count).rnvec = z;

                    if childsf == 0
                        child(count).skill_factor = population(i).skill_factor;
                    else
                        u = rand(1);
                        child(count).skill_factor(u <= 0.5) = population(i).skill_factor;
                        child(count).skill_factor(u > 0.5) = 2 / population(i).skill_factor;
                    end

                    count = count + 1;

                end

                parfor i = 1:pop
                    [child(i), calls_per_individual(i)] = evaluate(child(i), Tasks, p_il, no_of_tasks, options);
                end

                fnceval_calls = fnceval_calls + sum(calls_per_individual);
                TotalEvaluations(generation) = fnceval_calls;

                intpopulation(1:pop) = population;
                intpopulation(pop + 1:2 * pop) = child;
                factorial_cost = zeros(1, 2 * pop);

                for i = 1:no_of_tasks

                    for j = 1:2 * pop
                        factorial_cost(j) = intpopulation(j).factorial_costs(i);
                    end

                    [xxx, y] = sort(factorial_cost);
                    intpopulation = intpopulation(y);

                    for j = 1:2 * pop
                        intpopulation(j).factorial_ranks(i) = j;
                    end

                    if intpopulation(1).factorial_costs(i) <= bestobj(i)
                        bestobj(i) = intpopulation(1).factorial_costs(i);
                        bestInd_data(i) = intpopulation(1);
                    end

                    EvBestFitness(i, generation) = bestobj(i);

                    if mod(fnceval_calls, 3000) == 0
                        bestFncErrorValue(fnceval_calls / 3000, 1) = fnceval_calls;
                        bestFncErrorValue(fnceval_calls / 3000, i + 1) = bestobj(i);
                    end

                end

                for i = 1:2 * pop
                    [xxx, yyy] = min(intpopulation(i).factorial_ranks);
                    intpopulation(i).skill_factor = yyy;
                    intpopulation(i).scalar_fitness = 1 / xxx;
                end

                if strcmp(selection_process, 'elitist')
                    [xxx, y] = sort(-[intpopulation.scalar_fitness]);
                    intpopulation = intpopulation(y);
                    population = intpopulation(1:pop);
                elseif strcmp(selection_process, 'roulette wheel')

                    for i = 1:no_of_tasks
                        skill_group(i).individuals = intpopulation([intpopulation.skill_factor] == i);
                    end

                    count = 0;

                    while count < pop
                        count = count + 1;
                        skill = mod(count, no_of_tasks) + 1;
                        population(count) = skill_group(skill).individuals(RouletteWheelSelection([skill_group(skill).individuals.scalar_fitness]));
                    end

                end

                % disp(['MFDE Generation = ', num2str(generation), ' best factorial costs = ', num2str(bestobj)]);
            end

            data.clock_time = toc; % ��ʱ����
            data.convergence = EvBestFitness;
        end

        % dlmwrite(['MTSOO_P', num2str(index), '.txt'], bestFncErrorValue, 'precision', 6);
    end

end