function saveSOMF(data_MFO, data_SOO, reps, benchNum, taskNum)
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

    mkdir('./Results_SOMF/')
    aveSolutionMFO = fopen('./Results_SOMF/aveSolutionMFO.txt', 'wt');
    aveSolutionSO = fopen('./Results_SOMF/aveSolutionSO.txt', 'wt');
    stdMFO = fopen('./Results_SOMF/stdMFO.txt', 'wt');
    stdSO = fopen('./Results_SOMF/stdSO.txt', 'wt');
    clockMFO = fopen('./Results_SOMF/clockMFO.txt', 'wt');
    clockSO = fopen('./Results_SOMF/clockSO.txt', 'wt');

    for i = 1:benchNum
        aveInd = size(data_MFO(i).EvBestFitness, 2);
        aveInd_S = size(data_SOO(1, i).EvBestFitness, 2);

        MFO = data_MFO(i);
        SOO = data_SOO(:, i);

        MFO_end = MFO.EvBestFitness(:, aveInd);

        for task_i = 1:taskNum
            objTaskMFO(task_i, :) = mean(MFO.EvBestFitness(Task(task_i, :), :));
            aveTaskMFO(task_i, :) = objTaskMFO(task_i, aveInd);
            stdTaskMFO(task_i, :) = std(MFO_end(Task(task_i, :)));

            objTaskSO(task_i, :) = mean(SOO(task_i, :).EvBestFitness);
            aveTaskSO(task_i, :) = objTaskSO(task_i, aveInd_S);
            stdTaskSO(task_i, :) = std(SOO(task_i).EvBestFitness(:, aveInd_S));

        end

        aveClockMFO = MFO.wall_clock_time;
        aveClockSO = 0;

        for task_i = 1:taskNum
            aveClockSO = aveClockSO + SOO(task_i).wall_clock_time;
        end

        fprintf(aveSolutionMFO, '%f\n', mean(aveTaskMFO));
        fprintf(aveSolutionSO, '%f\n', mean(aveTaskSO));
        fprintf(stdMFO, '%f\n', mean(stdTaskMFO));
        fprintf(stdSO, '%f\n', mean(stdTaskSO));
        fprintf(clockMFO, '%f\n', aveClockMFO);
        fprintf(clockSO, '%f\n', aveClockSO);

    end

end
