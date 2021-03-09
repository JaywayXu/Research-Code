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

p_il = 0; % probability of individual learning (BFGA quasi-Newton Algorithm) --> Indiviudal Learning is an IMPORTANT component of the MFEA.
rmp=0.3; % random mating probability
reps = 20; % repetitions 20
for index = 1:9
    Tasks = benchmark(index);
    
    data_MFPSO(index)=MFPSO(Tasks,pop_M,gen,rmp,p_il,reps,index);

%     task_for_comparison_with_SOO = 1;
%     data_SOO_1(index)=PSO(Tasks(task_for_comparison_with_SOO),pop_S,gen,p_il,reps);   
% 
%     task_for_comparison_with_SOO = 2;
%     data_SOO_2(index)=PSO(Tasks(task_for_comparison_with_SOO),pop_S,gen,p_il,reps);     
end

%save('result.mat','data_MFPSO', 'data_SOO_1', 'data_SOO_2');

