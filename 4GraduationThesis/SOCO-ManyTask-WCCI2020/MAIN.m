pop_M = 200; % population size
pop_S = 50;
gen = 500; % generation count
rmp = 0.3; % random mating probability
pr = 0.5; % Probability Parameter
reps = 30; % repetitions
benchmark_num = 10;
task_num = 50;
is_run = 1; % 是否运行，false则直接读取mat文件

if is_run

    for index = 1:benchmark_num
        disp(['Benchmark: ', num2str(index)]);
        Tasks = benchmark(index);
        % data_MFGBO(index) = MFGBO(Tasks, pop_M, gen, rmp, pr, reps);
        data_MFGBO(index) = MFGBO_2(Tasks, pop_M, gen, rmp, pr, reps);
        for task_i = 1:size(Tasks, 2)
            disp(['SOTask: ', num2str(task_i)]);
            data_SOO(task_i, index) = SOGBO(Tasks(task_i), pop_S, gen, pr, reps);
        end

        % data_MFGA(index) = MFEA(Tasks, pop_M, gen, 'elitist', rmp, reps);
    end

    save('data_MFGBO', 'data_MFGBO');
    % save('data_MFGBO_2', 'data_MFGBO_2');
    save('data_SOO', 'data_SOO');
end

load('data_MFGBO', 'data_MFGBO');
load('data_SOO', 'data_SOO');
convergeTrend(data_MFGBO, data_SOO, reps, gen, benchmark_num, task_num);

% load('data_MFGBO_2', 'data_MFGBO_2');
% convergeTrend_2(data_MFGBO, data_MFGBO_2, reps, gen, benchmark_num, task_num);
