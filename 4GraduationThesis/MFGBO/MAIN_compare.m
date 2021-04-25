pop_M = 100; % population size 100
pop_S = pop_M;
gen = 500; % generation count 1000
p_il = 0; % probability of individual learning (BFGA quasi-Newton Algorithm) --> Indiviudal Learning is an IMPORTANT component of the MFGBO.
rmp = 0.3; % random mating probability
pr = 0.5; % Probability Parameter
reps = 30; % repetitions 20

benchmark_num = 9;
is_run = true; % 是否运行，false则直接读取mat文件

if is_run

    for index = 1:benchmark_num
        disp(['Benchmark: ', num2str(index)])
        Tasks = benchmark(index);
        data_GBO(index) = MFGBO(Tasks, pop_M, gen, rmp, pr, p_il, reps);
        data_EA(index) = MFEA(Tasks, pop_M, gen, 'elitist', rmp, p_il, reps);
        data_DE(index) = MFDE(Tasks, pop_M, gen, 'elitist', rmp, p_il, reps);
        data_PSO(index) = MFPSO(Tasks, pop_M, gen, rmp, p_il, reps);
    end

    % draw
    save('data_GBO', 'data_GBO');
    save('data_EA', 'data_EA');
    save('data_DE', 'data_DE');
    save('data_PSO', 'data_PSO');
end

save('data_GBO', 'data_GBO');
save('data_EA', 'data_EA');
save('data_DE', 'data_DE');
save('data_PSO', 'data_PSO')
convergeTrend_compare(data_GBO, data_EA, data_DE, data_PSO, reps, gen, benchmark_num)
