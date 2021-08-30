% This basic MATLAB implementation is for the MFEA-II algorithm proposed in the following reference:

%       Bali, K. K., Ong, Y. S., Gupta, A., & Tan, P. S. Multifactorial Evolutionary Algorithm with Online Transfer Parameter Estimation: MFEA-II.
%       IEEE Transactions on Evolutionary Computation, 2019.

% A few toy examples (binary optimization problems) are shown in this demo. The respective functions are defined in the "benchmark.m" file.
% Please refer to the paper (above) for details regarding the  encoding and decoding schemes as well as the appropriate parameter settings.
% This demo can be directly run via this "MAIN.m" file.

% For any bugs or suggestions, please contact: Bali Kavitesh Kumar (Email: bali0001@e.ntu.edu.sg)

%% Calling the solvers
% For large population sizes, consider using the Parallel Computing Toolbox of MATLAB.
% Else, the program can be slow.

clc
clear all;

pop_M = 200; % population size for multitasking
gen = 100; % generation count
selection_pressure = 'elitist'; % choose either 'elitist' or 'roulette wheel'
p_il = 0; % probability of individual learning (BFGA quasi-Newton Algorithm) - local search (optional)
reps = 30; % reps > 1 to compute mean rmp values

problem_set = 1; % The desired problem sets can be chosen from the "benchmark.m" file
Tasks = benchmark(problem_set);
data_MFEA2 = MFEA2(Tasks, pop_M, gen, selection_pressure, p_il, reps);
save('result_MFEA2.mat', 'data_MFEA2');

temp1 = data_MFEA2.EvBestFitness(1:2:end, :);
mean1_MFEA2 = mean(-temp1); % Task 1 mean fitness

temp2 = data_MFEA2.EvBestFitness(2:2:end, :);
mean2_MFEA2 = mean(temp2); % Task 2 mean fitness

rmp_mean = data_MFEA2.rmpMean; % average learned rmp values

save('mean1_MFEA2', 'mean1_MFEA2');
save('mean2_MFEA2', 'mean2_MFEA2');
save('rmp_mean', 'rmp_mean');

%plot(data_MFEA2.rmpMean)
