function saveCompare(algoNameList, benchNameList, reps, taskNum, gen)
    algoNum = length(algoNameList);
    benchNum = length(benchNameList);

    % 构造访问每个任务的下标矩阵
    Task = zeros(taskNum, reps);

    k = 1;

    for i = 1:reps

        for task_i = 1:taskNum
            Task(task_i, i) = k;
            k = k + 1;
        end

    end

    % load and prepare
    benchTaskAlgoEBF = zeros(benchNum, taskNum, algoNum * reps, gen);
    clockData = zeros(benchNum, algoNum);

    for algo_i = 1:algoNum
        dataName = ['data_', algoNameList{algo_i}];
        load(['./Data/', dataName], dataName);
        data = eval(dataName);

        for bench_i = 1:benchNum
            benchData = data(bench_i);
            clockData(bench_i, algo_i) = benchData.wall_clock_time;

            for task_i = 1:taskNum
                benchTaskAlgoEBF(bench_i, task_i, (algo_i - 1) * reps + 1:algo_i * reps, :) = benchData.EvBestFitness(Task(task_i, :), 1:gen); % reps * gen
            end

        end

    end

    % calculate score
    scoreEnd = zeros(benchNum, algoNum);
    convergence = zeros(benchNum, task_i, algoNum, gen);

    for bench_i = 1:benchNum

        for task_i = 1:taskNum
            meanEBF = mean(benchTaskAlgoEBF(bench_i, task_i, :, gen));
            stdEBF = std(benchTaskAlgoEBF(bench_i, task_i, :, gen));
            perScore = (benchTaskAlgoEBF(bench_i, task_i, :, gen) - meanEBF) ./ stdEBF;

            perAlgoScore = zeros(1, taskNum, algoNum, 1);

            for algo_i = 1:algoNum
                perAlgoScore(1, task_i, algo_i, 1) = mean(perScore(1, 1, (algo_i - 1) * reps + 1:algo_i * reps, 1));
                convergence(bench_i, task_i, algo_i, :) = mean(benchTaskAlgoEBF(bench_i, task_i, (algo_i - 1) * reps + 1:algo_i * reps, :));
            end

        end

        scoreEnd(bench_i, :) = reshape(mean(perAlgoScore), [1, algoNum]);

    end

    % save data
    mkdir('./Results_Compare/')
    scoreFile = fopen('./Results_Compare/score.txt', 'wt');
    fitnessFile = fopen('./Results_Compare/fitness.txt', 'wt');
    clockFile = fopen('./Results_Compare/clock.txt', 'wt');

    % save score
    for bench_i = 1:length(benchNameList)

        for algo_i = 1:length(algoNameList)
            % 每个算法数据
            fprintf(scoreFile, '%.2f\t', scoreEnd(bench_i, algo_i));
            fprintf(fitnessFile, '%.2f\t', convergence(bench_i, 1, algo_i, end));
            fprintf(fitnessFile, '%.2f\t', convergence(bench_i, 2, algo_i, end));
            fprintf(clockFile, '%.2f\t', clockData(bench_i, algo_i));
        end

        fprintf(scoreFile, '\n');
        fprintf(fitnessFile, '\n');
        fprintf(clockFile, '\n');

    end

    % draw convergence figure
    mkdir('./Results_Figure/')

    for bench_i = 1:benchNum

        for task_i = 1:taskNum
            fig = figure('Visible', 'off');
            x = 1:gen;

            for algo_i = 1:length(algoNameList)
                y = log(reshape(convergence(bench_i, task_i, algo_i, :), [1, gen]));
                plot(x, y, ...
                    'LineWidth', 1)
                hold on
            end

            % plot(reshape(score(bench_i, :, :), [algoNum, gen]))
            title([benchNameList{bench_i}, ' Task', int2str(task_i)])
            xlabel('Generation')
            ylabel('log(fitness)')
            legend(strrep(algoNameList, '_', '\_'))

            saveas(fig, ['./Results_Figure/', int2str(bench_i), '_', benchNameList{bench_i}, int2str(task_i), '.png']);
        end

    end

end
