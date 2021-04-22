function convergeTrend_compare(data_GBO, data_EA, data_DE, data_PSO, reps, gen, benchNum)
    Task1 = [];
    Task2 = [];

    for i = 1:2:(reps * 2)
        Task1 = [Task1, i];
        Task2 = [Task2, i + 1];
    end

    x = [];

    for i = 1:(gen + 1)
        x = [x, i];
    end

    taskName = {'CI_HS', 'CI_MS', 'CI_LS', 'PI_HS', 'PI_MS', 'PI_LS', 'NI_HS', 'NI_MS', 'NI_LS'};
    taskName1 = {'CI\_HS', 'CI\_MS', 'CI\_LS', 'PI\_HS', 'PI\_MS', 'PI\_LS', 'NI\_HS', 'NI\_MS', 'NI\_LS'};

    bestSolutionGBO = fopen('./Results_compare/bestSolutionGBO.txt', 'wt');
    bestSolutionEA = fopen('./Results_compare/bestSolutionEA.txt', 'wt');
    bestSolutionDE = fopen('./Results_compare/bestSolutionDE.txt', 'wt');
    bestSolutionPSO = fopen('./Results_compare/bestSolutionPSO.txt', 'wt');
    aveSolutionGBO = fopen('./Results_compare/aveSolutionGBO.txt', 'wt');
    aveSolutionEA = fopen('./Results_compare/aveSolutionEA.txt', 'wt');
    aveSolutionDE = fopen('./Results_compare/aveSolutionDE.txt', 'wt');
    aveSolutionPSO = fopen('./Results_compare/aveSolutionPSO.txt', 'wt');
    stdGBO = fopen('./Results_compare/stdGBO.txt', 'wt');
    stdEA = fopen('./Results_compare/stdEA.txt', 'wt');
    stdDE = fopen('./Results_compare/stdDE.txt', 'wt');
    stdPSO = fopen('./Results_compare/stdPSO.txt', 'wt');
    clockGBO = fopen('./Results_compare/clockGBO.txt', 'wt');
    clockEA = fopen('./Results_compare/clockEA.txt', 'wt');
    clockDE = fopen('./Results_compare/clockDE.txt', 'wt');
    clockPSO = fopen('./Results_compare/clockPSO.txt', 'wt');

    last = gen * ones(1, 2 * benchNum);

    for i = 1:benchNum
        start = 1;
        xstart = 1;
        aveInd = gen;

        GBO = data_GBO(i);
        EA = data_EA(i);
        DE = data_DE(i);
        PSO = data_PSO(i);
        objTask1GBO = mean(GBO.EvBestFitness(Task1, :));
        objTask2GBO = mean(GBO.EvBestFitness(Task2, :));
        objTask1EA = mean(EA.EvBestFitness(Task1, :));
        objTask2EA = mean(EA.EvBestFitness(Task2, :));
        objTask1DE = mean(DE.EvBestFitness(Task1, :));
        objTask2DE = mean(DE.EvBestFitness(Task2, :));
        objTask1PSO = mean(PSO.EvBestFitness(Task1, :));
        objTask2PSO = mean(PSO.EvBestFitness(Task2, :));

        bestTask1GBO = min(min(GBO.EvBestFitness(Task1, :)));
        bestTask2GBO = min(min(GBO.EvBestFitness(Task2, :)));
        aveTask1GBO = objTask1GBO(aveInd);
        aveTask2GBO = objTask2GBO(aveInd);
        stdTaskGBO = GBO.EvBestFitness(:, aveInd);
        stdTask1GBO = std(stdTaskGBO(Task1, :));
        stdTask2GBO = std(stdTaskGBO(Task2, :));

        bestTask1EA = min(min(EA.EvBestFitness(Task1, :)));
        bestTask2EA = min(min(EA.EvBestFitness(Task2, :)));
        aveTask1EA = objTask1EA(aveInd);
        aveTask2EA = objTask2EA(aveInd);
        stdTaskEA = EA.EvBestFitness(:, aveInd);
        stdTask1EA = std(stdTaskEA(Task1, :));
        stdTask2EA = std(stdTaskEA(Task2, :));

        bestTask1DE = min(min(DE.EvBestFitness(Task1, :)));
        bestTask2DE = min(min(DE.EvBestFitness(Task2, :)));
        aveTask1DE = objTask1DE(aveInd);
        aveTask2DE = objTask2DE(aveInd);
        stdTaskDE = DE.EvBestFitness(:, aveInd);
        stdTask1DE = std(stdTaskDE(Task1, :));
        stdTask2DE = std(stdTaskDE(Task2, :));

        bestTask1PSO = min(min(PSO.EvBestFitness(Task1, :)));
        bestTask2PSO = min(min(PSO.EvBestFitness(Task2, :)));
        aveTask1PSO = objTask1PSO(aveInd);
        aveTask2PSO = objTask2PSO(aveInd);
        stdTaskPSO = PSO.EvBestFitness(:, aveInd);
        stdTask1PSO = std(stdTaskPSO(Task1, :));
        stdTask2PSO = std(stdTaskPSO(Task2, :));

        aveClockGBO = mean(GBO.wall_clock_time());
        aveClockEA = mean(EA.wall_clock_time());
        aveClockDE = mean(DE.wall_clock_time());
        aveClockPSO = mean(PSO.wall_clock_time());

        fprintf(bestSolutionGBO, '%f\n', bestTask1GBO);
        fprintf(bestSolutionGBO, '%f\n', bestTask2GBO);
        fprintf(bestSolutionEA, '%f\n', bestTask1EA);
        fprintf(bestSolutionEA, '%f\n', bestTask2EA);
        fprintf(bestSolutionDE, '%f\n', bestTask1DE);
        fprintf(bestSolutionDE, '%f\n', bestTask2DE);
        fprintf(bestSolutionPSO, '%f\n', bestTask1PSO);
        fprintf(bestSolutionPSO, '%f\n', bestTask2PSO);

        fprintf(aveSolutionGBO, '%f\n', aveTask1GBO);
        fprintf(aveSolutionGBO, '%f\n', aveTask2GBO);
        fprintf(aveSolutionEA, '%f\n', aveTask1EA);
        fprintf(aveSolutionEA, '%f\n', aveTask2EA);
        fprintf(aveSolutionDE, '%f\n', aveTask1DE);
        fprintf(aveSolutionDE, '%f\n', aveTask2DE);
        fprintf(aveSolutionPSO, '%f\n', aveTask1PSO);
        fprintf(aveSolutionPSO, '%f\n', aveTask2PSO);

        fprintf(stdGBO, '%f\n', stdTask1GBO);
        fprintf(stdGBO, '%f\n', stdTask2GBO);
        fprintf(stdEA, '%f\n', stdTask1EA);
        fprintf(stdEA, '%f\n', stdTask2EA);
        fprintf(stdDE, '%f\n', stdTask1DE);
        fprintf(stdDE, '%f\n', stdTask2DE);
        fprintf(stdPSO, '%f\n', stdTask1PSO);
        fprintf(stdPSO, '%f\n', stdTask2PSO);

        fprintf(clockGBO, '%f\n', aveClockGBO);
        fprintf(clockEA, '%f\n', aveClockEA);
        fprintf(clockDE, '%f\n', aveClockDE);
        fprintf(clockPSO, '%f\n', aveClockPSO);

        h1 = figure(1);

        plot(x(xstart:last(2 * i - 1)), objTask1GBO(start:last(2 * i - 1)), 'r', 'Linewidth', 1);
        hold on;
        plot(x(xstart:last(2 * i - 1)), objTask1EA(start:last(2 * i - 1)), 'y', 'Linewidth', 1);
        hold on;
        plot(x(xstart:last(2 * i - 1)), objTask1DE(start:last(2 * i - 1)), 'g', 'Linewidth', 1);
        hold on;
        plot(x(xstart:last(2 * i - 1)), objTask1PSO(start:last(2 * i - 1)), 'b', 'Linewidth', 1);
        hold on;

        title(['T1', ' ', 'in', ' ', char(taskName1(i))]);
        t1 = legend('MFGBO', 'MFEA', 'MFDE', 'MFPSO');
        xlabel('Generation');
        ylabel('Fitness');
        axis([xstart last(2 * i - 1) -inf inf]);
        set(t1, 'Fontsize', 20);
        set(gca, 'Fontsize', 16);

        h2 = figure(2);
        plot(x(xstart:last(2 * i)), objTask2GBO(start:last(2 * i)), 'r', 'Linewidth', 1.5);
        hold on;
        plot(x(xstart:last(2 * i)), objTask2EA(start:last(2 * i)), 'y', 'Linewidth', 1.5);
        hold on;
        plot(x(xstart:last(2 * i)), objTask2DE(start:last(2 * i)), 'g', 'Linewidth', 1.5);
        hold on;
        plot(x(xstart:last(2 * i)), objTask2PSO(start:last(2 * i)), 'b', 'Linewidth', 1.5);
        hold on

        title(['T2', ' ', 'in', ' ', char(taskName1(i))]);
        t2 = legend('MFGBO', 'MFEA', 'MFDE', 'MFPSO');
        xlabel('Generation');
        ylabel('Fitness');
        axis([xstart last(2 * i) -inf inf]);
        set(t2, 'Fontsize', 20);
        set(gca, 'Fontsize', 16);
        outPath0 = ['./Results_compare/', char(taskName(i)), '1.png'];
        outPath1 = ['./Results_compare/', char(taskName(i)), '2.png'];
        print(h1, '-dpng', outPath0);
        print(h2, '-dpng', outPath1);
        close(h1);
        close(h2);
    end

end
