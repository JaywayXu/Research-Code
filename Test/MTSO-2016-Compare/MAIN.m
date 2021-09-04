pop_M = 100; % MF种群数量
gen = 1000; % 最大迭代次数
reps = 20; % 独立重复运行次数 30
% evaNum_M = pop_M * gen; % MF最大评价次数
evaNum_M = Inf;

benchNum = 9; % 测试集数量 9
taskNum = 2; % 任务数量 2
rmp = 0.3; % random mating probability

is_run = 1; % 是否运行，false则直接读取mat文件

benchNameList = {'CI-HS', 'CI-MS', 'CI-LS', 'PI-HS', 'PI-MS', 'PI-LS', 'NI-HS', 'NI-MS', 'NI-LS'};
algoList = {'MFEA', 'MFGBO', 'MFDE', 'MFPSO', 'MFEA_AKT', 'MFEA2'};

for algo_i = 1:length(algoList)
    addpath(['../Algorithm/', algoList{algo_i}, '/']);
end

algoList_test = {'MFEA', 'MFGBO', 'MFDE', 'MFPSO', 'MFEA_AKT', 'MFEA2'};

if is_run
    tStart = tic;

    for bench_i = 1:benchNum
        disp(['Benchmark: ', benchNameList{bench_i}])
        Tasks = benchmark(bench_i);

        for algo_i = 1:length(algoList_test)

            switch algoList_test{algo_i}
                case 'MFEA'
                    data_MFEA(bench_i) = MFEA(Tasks, pop_M, gen, evaNum_M, 'elitist', rmp, reps);
                case 'MFGBO'
                    data_MFGBO(bench_i) = MFGBO(Tasks, pop_M, gen, evaNum_M, rmp, reps);
                case 'MFDE'
                    data_MFDE(bench_i) = MFDE(Tasks, pop_M, gen, evaNum_M, 'elitist', rmp, reps);
                case 'MFPSO'
                    data_MFPSO(bench_i) = MFPSO(Tasks, pop_M, gen, evaNum_M, rmp, reps);
                case 'MFEA_AKT'
                    data_MFEA_AKT(bench_i) = MFEA_AKT(Tasks, pop_M, gen, evaNum_M, 'elitist', rmp, reps, 8);
                case 'MFEA2'
                    data_MFEA2(bench_i) = MFEA2(Tasks, pop_M, gen, evaNum_M, 'elitist', reps);
            end

        end

    end

    disp(['本次实验共计用时: ', char(duration([0, 0, toc(tStart)]))]);

    mkdir('./Data/');

    for algo_i = 1:length(algoList_test)
        save(['./Data/data_', algoList_test{algo_i}], ['data_', algoList_test{algo_i}]);
    end

end

saveCompare(algoList_test, benchNameList, reps, taskNum, gen);
