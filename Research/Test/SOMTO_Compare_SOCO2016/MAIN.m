pop_M = 100; % MF种群数量
gen = 1000; % 最大迭代次数
benchmark_num = 9; % 测试集数量 9
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
        data_MFEA_AKT(index) = MFEA_AKT(Tasks, pop_M, gen, eva_num_M, 'elitist', rmp, reps);
        data_MFEA(index) = MFEA(Tasks, pop_M, gen, eva_num_M, 'elitist', rmp, reps);
        data_MFGBO(index) = MFGBO(Tasks, pop_M, gen, eva_num_M, rmp, reps);
        data_MFDE(index) = MFDE(Tasks, pop_M, gen, eva_num_M, 'elitist', rmp, reps);
        data_MFPSO(index) = MFPSO(Tasks, pop_M, gen, eva_num_M, rmp, reps);
    end

    save('data_MFEA_AKT', 'data_MFEA_AKT');
    save('data_MFEA', 'data_MFEA');
    save('data_MFGBO', 'data_MFGBO');
    save('data_MFDE', 'data_MFDE');
    save('data_MFPSO', 'data_MFPSO');
end

% load('data_MFEA_AKT', 'data_MFEA_AKT');
% load('data_MFEA', 'data_MFEA');
% load('data_MFGBO', 'data_MFGBO');
% load('data_MFDE', 'data_MFDE');
% load('data_MFPSO', 'data_MFPSO');
% saveCompare(data_MFGBO, data_GA, data_DE, data_PSO, reps, benchmark_num, task_num);
