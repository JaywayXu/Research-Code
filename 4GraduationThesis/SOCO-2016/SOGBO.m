function data_SOO = SOGBO(Task, pop, gen, eva_num, reps)
    % 单任务GBO
    % 参数(任务, 种群数量, 迭代次数, 最大评价次数, LEO局部逃逸概率, 独立运行测试次数)
    % 返回值(data.wall_clock_time, data.EvBestFitness, data.bestInd_data, data.TotalEvaluations)
    tic % 计时开始
    pr = 0.5; % Probability Parameter in GBO
    options = optimoptions(@fminunc, 'Display', 'off', 'Algorithm', 'quasi-newton', 'MaxIter', 2); % settings for individual learning

    % 保证种群数量为2的整数倍
    if mod(pop, 2) ~= 0
        pop = pop + 1;
    end

    D = Task.dims; % 任务维数

    fnceval_calls = zeros(1, reps); % 每次独立测试的总评价次数
    calls_per_individual = zeros(1, pop); %每个个体的评价次数
    % EvBestFitness = zeros(reps, gen); % 每次次独立测试每代的最优解
    % TotalEvaluations = zeros(reps, gen); % 每次独立测试每代的总评价次数

    for rep = 1:reps
        % 独立运行测试
        disp(['SOGBO: ', num2str(rep), ' test'])

        % 生成种群
        for i = 1:pop
            population(i) = Chromosome();
            population(i) = initialize(population(i), D);
        end

        % 适应值评价
        parfor i = 1:pop
            [population(i), calls_per_individual(i)] = evaluate_SOO(population(i), Task, 0, options);
        end

        % 更新评价次数
        fnceval_calls(rep) = fnceval_calls(rep) + sum(calls_per_individual);
        TotalEvaluations(rep, 1) = fnceval_calls(rep);

        % 更新第一代最优解
        [bestobj, best_idx] = min([population.factorial_costs]);
        EvBestFitness(rep, 1) = bestobj;

        % GBO需要的最优X和最差X
        Best_X = population(best_idx).rnvec;
        [worstobj, worst_idx] = max([population.factorial_costs]);
        Worst_X = population(worst_idx).rnvec;

        generation = 1;

        while generation < gen && TotalEvaluations(rep, generation) < eva_num
            % 主循环
            generation = generation + 1;

            beta = 0.2 + (1.2 - 0.2) * (1 - (TotalEvaluations(rep, generation - 1) / eva_num)^3)^2; % Eq.(14.2)
            alpha = abs(beta .* sin((3 * pi / 2 + sin(3 * pi / 2 * beta)))); % Eq.(14.1)

            % GBO算法部分
            for i = 1:pop
                A1 = fix(rand(1, pop) * pop) + 1; % Four positions randomly selected from population
                r1 = A1(1); r2 = A1(2);
                r3 = A1(3); r4 = A1(4);

                % 将个体基因转换为原GBO中的X
                X = zeros(pop, D);

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

                Xnew = zeros(1, D);

                for j = 1:D
                    ro = alpha .* (2 * rand - 1);
                    X3 = X(i, j) - ro .* (X2(j) - X1(j));
                    ra = rand; rb = rand;
                    Xnew(j) = ra .* (rb .* X1(j) + (1 - rb) .* X2(j)) + (1 - ra) .* X3; % Eq.(27)
                end

                % Local escaping operator(LEO)                              % Eq.(28)
                lb = 0;
                ub = 1;

                if rand < pr
                    k = fix(rand * pop) + 1;
                    f1 = -1 + (1 - (-1)) .* rand(); f2 = -1 + (1 - (-1)) .* rand();
                    ro = alpha .* (2 * rand - 1);
                    Xk = unifrnd(lb, ub, 1, D); %lb+(ub-lb).*rand(1,D); % Eq.(28.8)

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

                % 计算适应值
                Chromosome_new = Chromosome();
                Chromosome_new.rnvec = Xnew;
                [Chromosome_new, calls_per_individual(i)] = evaluate_SOO(Chromosome_new, Task, 0, options);

                % 更新最优
                if Chromosome_new.factorial_costs < population(i).factorial_costs
                    population(i) = Chromosome_new;

                    % 更新最大值
                    if population(i).factorial_costs < bestobj
                        Best_X = population(i).rnvec;
                        bestobj = population(i).factorial_costs;
                        bestInd_data(rep) = population(i);
                    end

                end

                % 更新最差
                if population(i).factorial_costs > worstobj
                    Worst_X = population(i).rnvec;
                    worstobj = population(i).factorial_costs;
                end

            end

            fnceval_calls(rep) = fnceval_calls(rep) + sum(calls_per_individual);
            TotalEvaluations(rep, generation) = fnceval_calls(rep);
            EvBestFitness(rep, generation) = bestobj;

            % disp(['SOO Generation ', num2str(generation), ' best objective = ', num2str(bestobj)])
        end

    end

    data_SOO.wall_clock_time = toc;
    data_SOO.EvBestFitness = EvBestFitness;
    data_SOO.bestInd_data = bestInd_data;
    data_SOO.TotalEvaluations = TotalEvaluations;
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
