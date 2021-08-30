pop_M = 100; % MF种群数量
gen = 1000; % 最大迭代次数
reps = 20; % 独立重复运行次数 30
% evaNum_M = pop_M * gen; % MF最大评价次数
evaNum_M = Inf;

benchNum = 9; % 测试集数量 9
taskNum = 2; % 任务数量 2
rmp = 0.3; % random mating probability

is_run = 0; % 是否运行，false则直接读取mat文件

benchNameList = {'CI-HS', 'CI-MS', 'CI-LS', 'PI-HS', 'PI-MS', 'PI-LS', 'NI-HS', 'NI-MS', 'NI-LS'};
% algoNameList = {'MFEA_TwoPoint', ...
%                 'MFEA_Uniform', ...
%                 'MFEA_Arithmetical', ...
%                 'MFEA_Geometric', ...
%                 'MFEA_BLXa', ...
%                 'MFEA_SBX', ...
%                 'MFEA_AKT'};
algoNameList = {'MFEA_AKT', 'MFEA', 'MFGBO', 'MFDE', 'MFPSO'};

if is_run

    for bench_i = 1:benchNum
        disp(['Benchmark: ', num2str(bench_i)])
        Tasks = benchmark(bench_i);
        % MFEA_AKT test
        % data_MFEA_TwoPoint(bench_i) = MFEA_AKT(Tasks, pop_M, gen, evaNum_M, 'elitist', rmp, reps, 2);
        % data_MFEA_Uniform(bench_i) = MFEA_AKT(Tasks, pop_M, gen, evaNum_M, 'elitist', rmp, reps, 3);
        % data_MFEA_Arithmetical(bench_i) = MFEA_AKT(Tasks, pop_M, gen, evaNum_M, 'elitist', rmp, reps, 4);
        % data_MFEA_Geometric(bench_i) = MFEA_AKT(Tasks, pop_M, gen, evaNum_M, 'elitist', rmp, reps, 7);
        % data_MFEA_BLXa(bench_i) = MFEA_AKT(Tasks, pop_M, gen, evaNum_M, 'elitist', rmp, reps, 5);
        % data_MFEA_SBX(bench_i) = MFEA_AKT(Tasks, pop_M, gen, evaNum_M, 'elitist', rmp, reps, 6);
        % data_MFEA_AKT(bench_i) = MFEA_AKT(Tasks, pop_M, gen, evaNum_M, 'elitist', rmp, reps, 8);

        % data_MFEA(bench_i) = MFEA(Tasks, pop_M, gen, evaNum_M, 'elitist', rmp, reps);
        % data_MFGBO(bench_i) = MFGBO(Tasks, pop_M, gen, evaNum_M, rmp, reps);
        % data_MFDE(bench_i) = MFDE(Tasks, pop_M, gen, evaNum_M, 'elitist', rmp, reps);
        % data_MFPSO(bench_i) = MFPSO(Tasks, pop_M, gen, evaNum_M, rmp, reps);
    end

    mkdir('./Data/');

    for algo_i = 1:length(algoNameList)
        save(['./Data/data_', algoNameList{algo_i}], ['data_', algoNameList{algo_i}]);
    end

end

saveCompare(algoNameList, benchNameList, reps, taskNum, gen);
