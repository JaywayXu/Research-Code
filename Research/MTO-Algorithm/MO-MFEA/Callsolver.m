% Note that this trial version of the MO-MFEA (which is based on NSGA-II) handles upto 2 "continuous" multi-objective
% optimization tasks concurrently. Further, this code is tested for upto 3
% objective functions per task.

% Default Parameter Settings and genetic operators provided/implemented herein are in accordance with the paper
% "Multi-Objective Multifactorial Optimization in Evolutionary
% Multitasking" published in IEEE Trans. Cybernetics, 2016.

% This implementation assumes a simple random-key encoding scheme with a
% straightforward decoding mechanism as described in "Multi-Objective Multifactorial Optimization in Evolutionary
% Multitasking" published in IEEE Trans. Cybernetics, and "Multifactorial
% Evolution: Towards Evolutionary Multitasking", published in IEEE Trans.
% TEVC. More sophisticated unified representation schemes, decoding
% mechanisms, genetic operators, etc., may be implemented in a simple manner for real-world problems
% where relevant domain knowledge is available.

% Note that the mat file M.mat contains a randomly generated rotation matrix of size 9x9.

% Note that the mat file data.mat contains the Pareto Front of the ZDT4
% family of problems.

% For any bugs identified or future suggestions, please contact Abhishek
% Gupta at abhishekg@ntu.edu.sg

%% Instance 1: ZDT4-R,ZDT4-G
% clear all
% load M % Rotation Matrix
% load data % Known PF data of test function
% for run = 1:1
%     f1='ZDT4-R';
%     % Assigning upper and lower bounds of search space of task 1
%     L1=-5*ones(1,10);
%     U1=5*ones(1,10);
%     L1(1)=0;U1(1)=1;
%     pop1=50;% Population size for task 1
%     f2='ZDT4-G';
%     % Assigning upper and lower bounds of search space of task 2
%     L2=-512*ones(1,10);
%     U2=512*ones(1,10);
%     L2(1)=0;U2(1)=1;
%     pop2=50; % Population size for task 2
%     rmp=1; % Random mating probability
%     gen = 250; % Maximum Number of generations
%     muc = 10; % Distribution Index of SBX crossover operator
%     mum = 10; % Distribution Index of Polynomial Mutation operator
%     prob_vswap = 0; % Probability that certain pair of variables are swapped (uniform crossover-like) during SBX crossover. Change to prob_swap = 0.5 for enhanced global search at the cost of high chromosome disruption.
%     store_Instance1(run).data = MOMFEA_v1(L1,U1,f1,pop1,L2,U2,f2,pop2,rmp,M,gen,muc,mum,prob_vswap,data);
% end
% save('store_Instance1','store_Instance1');

%% Instance 2: ZDT4-RC,ZDT4-A
clear all
load M % Rotation Matrix
load data % Known PF data of test function

for run = 1:1
    f1 = 'ZDT4-RC';
    % Assigning upper and lower bounds of search space of task 1
    L1 = -5 * ones(1, 10);
    U1 = 5 * ones(1, 10);
    L1(1) = 0; U1(1) = 1;
    pop1 = 50; % Population size for task 1
    f2 = 'ZDT4-A';
    % Assigning upper and lower bounds of search space of task 2
    L2 = -32 * ones(1, 10);
    U2 = 32 * ones(1, 10);
    L2(1) = 0; U2(1) = 1;
    pop2 = 50; % Population size for task 2
    rmp = 1; % Random mating probability
    gen = 250; % Maximum Number of generations
    muc = 10; % Distribution Index of SBX crossover operator
    mum = 10; % Distribution Index of Polynomial Mutation operator
    prob_vswap = 0; % Probability that certain pair of variables are swapped (uniform crossover-like) during SBX crossover. Change to prob_swap = 0.5 for enhanced global search at the cost of high chromosome disruption.
    store_Instance2(run).data = MOMFEA_v1(L1, U1, f1, pop1, L2, U2, f2, pop2, rmp, M, gen, muc, mum, prob_vswap, data);
end

save('store_Instance2', 'store_Instance2');
