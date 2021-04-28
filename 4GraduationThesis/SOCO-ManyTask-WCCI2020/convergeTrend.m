function convergeTrend(data_MFO, data_SOO, reps, gen, benchNum, taskNum)
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

    mkdir('./Results/')
    bestSolutionMFO = fopen('./Results/bestSolutionMFO.txt', 'wt');
    bestSolutionSO = fopen('./Results/bestSolutionSO.txt', 'wt');
    aveSolutionMFO = fopen('./Results/aveSolutionMFO.txt', 'wt');
    aveSolutionSO = fopen('./Results/aveSolutionSO.txt', 'wt');
    stdMFO = fopen('./Results/stdMFO.txt', 'wt');
    stdSO = fopen('./Results/stdSO.txt', 'wt');
    clockMFO = fopen('./Results/clockMFO.txt', 'wt');
    clockSO = fopen('./Results/clockSO.txt', 'wt');

    for i = 1:benchNum
        aveInd = gen;

        MFO = data_MFO(i);
        SOO = data_SOO(:, i);

        MFO_end = MFO.EvBestFitness(:, aveInd);

        for task_i = 1:taskNum
            objTaskMFO(task_i, :) = mean(MFO.EvBestFitness(Task(task_i, :), :));
            objTaskSO(task_i, :) = mean(SOO(task_i, :).EvBestFitness);

            bestTaskMFO(task_i, :) = min(min(MFO.EvBestFitness(Task(task_i, :), :)));
            aveTaskMFO(task_i, :) = objTaskMFO(task_i, aveInd);
            stdTaskMFO(task_i, :) = std(MFO_end(Task(task_i, :)));

            bestTaskSO(task_i, :) = min(min(SOO(task_i).EvBestFitness));
            aveTaskSO(task_i, :) = objTaskSO(task_i, aveInd);
            stdTaskSO(task_i, :) = std(SOO(task_i).EvBestFitness(:, aveInd));

        end

        aveClockMFO = MFO.wall_clock_time;
        aveClockSO = 0;

        for task_i = 1:taskNum
            aveClockSO = aveClockSO + SOO(task_i).wall_clock_time;
        end

        fprintf(bestSolutionMFO, '%f\n', mean(bestTaskMFO));
        fprintf(bestSolutionSO, '%f\n', mean(bestTaskSO));
        fprintf(aveSolutionMFO, '%f\n', mean(aveTaskMFO));
        fprintf(aveSolutionSO, '%f\n', mean(aveTaskSO));
        fprintf(stdMFO, '%f\n', mean(stdTaskMFO));
        fprintf(stdSO, '%f\n', mean(stdTaskSO));
        % for task_i = 1:taskNum
        %     fprintf(bestSolutionMFO, '%f\n', bestTaskMFO(task_i));
        %     fprintf(bestSolutionSO, '%f\n', bestTaskSO(task_i));
        %     fprintf(aveSolutionMFO, '%f\n', aveTaskMFO(task_i));
        %     fprintf(aveSolutionSO, '%f\n', aveTaskSO(task_i));
        %     fprintf(stdMFO, '%f\n', stdTaskMFO(task_i));
        %     fprintf(stdSO, '%f\n', stdTaskSO(task_i));
        % end

        fprintf(clockMFO, '%f\n', aveClockMFO);
        fprintf(clockSO, '%f\n', aveClockSO);

        mkdir(['./Results/', strrep(benchName(i, :), ' ', '')])

        for task_i = 1:taskNum
            h = figure('visible', 'off');
            plot(x, objTaskMFO(task_i, 1:gen), 'r', 'Linewidth', 1);
            hold on;
            plot(x, objTaskSO(task_i, 1:gen), 'b', 'Linewidth', 1);
            hold on;

            title(['T', num2str(task_i), ' ', 'in', ' ', benchName(i, :)]);
            t = legend('MFO', 'SOO');
            xlabel('Generation');
            ylabel('Cost');
            set(t, 'Fontsize', 20);
            set(gca, 'Fontsize', 16);

            outPath = ['./Results/', strrep(benchName(i, :), ' ', ''), '/Task', num2str(task_i), '.png'];
            print(h, '-dpng', outPath);
            close(h);

        end

    end

end
