function data_MFGBO = MFGBO(Tasks, pop, gen, rmp, pr, p_il, reps)
    % MFGBO
    % 参数(任务组, 种群数量, 迭代次数, 随机匹配概率, LEO局部逃逸概率, 用局部优化函数的概率)
    % 返回值(data.wall_clock_time, data.EvBestFitness, data.bestInd_data, data.TotalEvaluations)
    clc
    tic % 计时开始

    % 保证种群数量为2的整数倍
    if mod(pop, 2) ~= 0
        pop = pop + 1;
    end

    no_of_tasks = length(Tasks); % 任务数量

    % 保证任务数量大于1
    if no_of_tasks <= 1
        error('At least 2 tasks required for MFGBO');
    end

    D = zeros(1, no_of_tasks); % 每个任务解的维数

    for i = 1:no_of_tasks
        D(i) = Tasks(i).dims;
    end

    D_multitask = max(D); %个体的维数(所有任务中最大的维数)

    % 局部搜索方法，quasi-newton法
    options = optimoptions(@fminunc, 'Display', 'off', 'Algorithm', 'quasi-newton', 'MaxIter', 5);

    fnceval_calls = zeros(1, reps); % 每次独立测试的总评价次数
    calls_per_individual = zeros(1, pop); % 每个个体的评价次数
    EvBestFitness = zeros(no_of_tasks * reps, gen); % 每次测试的每个任务上每代最优解
    TotalEvaluations = zeros(reps, gen); % 每次独立测试每代的总评价次数
    bestobj = inf * (ones(1, no_of_tasks)); % 每个任务的最优解
    worstobj = zeros(1, no_of_tasks); % 每个任务对最差解
    Best_Xs = zeros(no_of_tasks, D_multitask);
    Worst_Xs = zeros(no_of_tasks, D_multitask);

    for rep = 1:reps
        disp(rep)

        % 生成种群
        for i = 1:pop
            population(i) = Chromosome();
            population(i) = initialize(population(i), D_multitask);
            population(i).skill_factor = 0;
        end

        % 适应值评价
        parfor i = 1:pop
            [population(i), calls_per_individual(i)] = evaluate(population(i), Tasks, p_il, no_of_tasks, options);
        end

        % 更新评价次数
        fnceval_calls(rep) = fnceval_calls(rep) + sum(calls_per_individual);
        TotalEvaluations(rep, 1) = fnceval_calls(rep);

        factorial_cost = zeros(1, pop); % 每个个体的因子函数值

        for i = 1:no_of_tasks
            % 统计个体在每个任务上的因子排名

            for j = 1:pop
                factorial_cost(j) = population(j).factorial_costs(i);
            end

            % 按照任务i的函数值对population进行排序
            [~, y] = sort(factorial_cost);
            population = population(y);

            for j = 1:pop
                % 统计每个个体在第i个任务的排名
                population(j).factorial_ranks(i) = j;
            end

            bestobj(i) = population(1).factorial_costs(i);
            worstobj(i) = population(end).factorial_costs(i);
            Best_Xs(i, :) = population(1).rnvec;
            Worst_Xs(i, :) = population(end).rnvec;
            EvBestFitness(i + 2 * (rep - 1), 1) = bestobj(i);
            bestInd_data(rep, i) = population(1); % 每个任务上最优解对应的个体
        end

        for i = 1:pop
            % 设置每个个体的技能因子

            % 找到每个个体最适应的任务
            [xxx, yyy] = min(population(i).factorial_ranks);
            x = find(population(i).factorial_ranks == xxx);
            equivalent_skills = length(x); % 最适应的任务的个数

            if equivalent_skills > 1
                % 适应多个任务

                % 随机选取一个最适应的任务
                population(i).skill_factor = x(1 + round((equivalent_skills - 1) * rand(1)));
                % 将其他的函数值置为无穷大，只保留当前最适应的任务的函数值
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

        generation = 1;

        while generation <= gen
            % 主循环
            generation = generation + 1;

            beta = 0.2 + (1.2 - 0.2) * (1 - (generation / gen)^3)^2; % Eq.(14.2)
            alpha = abs(beta .* sin((3 * pi / 2 + sin(3 * pi / 2 * beta)))); % Eq.(14.1)

            for i = 1:pop
                % 分类交配关键代码
                A1 = fix(rand(1, pop) * pop) + 1;
                r1 = A1(1); % 主个体

                if rand() < rmp
                    % 随机选取其他3个个体
                    r2 = A1(2);
                    r3 = A1(3);
                    r4 = A1(4);

                    % 最优解和最差解从任务中随机选取
                    Best_X = Best_Xs(randi([1, no_of_tasks]));
                    Worst_X = Worst_Xs(randi([1, no_of_tasks]));
                else
                    % 当前任务内选取其他3个个体
                    sf = population(r1).skill_factor;
                    iter = 2;

                    while population(iter).skill_factor ~= sf
                        iter = iter + 1;
                    end

                    r2 = A1(iter);
                    iter = iter + 1;

                    while population(iter).skill_factor ~= sf
                        iter = iter + 1;
                    end

                    r3 = A1(iter);
                    iter = iter + 1;

                    while population(iter).skill_factor ~= sf
                        iter = iter + 1;
                    end

                    r4 = A1(iter);

                    % 最优解和最差解从当前任务中选取
                    Best_X = Best_Xs(sf);
                    Worst_X = Worst_Xs(sf);
                end

                % 将个体基因转换为原GBO中的X
                X = zeros(pop, D_multitask);

                for j = 1:pop
                    X(j, :) = population(j).rnvec;
                end

                Xm = (X(r1, :) + X(r2, :) + X(r3, :) + X(r4, :)) / 4; % Average of Four positions randomly selected from population
                ro = alpha .* (2 * rand - 1); ro1 = alpha .* (2 * rand - 1);
                eps = 5e-3 * rand; % Randomization Epsilon

                DM = rand .* ro .* (Best_X - X(r1, :)); Flag = 1; % Direction of Movement Eq.(18)
                GSR = GradientSearchRule(ro1, Best_X, Worst_X, X(i, :), X(r1, :), DM, eps, Xm, Flag);
                DM = rand .* ro .* (Best_X - X(r1, :));
                X1 = X(i, :) - GSR + DM; % Eq.(25)

                DM = rand .* ro .* (X(r1, :) - X(r2, :)); Flag = 2;
                GSR = GradientSearchRule(ro1, Best_X, Worst_X, X(i, :), X(r1, :), DM, eps, Xm, Flag);
                DM = rand .* ro .* (X(r1, :) - X(r2, :));
                X2 = Best_X - GSR + DM; % Eq.(26)

                Xnew = zeros(1, D_multitask);

                % Local escaping operator(LEO)                              % Eq.(28)
                lb = 0;
                ub = 1;

                if rand < pr
                    k = fix(rand * pop) + 1;
                    f1 = -1 + (1 - (-1)) .* rand(); f2 = -1 + (1 - (-1)) .* rand();
                    ro = alpha .* (2 * rand - 1);
                    Xk = unifrnd(lb, ub, 1, D_multitask); %lb+(ub-lb).*rand(1,D_multitask); % Eq.(28.8)

                    L1 = rand < 0.5; u1 = L1 .* 2 * rand + (1 - L1) .* 1; u2 = L1 .* rand + (1 - L1) .* 1;
                    u3 = L1 .* rand + (1 - L1) .* 1;
                    L2 = rand < 0.5;
                    Xp = (1 - L2) .* X(k, :) + (L2) .* Xk; % Eq.(28.7)

                    if u1 < 0.5
                        Xnew = Xnew + f1 .* (u1 .* Best_X - u2 .* Xp) + f2 .* ro .* (u3 .* (X2 - X1) + u2 .* (X(r1, :) - X(r2, :))) / 2;
                    else
                        Xnew = Best_X + f1 .* (u1 .* Best_X - u2 .* Xp) + f2 .* ro .* (u3 .* (X2 - X1) + u2 .* (X(r1, :) - X(r2, :))) / 2;
                    end

                end

                % 越界则拉回到边界
                Xnew(Xnew > ub) = ub;
                Xnew(Xnew < lb) = lb;

                % 生成新个体
                child(i) = Chromosome();
                child(i).rnvec = Xnew;

                % 随机遗传r1或r2的技能因子
                if rand() < 0.5
                    child(i).skill_factor = population(r1).skill_factor;
                else
                    child(i).skill_factor = population(r2).skill_factor;
                end

            end

            parfor i = 1:pop
                % 函数值评价
                [child(i), calls_per_individual(i)] = evaluate(child(i), Tasks, p_il, no_of_tasks, options);
            end

            % 更新评价次数
            fnceval_calls(rep) = fnceval_calls(rep) + sum(calls_per_individual);
            TotalEvaluations(rep, generation) = fnceval_calls(rep);

            % 合并两代种群
            intpopulation(1:pop) = population;
            intpopulation(pop + 1:2 * pop) = child;
            factorial_cost = zeros(1, 2 * pop);

            for i = 1:no_of_tasks
                % 统计个体在每个任务上的因子排名

                for j = 1:2 * pop
                    factorial_cost(j) = intpopulation(j).factorial_costs(i);
                end

                % 按照任务i的函数值对population进行排序
                [~, y] = sort(factorial_cost);
                intpopulation = intpopulation(y);

                for j = 1:2 * pop
                    % 统计每个个体在第i个任务的排名
                    intpopulation(j).factorial_ranks(i) = j;
                end

                if intpopulation(1).factorial_costs(i) < bestobj(i)
                    % 更新最优
                    bestobj(i) = intpopulation(1).factorial_costs(i);
                    bestInd_data(rep, i) = intpopulation(1);
                    Best_Xs(i, :) = population(1).rnvec;
                end

                if intpopulation(end).factorial_costs(i) > worstobj(i)
                    % 更新最差
                    worstobj(i) = population(end).factorial_costs(i);
                    Worst_Xs(i, :) = population(end).rnvec;
                end

                EvBestFitness(i + 2 * (rep - 1), generation) = bestobj(i);
            end

            for i = 1:2 * pop
                % 更新每个个体的技能因子和标量适应值
                [xxx, yyy] = min(intpopulation(i).factorial_ranks);
                intpopulation(i).skill_factor = yyy;
                intpopulation(i).scalar_fitness = 1 / xxx;
            end

            % 保留适应值最好的前pop个
            [~, y] = sort(-[intpopulation.scalar_fitness]);
            intpopulation = intpopulation(y);
            population = intpopulation(1:pop);

            disp(['MFGBO Generation = ', num2str(generation), ' best factorial costs = ', num2str(bestobj)]);
        end

        data_MFGBO.wall_clock_time = toc; % 计时结束
        data_MFGBO.EvBestFitness = EvBestFitness;
        data_MFGBO.bestInd_data = bestInd_data;
        data_MFGBO.TotalEvaluations = TotalEvaluations;

    end

end

% _________________________________________________
% Gradient Search Rule
function GSR = GradientSearchRule(ro1, Best_X, Worst_X, X, Xr1, DM, eps, Xm, Flag)
    D = size(X, 2);
    Delta = 2 .* rand .* abs(Xm - X); % Eq.(16.2)
    Step = ((Best_X - Xr1) + Delta) / 2; % Eq.(16.1)
    DelX = rand(1, D) .* (abs(Step)); % Eq.(16)

    GSR = randn .* ro1 .* (2 * DelX .* X) ./ (Best_X - Worst_X + eps); % Gradient search rule  Eq.(15)

    if Flag == 1
        Xs = X - GSR + DM; % Eq.(21)
    else
        Xs = Best_X - GSR + DM;
    end

    yp = rand .* (0.5 * (Xs + X) + rand .* DelX); % Eq.(22.6)
    yq = rand .* (0.5 * (Xs + X) - rand .* DelX); % Eq.(22.7)
    GSR = randn .* ro1 .* (2 * DelX .* X) ./ (yp - yq + eps); % Eq.(23)
end
