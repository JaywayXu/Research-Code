function convergeTrend(data_MFPSO, data_SOO_1, data_SOO_2)
    Task1 = [];
    Task2 = [];

    for i = 1:2:40
        Task1 = [Task1, i];
        Task2 = [Task2, i + 1];
    end

    x = [];

    for i = 1:1001
        x = [x, i];
    end

    taskName = {'CI_HS', 'CI_MS', 'CI_LS', 'PI_HS', 'PI_MS', 'PI_LS', 'NI_HS', 'NI_MS', 'NI_LS'};
    taskName1 = {'CI\_HS', 'CI\_MS', 'CI\_LS', 'PI\_HS', 'PI\_MS', 'PI\_LS', 'NI\_HS', 'NI\_MS', 'NI\_LS'};

    bestSolutionMFO = fopen('.\MFPSOResults\bestSolutionMFO.txt', 'wt');
    bestSolutionSO = fopen('.\MFPSOResults\bestSolutionSO.txt', 'wt');
    aveSolutionMFO = fopen('.\MFPSOResults\aveSolutionMFO.txt', 'wt');
    aveSolutionSO = fopen('.\MFPSOResults\aveSolutionSO.txt', 'wt');
    stdMFO = fopen('.\MFPSOResults\stdMFO.txt', 'wt');
    stdSO = fopen('.\MFPSOResults\stdSO.txt', 'wt');
    taskNum = 3;

    last = [600, 1000, 1000, 1000, 1000, 1000, 1000, 300, 1000, 300, 1000, 1000, 300, 1000, 600, 1000, 1000, 1000];
    %last=1000*ones(1,18);
    for i = 1:taskNum
        start = 1;
        step = 50;
        xstart = 1;
        aveInd = 1000;

        MFPSO = data_MFPSO(i);
        SOO_1 = data_SOO_1(i);
        SOO_2 = data_SOO_2(i);
        objTask1MFO = mean(MFPSO.EvBestFitness(Task1, :));
        objTask2MFO = mean(MFPSO.EvBestFitness(Task2, :));
        objTask1SO = mean(SOO_1.EvBestFitness);
        objTask2SO = mean(SOO_2.EvBestFitness);

        bestTask1MFO = min(min(MFPSO.EvBestFitness(Task1, :)));
        bestTask2MFO = min(min(MFPSO.EvBestFitness(Task2, :)));
        aveTask1MFO = objTask1MFO(aveInd);
        aveTask2MFO = objTask2MFO(aveInd);
        stdTaskMFO = MFPSO.EvBestFitness(:, aveInd);
        stdTask1MFO = std(stdTaskMFO(Task1, :));
        stdTask2MFO = std(stdTaskMFO(Task2, :));

        bestTask1SO = min(min(SOO_1.EvBestFitness));
        bestTask2SO = min(min(SOO_2.EvBestFitness));
        aveTask1SO = objTask1SO(aveInd);
        aveTask2SO = objTask2SO(aveInd);
        stdTask1SO = std(SOO_1.EvBestFitness(:, aveInd));
        stdTask2SO = std(SOO_2.EvBestFitness(:, aveInd));

        fprintf(bestSolutionMFO, '%f\n', bestTask1MFO);
        fprintf(bestSolutionMFO, '%f\n', bestTask2MFO);
        fprintf(bestSolutionSO, '%f\n', bestTask1SO);
        fprintf(bestSolutionSO, '%f\n', bestTask2SO);
        fprintf(aveSolutionMFO, '%f\n', aveTask1MFO);
        fprintf(aveSolutionMFO, '%f\n', aveTask2MFO);
        fprintf(aveSolutionSO, '%f\n', aveTask1SO);
        fprintf(aveSolutionSO, '%f\n', aveTask2SO);
        fprintf(stdMFO, '%f\n', stdTask1MFO);
        fprintf(stdMFO, '%f\n', stdTask2MFO);
        fprintf(stdSO, '%f\n', stdTask1SO);
        fprintf(stdSO, '%f\n', stdTask2SO);

        h1 = figure(1);

        plot(x(xstart:xstart), objTask1MFO(start:start), '-ro', 'Linewidth', 2, 'MarkerSize', 8);
        hold on;
        plot(x(xstart:xstart), objTask1SO(start:start), '-bx', 'Linewidth', 2, 'MarkerSize', 8);
        hold on;

        plot(x(xstart:last(2 * i - 1)), objTask1MFO(start:last(2 * i - 1)), 'r', 'Linewidth', 2.5);
        hold on;
        plot(x(xstart:last(2 * i - 1)), objTask1SO(start:last(2 * i - 1)), 'b', 'Linewidth', 2.5);
        hold on;

        plot(x(xstart:last(2 * i - 1) / 20:last(2 * i - 1)), objTask1MFO(start:last(2 * i - 1) / 20:last(2 * i - 1)), 'ro', 'Linewidth', 2, 'MarkerSize', 8);
        hold on;
        plot(x(xstart:last(2 * i - 1) / 20:last(2 * i - 1)), objTask1SO(start:last(2 * i - 1) / 20:last(2 * i - 1)), 'bx', 'Linewidth', 2, 'MarkerSize', 8);
        hold on;
        title(['T1', ' ', 'in', ' ', char(taskName1(i))]);
        t1 = legend('MFDE', 'DE');
        xlabel('Generation');
        ylabel('Fitness');
        axis([xstart last(2 * i - 1) -inf inf]);
        set(t1, 'Fontsize', 20);
        set(gca, 'Fontsize', 16);

        h2 = figure(2);
        plot(x(xstart:xstart), objTask2MFO(start:start), '-ro', 'Linewidth', 2, 'MarkerSize', 8);
        hold on;
        plot(x(xstart:xstart), objTask2SO(start:start), '-bx', 'Linewidth', 2, 'MarkerSize', 8);
        hold on;

        plot(x(xstart:last(2 * i)), objTask2MFO(start:last(2 * i)), 'r', 'Linewidth', 2.5);
        hold on;
        plot(x(xstart:last(2 * i)), objTask2SO(start:last(2 * i)), 'b', 'Linewidth', 2.5);
        hold on;

        plot(x(xstart:last(2 * i) / 20:last(2 * i)), objTask2MFO(start:last(2 * i) / 20:last(2 * i)), 'ro', 'Linewidth', 2, 'MarkerSize', 8);
        hold on;
        plot(x(xstart:last(2 * i) / 20:last(2 * i)), objTask2SO(start:last(2 * i) / 20:last(2 * i)), 'bx', 'Linewidth', 2, 'MarkerSize', 8);
        hold on;
        title(['T2', ' ', 'in', ' ', char(taskName1(i))]);
        t2 = legend('MFDE', 'DE');
        xlabel('Generation');
        ylabel('Fitness');
        axis([xstart last(2 * i) -inf inf]);
        set(t2, 'Fontsize', 20);
        set(gca, 'Fontsize', 16);
        outPath0 = ['.\MFPSOResults\', char(taskName(i)), '1.png'];
        outPath0_1 = ['.\MFPSOResults\', char(taskName(i)), '1.eps'];
        outPath1 = ['.\MFPSOResults\', char(taskName(i)), '2.png'];
        outPath1_1 = ['.\MFPSOResults\', char(taskName(i)), '2.eps'];
        print(h1, '-dpng', outPath0);
        print(h1, '-depsc', outPath0_1);
        print(h2, '-dpng', outPath1);
        print(h2, '-depsc', outPath1_1);
        close(h1);
        close(h2);
    end

    fclose(bestSolutionMFO);
    fclose(bestSolutionSO);
    fclose(aveSolutionMFO);
    fclose(aveSolutionSO);
end
