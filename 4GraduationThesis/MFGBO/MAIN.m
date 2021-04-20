pop_M = 100; % population size 100
pop_S = pop_M;
gen = 1000; % generation count 1000
selection_pressure = 'elitist'; % choose either 'elitist' or 'roulette wheel'
p_il = 0; % probability of individual learning (BFGA quasi-Newton Algorithm) --> Indiviudal Learning is an IMPORTANT component of the MFGBO.
rmp = 0.3; % random mating probability
reps = 20; % repetitions 20

for index = 1:9
    Tasks = benchmark(index);
    data_MFGBO(index) = MFGBO(Tasks, pop_M, gen, selection_pressure, rmp, p_il, reps);

    % "task_for_comparison_with_SOO" compares performance of corresponding task in MFO with SOO.
    % For Instance, In EXAMPLE 1 ...
    % "task_for_comparison_with_SOO" = 1 --> compares 40-D Rastrin in MFO with 40-D
    % Rastrigin in SOO.
    % "task_for_comparison_with_SOO" = 2 --> compares 30D Ackley in MFO with
    % 30D Ackley in SOO.
    task_for_comparison_with_SOO = 1;
    data_SOO_1(index) = SOGBO(Tasks(task_for_comparison_with_SOO), pop_S, gen / 2, selection_pressure, p_il, reps);

    task_for_comparison_with_SOO = 2;
    data_SOO_2(index) = SOGBO(Tasks(task_for_comparison_with_SOO), pop_S, gen / 2, selection_pressure, p_il, reps);
end

save('result.mat', 'data_MFGBO', 'data_SOO_1', 'data_SOO_2');
