
pop_M=100; % population size 100
pop_S = pop_M;
gen=1000; % generation count 1000
selection_pressure = 'elitist'; % choose either 'elitist' or 'roulette wheel'
p_il = 0; % probability of individual learning (BFGA quasi-Newton Algorithm) --> Indiviudal Learning is an IMPORTANT component of the MFEA.
rmp=0.3; % random mating probability
reps=20; % repetitions 20

cxname={'sp','tp','uf','ari','blxa','sbx','geo','adpt'};
for ncx=8:8 %ncx: number of crossover
    disp(cxname{ncx});
    for index =1:9
        disp(['p',num2str(index)]);
        Tasks = benchmark(index);
        OX_MFEA(index)=MFEA(Tasks,pop_M,gen,selection_pressure,rmp,p_il,reps,ncx);
      
%          task_for_comparison_with_SOO = 1;
%          data_SOO_1(index)=SOEA(Tasks(task_for_comparison_with_SOO),pop_S,gen/2,selection_pressure,p_il,reps,ncx);
%          
%          task_for_comparison_with_SOO = 2;
%          data_SOO_2(index)=SOEA(Tasks(task_for_comparison_with_SOO),pop_S,gen/2,selection_pressure,p_il,reps,ncx);
    end
end

