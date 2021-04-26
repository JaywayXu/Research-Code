pop_M = 100; % population size 100
pop_S = pop_M;
gen = 500; % generation count 1000
p_il = 0; % probability of individual learning (BFGA quasi-Newton Algorithm) --> Indiviudal Learning is an IMPORTANT component of the MFGBO.
rmp = 0.3; % random mating probability
pr = 0.5; % Probability Parameter
reps = 30; % repetitions 20

benchmark_num = 9;
is_run = false; % 是否运行，false则直接读取mat文件

if is_run

    for index = 1:benchmark_num
        disp(['Benchmark: ', num2str(index)])
        Tasks = benchmark(index);
        data_MFGBO(index) = MFGBO(Tasks, pop_M, gen, rmp, pr, p_il, reps);

        % "task_for_comparison_with_SOO" compares performance of corresponding task in MFO with SOO.
        % For Instance, In EXAMPLE 1 ...
        % "task_for_comparison_with_SOO" = 1 --> compares 40-D Rastrin in MFO with 40-D
        % Rastrigin in SOO.
        % "task_for_comparison_with_SOO" = 2 --> compares 30D Ackley in MFO with
        % 30D Ackley in SOO.
        task_for_comparison_with_SOO = 1;
        data_SOO_1(index) = SOGBO(Tasks(task_for_comparison_with_SOO), pop_S, gen, pr, p_il, reps);

        task_for_comparison_with_SOO = 2;
        data_SOO_2(index) = SOGBO(Tasks(task_for_comparison_with_SOO), pop_S, gen, pr, p_il, reps);

        data_EA(index) = MFEA(Tasks, pop_M, gen, 'elitist', rmp, p_il, reps);
        data_DE(index) = MFDE(Tasks, pop_M, gen, 'elitist', rmp, p_il, reps);
        data_PSO(index) = MFPSO(Tasks, pop_M, gen, rmp, p_il, reps);
    end

    % draw
    save('data_MFGBO', 'data_MFGBO');
    save('data_SOO_1', 'data_SOO_1');
    save('data_SOO_2', 'data_SOO_2');
    save('data_EA', 'data_EA');
    save('data_DE', 'data_DE');
    save('data_PSO', 'data_PSO');
end

load('data_MFGBO', 'data_MFGBO');
load('data_SOO_1', 'data_SOO_1');
load('data_SOO_2', 'data_SOO_2');
load('data_EA', 'data_EA');
load('data_DE', 'data_DE');
load('data_PSO', 'data_PSO');
convergeTrend(data_MFGBO, data_SOO_1, data_SOO_2, reps, gen, benchmark_num);
convergeTrend_compare(data_MFGBO, data_EA, data_DE, data_PSO, reps, gen, benchmark_num);