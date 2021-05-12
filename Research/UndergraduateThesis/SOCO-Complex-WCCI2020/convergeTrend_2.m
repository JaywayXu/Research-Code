function convergeTrend_2(data_GBO, data_GBO_2, reps, gen, benchNum, taskNum)
    benchName = char('Benchmark1');

    for bi = 2:benchNum
        benchName = char(benchName, ['Benchmark', num2str(bi)]);
    end

    Task = zeros(taskNum, reps);

    k = 1;

    for i = 1:reps

        for task_i = 1:taskNum
            Task(task_i, i) = k;
            k = k + 1;
        end

    end

    x = zeros(1, gen);

    for i = 1:gen
        x(i) = i;
    end

    mkdir('./Results_2/')
    bestSolutionGBO = fopen('./Results_2/bestSolutionGBO.txt', 'wt');
    bestSolutionGBO_2 = fopen('./Results_2/bestSolutionGBO_2.txt', 'wt');
    aveSolutionGBO = fopen('./Results_2/aveSolutionGBO.txt', 'wt');
    aveSolutionGBO_2 = fopen('./Results_2/aveSolutionGBO_2.txt', 'wt');
    stdGBO = fopen('./Results_2/stdGBO.txt', 'wt');
    stdGBO_2 = fopen('./Results_2/stdGBO_2.txt', 'wt');
    % clock
    clockGBO = fopen('./Results_2/clockGBO.txt', 'wt');
    clockGBO_2 = fopen('./Results_2/clockGBO_2.txt', 'wt');

    for i = 1:benchNum
        aveInd = gen;

        GBO = data_GBO(i);
        GBO_2 = data_GBO_2(i);

        GBO_end = GBO.EvBestFitness(:, aveInd);
        GBO_2_end = GBO_2.EvBestFitness(:, aveInd);

        for task_i = 1:taskNum
            objTaskGBO(task_i, :) = mean(GBO.EvBestFitness(Task(task_i, :), :));
            bestTaskGBO(task_i, :) = min(GBO.EvBestFitness(Task(task_i, :), aveInd));
            aveTaskGBO(task_i, :) = objTaskGBO(task_i, aveInd);
            stdTaskGBO(task_i, :) = std(GBO_end(Task(task_i, :)));

            objTaskGBO_2(task_i, :) = mean(GBO_2.EvBestFitness(Task(task_i, :), :));
            bestTaskGBO_2(task_i, :) = min(GBO_2.EvBestFitness(Task(task_i, :), aveInd));
            aveTaskGBO_2(task_i, :) = objTaskGBO_2(task_i, aveInd);
            stdTaskGBO_2(task_i, :) = std(GBO_2_end(Task(task_i, :)));
        end

        % clock
        aveClockGBO = GBO.wall_clock_time;
        aveClockGBO_2 = GBO_2.wall_clock_time;
        fprintf(clockGBO, '%f\n', aveClockGBO);
        fprintf(clockGBO_2, '%f\n', aveClockGBO_2);

        for task_i = 1:taskNum
            fprintf(bestSolutionGBO, '%f\n', bestTaskGBO(task_i, :));
            fprintf(aveSolutionGBO, '%f\n', aveTaskGBO(task_i, :));
            fprintf(stdGBO, '%f\n', stdTaskGBO(task_i, :));

            fprintf(bestSolutionGBO_2, '%f\n', bestTaskGBO_2(task_i, :));
            fprintf(aveSolutionGBO_2, '%f\n', aveTaskGBO_2(task_i, :));
            fprintf(stdGBO_2, '%f\n', stdTaskGBO_2(task_i, :));
        end

        for task_i = 1:taskNum
            h = figure('visible', 'off');
            plot(x, objTaskGBO(task_i, 1:gen), 'r', 'Linewidth', 1);
            hold on;
            plot(x, objTaskGBO_2(task_i, 1:gen), 'y', 'Linewidth', 1);
            hold on;

            title(['T', num2str(task_i), ' ', 'in', ' ', benchName(i, :)]);
            t = legend('GBO', 'GBO_2');
            xlabel('Generation');
            ylabel('Cost');
            set(t, 'Fontsize', 20);
            set(gca, 'Fontsize', 16);

            outPath = ['./Results_2/', strrep(benchName(i, :), ' ', ''), 'Task', num2str(task_i), '.png'];
            print(h, '-dpng', outPath);
            close(h);

        end

    end

end
