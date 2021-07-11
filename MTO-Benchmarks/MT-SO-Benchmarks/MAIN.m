% This MATLAB R2014b code is for EVOLUTIONARY MULTITASKING across minimization problems. 
% For maximization problems, multiply objective function by -1.

% Settings of simulated binary crossover (SBX) in this code is Pc = 1, 
% and probability of variable sawpping = 0. 

% For suggestions please contact: Bingshui Da (Email: da0002ui@e.ntu.edu.sg)

%% Calling the solvers
% For large population sizes, consider using the Parallel Computing Toolbox
% of MATLAB.
% Else, program can be slow.
pop_M=100; % population size 100
pop_S = pop_M;
gen=1000; % generation count 1000
selection_pressure = 'elitist'; % choose either 'elitist' or 'roulette wheel'
p_il = 0; % probability of individual learning (BFGA quasi-Newton Algorithm) --> Indiviudal Learning is an IMPORTANT component of the MFEA.
rmp=0.3; % random mating probability
reps = 20; % repetitions 20
for index = 1:9
    Tasks = benchmark(index);
    data_MFEA(index)=MFEA(Tasks,pop_M,gen,selection_pressure,rmp,p_il,reps);   

    % "task_for_comparison_with_SOO" compares performance of corresponding task in MFO with SOO.
    % For Instance, In EXAMPLE 1 ...
    % "task_for_comparison_with_SOO" = 1 --> compares 40-D Rastrin in MFO with 40-D
    % Rastrigin in SOO.
    % "task_for_comparison_with_SOO" = 2 --> compares 30D Ackley in MFO with
    % 30D Ackley in SOO.
    task_for_comparison_with_SOO = 1;
    data_SOO_1(index)=SOEA(Tasks(task_for_comparison_with_SOO),pop_S,gen/2,selection_pressure,p_il,reps);   

    task_for_comparison_with_SOO = 2;
    data_SOO_2(index)=SOEA(Tasks(task_for_comparison_with_SOO),pop_S,gen/2,selection_pressure,p_il,reps);     
end

save('result.mat','data_MFEA', 'data_SOO_1', 'data_SOO_2');
