pop_M = 100; % MF种群数量
pop_S = pop_M; % SO种群数量
gen = 500; % 最大迭代次数
benchmark_num = 10; % 测试集数量 10
task_num = 2; % 任务数量 2
eva_num_M = pop_M * gen; % MF最大评价次数
eva_num_S = eva_num_M / task_num; % SO最大评价次数
reps = 20; % 独立重复运行次数 30
is_run = 1; % 是否运行，false则直接读取mat文件

rmp = 0.3; % random mating probability

if is_run

    for index = 1:benchmark_num
        disp(['Benchmark: ', num2str(index)])
        Tasks = benchmark(index);
        data_MFGBO(index) = MFGBO(Tasks, pop_M, gen, eva_num_M, rmp, reps);
        % data_MFGBO_2(index) = MFGBO_2Tasks, pop_M, gen, eva_num_M, rmp, reps);

        for task_i = 1:size(Tasks, 2)
            disp(['SOTask: ', num2str(task_i)]);
            data_SOO(task_i, index) = SOGBO(Tasks(task_i), pop_S, gen, eva_num_S, reps);
        end

        data_GA(index) = MFEA(Tasks, pop_M, gen, eva_num_M, 'elitist', rmp, reps);
        data_DE(index) = MFDE(Tasks, pop_M, gen, eva_num_M, 'elitist', rmp, reps);
        data_PSO(index) = MFPSO(Tasks, pop_M, gen, eva_num_M, rmp, reps);
    end

    save('data_MFGBO', 'data_MFGBO');
    % save('data_MFGBO_2', 'data_MFGBO_2');
    save('data_SOO', 'data_SOO');
    save('data_GA', 'data_GA');
    save('data_DE', 'data_DE');
    save('data_PSO', 'data_PSO');
end

load('data_MFGBO', 'data_MFGBO');
load('data_SOO', 'data_SOO');
load('data_GA', 'data_GA');
load('data_DE', 'data_DE');
load('data_PSO', 'data_PSO');
saveSOMF(data_MFGBO, data_SOO, reps, benchmark_num, task_num);
saveCompare(data_MFGBO, data_GA, data_DE, data_PSO, reps, benchmark_num, task_num)

% load('data_MFGBO_2', 'data_MFGBO_2');
% convergeTrend_2(data_MFGBO, data_MFGBO_2, reps, gen, benchmark_num, task_num)
