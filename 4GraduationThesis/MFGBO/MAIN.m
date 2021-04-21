pop_M = 100; % population size 100
pop_S = pop_M;
gen = 500; % generation count 1000
p_il = 0; % probability of individual learning (BFGA quasi-Newton Algorithm) --> Indiviudal Learning is an IMPORTANT component of the MFGBO.
rmp = 0.3; % random mating probability
pr = 0.5; % Probability Parameter
reps = 2; % repetitions 20

benchmark_num = 1;
is_run = true; % 是否运行，false则直接读取mat文件

if is_run

    for index = 1:benchmark_num
        Tasks = benchmark(index);
        % TODO
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
    end

    % draw
    save('data_MFGBO', 'data_MFGBO');
    save('data_SOO_1', 'data_SOO_1');
    save('data_SOO_2', 'data_SOO_2');
end

load('data_MFGBO', 'data_MFGBO');
load('data_SOO_1', 'data_SOO_1');
load('data_SOO_2', 'data_SOO_2');
convergeTrend(data_MFGBO, data_SOO_1, data_SOO_2, reps, gen, benchmark_num)
