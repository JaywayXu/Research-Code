pop_M = 100; % population size
pop_S = pop_M;
gen = 500; % generation count
p_il = 0; % probability of individual learning (BFGA quasi-Newton Algorithm) --> Indiviudal Learning is an IMPORTANT component of the MFGBO.
rmp = 0.3; % random mating probability
pr = 0.5; % Probability Parameter
reps = 30; % repetitions
benchmark_num = 9;
is_run = 1; % 是否运行，false则直接读取mat文件

if is_run

    for index = 1:benchmark_num
        disp(['Benchmark: ', num2str(index)])
        Tasks = benchmark(index);
        data_MFGBO(index) = MFGBO(Tasks, pop_M, gen, rmp, pr, p_il, reps);

        for task_i = 1:size(Tasks, 2)
            disp(['SOTask: ', num2str(task_i)]);
            data_SOO(task_i, index) = SOGBO(Tasks(task_i), pop_S, gen, pr, p_il, reps);
        end

        data_GA(index) = MFEA(Tasks, pop_M, gen, 'elitist', rmp, p_il, reps);
        data_DE(index) = MFDE(Tasks, pop_M, gen, 'elitist', rmp, p_il, reps);
        data_PSO(index) = MFPSO(Tasks, pop_M, gen, rmp, p_il, reps);
    end

    save('data_MFGBO', 'data_MFGBO');
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
convergeTrend(data_MFGBO, data_SOO, reps, gen, benchmark_num, 2);
convergeTrend_compare(data_MFGBO, data_GA, data_DE, data_PSO, reps, gen, benchmark_num, 2);