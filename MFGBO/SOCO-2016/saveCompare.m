function saveCompare(data_GBO, data_GA, data_DE, data_PSO, reps, benchNum, taskNum)
    benchName = {'CI-HS', 'CI-MS', 'CI-LS', 'PI-HS', 'PI-MS', 'PI-LS', 'NI-HS', 'NI-MS', 'NI-LS'};

    Task = zeros(taskNum, reps);

    k = 1;

    for i = 1:reps

        for task_i = 1:taskNum
            Task(task_i, i) = k;
            k = k + 1;
        end

    end

    mkdir('./Results_Compare/')
    aveSolutionGBO = fopen('./Results_Compare/aveSolutionGBO.txt', 'wt');
    aveSolutionGA = fopen('./Results_Compare/aveSolutionGA.txt', 'wt');
    aveSolutionDE = fopen('./Results_Compare/aveSolutionDE.txt', 'wt');
    aveSolutionPSO = fopen('./Results_Compare/aveSolutionPSO.txt', 'wt');
    stdGBO = fopen('./Results_Compare/stdGBO.txt', 'wt');
    stdGA = fopen('./Results_Compare/stdGA.txt', 'wt');
    stdDE = fopen('./Results_Compare/stdDE.txt', 'wt');
    stdPSO = fopen('./Results_Compare/stdPSO.txt', 'wt');
    % clock
    clockGBO = fopen('./Results_Compare/clockGBO.txt', 'wt');
    clockGA = fopen('./Results_Compare/clockGA.txt', 'wt');
    clockDE = fopen('./Results_Compare/clockDE.txt', 'wt');
    clockPSO = fopen('./Results_Compare/clockPSO.txt', 'wt');

    for i = 1:benchNum
        aveInd_GBO = size(data_GBO(i).EvBestFitness, 2);
        aveInd_GA = size(data_GA(i).EvBestFitness, 2);
        aveInd_DE = size(data_DE(i).EvBestFitness, 2);
        aveInd_PSO = size(data_PSO(i).EvBestFitness, 2);

        GBO = data_GBO(i);
        GA = data_GA(i);
        DE = data_DE(i);
        PSO = data_PSO(i);

        GBO_end = GBO.EvBestFitness(:, aveInd_GBO);
        GA_end = GA.EvBestFitness(:, aveInd_GA);
        DE_end = DE.EvBestFitness(:, aveInd_DE);
        PSO_end = PSO.EvBestFitness(:, aveInd_PSO);

        for task_i = 1:taskNum
            objTaskGBO(task_i, :) = mean(GBO.EvBestFitness(Task(task_i, :), :));
            aveTaskGBO(task_i, :) = objTaskGBO(task_i, aveInd_GBO);
            stdTaskGBO(task_i, :) = std(GBO_end(Task(task_i, :)));

            objTaskGA(task_i, :) = mean(GA.EvBestFitness(Task(task_i, :), :));
            aveTaskGA(task_i, :) = objTaskGA(task_i, aveInd_GA);
            stdTaskGA(task_i, :) = std(GA_end(Task(task_i, :)));

            objTaskDE(task_i, :) = mean(DE.EvBestFitness(Task(task_i, :), :));
            aveTaskDE(task_i, :) = objTaskDE(task_i, aveInd_DE);
            stdTaskDE(task_i, :) = std(DE_end(Task(task_i, :)));

            objTaskPSO(task_i, :) = mean(PSO.EvBestFitness(Task(task_i, :), :));
            aveTaskPSO(task_i, :) = objTaskPSO(task_i, aveInd_PSO);
            stdTaskPSO(task_i, :) = std(PSO_end(Task(task_i, :)));
        end

        % clock
        aveClockGBO = GBO.wall_clock_time;
        aveClockGA = GA.wall_clock_time;
        aveClockDE = DE.wall_clock_time;
        aveClockPSO = PSO.wall_clock_time;
        fprintf(clockGBO, '%f\n', aveClockGBO);
        fprintf(clockGA, '%f\n', aveClockGA);
        fprintf(clockDE, '%f\n', aveClockDE);
        fprintf(clockPSO, '%f\n', aveClockPSO);

        for task_i = 1:taskNum
            fprintf(aveSolutionGBO, '%f\n', aveTaskGBO(task_i, :));
            fprintf(stdGBO, '%f\n', stdTaskGBO(task_i, :));

            fprintf(aveSolutionGA, '%f\n', aveTaskGA(task_i, :));
            fprintf(stdGA, '%f\n', stdTaskGA(task_i, :));

            fprintf(aveSolutionDE, '%f\n', aveTaskDE(task_i, :));
            fprintf(stdDE, '%f\n', stdTaskDE(task_i, :));

            fprintf(aveSolutionPSO, '%f\n', aveTaskPSO(task_i, :));
            fprintf(stdPSO, '%f\n', stdTaskPSO(task_i, :));
        end

    end

end
