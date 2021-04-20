% This MATLAB R2014b code is for EVOLUTIONARY MULTITASKING across minimization problems.
% For maximization problems, multiply objective function by -1.

% For suggestions please contact: Wei Zhou (Email: jerryzhou@cqu.edu.cn)

%% Calling the solvers
% For large population sizes, consider using the Parallel Computing Toolbox
% of MATLAB.
% Else, program can be slow.
pop_M = 100; % population size 100
pop_S = pop_M;
gen = 500; % generation count 1000
selection_pressure = 'elitist'; % choose either 'elitist' or 'roulette wheel'
p_il = 0; % probability of individual learning (BFGA quasi-Newton Algorithm) --> Indiviudal Learning is an IMPORTANT component of the MFDE.
rmp = 0.3; % random mating probability
reps = 20; % repetitions 20

benchmark_num = 9;

is_run = true; % 是否运行，false则直接读取mat文件

if is_run

    for index = 1:benchmark_num
        Tasks = benchmark(index);
        data_MFDE(index) = MFDE(Tasks, pop_M, gen, selection_pressure, rmp, p_il, reps, index);

        % "task_for_comparison_with_SOO" compares performance of corresponding task in MFO with SOO.
        % For Instance, In EXAMPLE 1 ...
        % "task_for_comparison_with_SOO" = 1 --> compares 40-D Rastrin in MFO with 40-D
        % Rastrigin in SOO.
        % "task_for_comparison_with_SOO" = 2 --> compares 30D Ackley in MFO with
        % 30D Ackley in SOO.
        task_for_comparison_with_SOO = 1;
        data_SOO_1(index) = SOEA(Tasks(task_for_comparison_with_SOO), pop_S, gen, selection_pressure, p_il, reps);

        task_for_comparison_with_SOO = 2;
        data_SOO_2(index) = SOEA(Tasks(task_for_comparison_with_SOO), pop_S, gen, selection_pressure, p_il, reps);
    end

    % draw
    save('data_MFDE', 'data_MFDE');
    save('data_SOO_1', 'data_SOO_1');
    save('data_SOO_2', 'data_SOO_2');
end

load('data_MFDE', 'data_MFDE');
load('data_SOO_1', 'data_SOO_1');
load('data_SOO_2', 'data_SOO_2');
convergeTrend(data_MFDE, data_SOO_1, data_SOO_2, reps, gen, benchmark_num)
