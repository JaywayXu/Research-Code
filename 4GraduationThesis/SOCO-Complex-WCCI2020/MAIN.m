pop_M = 200; % population size
pop_S = 100;
gen = 500; % generation count
rmp = 0.3; % random mating probability
pr = 0.5; % Probability Parameter
reps = 2; % repetitions
benchmark_num = 10;
is_run = 1; % 是否运行，false则直接读取mat文件

if is_run

    for index = 1:benchmark_num
        disp(['Benchmark: ', num2str(index)])
        Tasks = benchmark(index);
        data_MFGBO(index) = MFGBO(Tasks, pop_M, gen, rmp, pr, reps);
        data_MFGBO_2(index) = MFGBO_2(Tasks, pop_M, gen, rmp, pr, reps);
        % for task_i = 1:size(Tasks, 2)
        %     disp(['SOTask: ', num2str(task_i)]);
        %     data_SOO(task_i, index) = SOGBO(Tasks(task_i), pop_S, gen, pr, reps);
        % end

        % data_GA(index) = MFEA(Tasks, pop_M, gen, 'elitist', rmp, reps);
        % data_DE(index) = MFDE(Tasks, pop_M, gen, 'elitist', rmp, reps);
        % data_PSO(index) = MFPSO(Tasks, pop_M, gen, rmp, reps);
    end

    save('data_MFGBO', 'data_MFGBO');
    save('data_MFGBO_2', 'data_MFGBO_2');
    % save('data_SOO', 'data_SOO');
    % save('data_GA', 'data_GA');
    % save('data_DE', 'data_DE');
    % save('data_PSO', 'data_PSO');
end

load('data_MFGBO', 'data_MFGBO');
load('data_MFGBO_2', 'data_MFGBO_2');
% load('data_SOO', 'data_SOO');
% load('data_GA', 'data_GA');
% load('data_DE', 'data_DE');
% load('data_PSO', 'data_PSO');
% convergeTrend(data_MFGBO, data_SOO, reps, gen, benchmark_num, 2);
% convergeTrend_compare(data_MFGBO, data_GA, data_DE, data_PSO, reps, gen, benchmark_num, 2)
convergeTrend_2(data_MFGBO, data_MFGBO_2, reps, gen, benchmark_num, 2)
