% This trial version of the Multi-Objective Multifactorial Evolutionary Algorithm (MO-MFEA: which is based on NSGA-II) has been
% developed to handle only two "continuous" multiobjective problems (or tasks) at a time.
% Each problem may comprise upto three objective functions.
% Generalization to many-tasking can be done based on this framework.
function [store]=MOMFEA2(L1,U1,f1,pop1,L2,U2,f2,pop2,pf1,pf2,rmp,M,gen,muc,mum,prob_vswap,prob_xover) 
    
    pop=pop1+pop2;
    if mod(pop,2)~=0
        pop=pop+1;
        pop2=pop2+1;
    end
    
    dim1=length(L1);
    dim2=length(L2);
    dim=max([dim1,dim2]);
   
   % load M
    M1 = M;
    M2 = M;
    
    
    vars=zeros(1,2);
    vars(1) = dim1;
    vars(2) = dim2;
    
       
    store=[];
    
    for i=1:pop
        population(i)=Chromosome;
        population(i)=initialize(population(i),dim);
        if i<=pop1
            population(i).skill_factor=1;
        else
            population(i).skill_factor=2;
        end
    end    
    parfor i=1:pop
        population(i)=evaluate(population(i),L1,U1,f1,L2,U2,f2,dim1,dim2,M1,M2);
    end        
    population_T1=population([population.skill_factor]==1);
    population_T2=population([population.skill_factor]==2);
    no_of_objs_T1 = length(population_T1(1).objs_T1);
    no_of_objs_T2 = length(population_T2(1).objs_T2);
    [population_T1,frontnumbers]=SolutionComparison.nondominatedsort(population_T1,pop1,no_of_objs_T1);
    [population_T1,~]=SolutionComparison.diversity(population_T1,frontnumbers,pop1,no_of_objs_T1);
    [population_T2,frontnumbers]=SolutionComparison.nondominatedsort(population_T2,pop2,no_of_objs_T2);
    [population_T2,~]=SolutionComparison.diversity(population_T2,frontnumbers,pop2,no_of_objs_T2);
    population(1:pop1) = population_T1;
    population(pop1+1:pop) = population_T2;
    
    for generation=1:gen       
        rndlist=randperm(pop);
        population=population(rndlist);
        for i = 1:pop % Performing binary tournament selection to create parent pool
            parent(i)=Chromosome();
            p1=1+round(rand(1)*(pop-1));
            p2=1+round(rand(1)*(pop-1));
            if population(p1).rank < population(p2).rank
                parent(i).rnvec=population(p1).rnvec;
                parent(i).skill_factor=population(p1).skill_factor;
            elseif population(p1).rank == population(p2).rank
                if rand(1) <= 0.5
                    parent(i).rnvec=population(p1).rnvec;
                    parent(i).skill_factor=population(p1).skill_factor;
                else
                    parent(i).rnvec=population(p2).rnvec;
                    parent(i).skill_factor=population(p2).skill_factor;
                end
            else
                parent(i).rnvec=population(p2).rnvec;
                parent(i).skill_factor=population(p2).skill_factor;
            end
        end
        
      
        % Extract task specific data sets for building probabilistic models
        % and learning the RMP matrix
            for i = 1:2
                subpops(i).data = [];
            end
  
             for i = 1:pop
                 subpops(parent(i).skill_factor).data = [subpops(parent(i).skill_factor).data;parent(i).rnvec];
             end
             

            RMP = learnRMP(subpops,vars); % learning RMP matrix online at every generation.
            rmp = RMP(1,2);
        
        count=1;
        for i=1:2:pop-1 % Create offspring population via mutation and crossover
            child(count)=Chromosome;
            child(count+1)=Chromosome;
            p1=i;
            p2=i+1;
            if parent(p1).skill_factor==parent(p2).skill_factor
                [child(count).rnvec,child(count+1).rnvec]=Evolve.crossover(parent(p1).rnvec,parent(p2).rnvec,muc,dim,prob_vswap,prob_xover);
                child(count).rnvec = Evolve.mutate(child(count).rnvec,mum,dim,1/dim);
                child(count+1).rnvec=Evolve.mutate(child(count+1).rnvec,mum,dim,1/dim);
                child(count).skill_factor=parent(p1).skill_factor;
                child(count+1).skill_factor=parent(p2).skill_factor;
            else
                if rand(1)<rmp
                    prob_vswap = 0; 
                    [child(count).rnvec,child(count+1).rnvec]= Evolve.crossover(parent(p1).rnvec,parent(p2).rnvec,muc,dim,prob_vswap,prob_xover); 
                    child(count).rnvec = Evolve.mutate(child(count).rnvec,mum,dim,1/dim);
                    child(count+1).rnvec=Evolve.mutate(child(count+1).rnvec,mum,dim,1/dim);
                    child(count).skill_factor=round(rand(1))+1;
                    child(count+1).skill_factor=round(rand(1))+1;
                else

                   % Randomly pick another individual from the  same task
                   % for Crossover (SBX + uniform)  + Mutate

                           %select another unique individual p11 having the same skill factor as p1
                           sol1 = find([parent.skill_factor] == parent(p1).skill_factor);
                           c1 = numel(sol1);
                           idx1 = randi(c1);    
                           p11 = sol1(idx1);

                           while (p11 == p1)
                               idx1 = randi(c1);
                               p11 = sol1(idx1);
                           end
                           
                           %select another unique individual p22 having the same skill factor as p2
                           sol2 = find([parent.skill_factor] == parent(p2).skill_factor);
                           c2 = numel(sol2);
                           idx2 = randi(c2);
                           p22 = sol2(idx2);

                           while (p22 == p2)
                               idx2 = randi(c2);
                               p22 = sol2(idx2);
                           end
                           
                           [child(count).rnvec,~]= Evolve.crossover(parent(p1).rnvec,parent(p11).rnvec,muc,dim,prob_vswap,prob_xover);
                           child(count).rnvec = Evolve.mutate(child(count).rnvec,mum,dim,1/dim);
                           child(count).skill_factor=parent(p1).skill_factor;
                           
                           [child(count+1).rnvec,~]= Evolve.crossover(parent(p2).rnvec,parent(p22).rnvec,muc,dim,prob_vswap,prob_xover);
                           child(count+1).rnvec = Evolve.mutate(child(count+1).rnvec,mum,dim,1/dim);
                           child(count+1).skill_factor=parent(p2).skill_factor;


                end
            end
            count=count+2;
        end        
        parfor i=1:pop
            child(i)=evaluate(child(i),L1,U1,f1,L2,U2,f2,dim1,dim2,M1,M2);
        end
        population=reset(population,pop);
        intpopulation(1:pop)=population;
        intpopulation(pop+1:2*pop)=child;
        intpopulation_T1=intpopulation([intpopulation.skill_factor]==1);
        intpopulation_T2=intpopulation([intpopulation.skill_factor]==2);
        T1_pop=length(intpopulation_T1);
        T2_pop=length(intpopulation_T2);
        [intpopulation_T1,frontnumbers]=SolutionComparison.nondominatedsort(intpopulation_T1,T1_pop,no_of_objs_T1);
        [intpopulation_T1,~]=SolutionComparison.diversity(intpopulation_T1,frontnumbers,T1_pop,no_of_objs_T1);
        [intpopulation_T2,frontnumbers]=SolutionComparison.nondominatedsort(intpopulation_T2,T2_pop,no_of_objs_T2);
        [intpopulation_T2,~]=SolutionComparison.diversity(intpopulation_T2,frontnumbers,T2_pop,no_of_objs_T2);
        population(1:pop1) = intpopulation_T1(1:pop1);
        population(pop1+1:pop) = intpopulation_T2(1:pop2);     

        % Convergence testing
        T1_data = vec2mat([population(1:pop1).objs_T1],no_of_objs_T1);

       IGD1 = IGD(T1_data,pf1,no_of_objs_T1);
       store(1,generation) = IGD1;
              
       
        T2_data = vec2mat([population(pop1+1:pop).objs_T2],no_of_objs_T2);
        IGD2 =  IGD(T2_data,pf2,no_of_objs_T2);
        store(2,generation) = IGD2;
 
        store(3,generation)=rmp;
        
        disp(['MFEA-II Generation = ', num2str(generation),  '  rmp = ', num2str(rmp), '       IGD1 = ', num2str(store(1,generation)), '      IGD2 = ', num2str(store(2,generation)) ]); %  
    end
    
    T1_f1=[];
    T1_f2=[];
    T1_f3=[];
    T2_f1=[];
    T2_f2=[];
    T2_f3=[];
    for i=1:pop
        if population(i).skill_factor==1
            if no_of_objs_T1 == 2
                T1_f1=[T1_f1,population(i).objs_T1(1)];
                T1_f2=[T1_f2,population(i).objs_T1(2)];
            else
                T1_f1=[T1_f1,population(i).objs_T1(1)];
                T1_f2=[T1_f2,population(i).objs_T1(2)];
                T1_f3=[T1_f3,population(i).objs_T1(3)];
            end
        else
            if no_of_objs_T2 == 2
                T2_f1=[T2_f1,population(i).objs_T2(1)];
                T2_f2=[T2_f2,population(i).objs_T2(2)];
            else
                T2_f1=[T2_f1,population(i).objs_T2(1)];
                T2_f2=[T2_f2,population(i).objs_T2(2)];
                T2_f3=[T2_f3,population(i).objs_T2(3)];
            end
        end
    end
    figure(01)
    if no_of_objs_T1 == 2
        plot(T1_f1,T1_f2,'o')
        title('Task 1 PF approx.')
        xlabel('Objective f1')
        ylabel('Objective f2')
    else
        plot3(T1_f1,T1_f2,T1_f3,'o')
    end
    figure(02)
    if no_of_objs_T2 == 2
        plot(T2_f1,T2_f2,'o')
        title('Task 2 PF approx.')
        xlabel('Objective f1')
        ylabel('Objective f2')
    else
        plot3(T2_f1,T2_f2,T2_f3,'o')
    end    
    figure(03)
    plot(store(1,:)/max(store(1,:)))
    title('Task 1 IGD convergence')
    xlabel('Generations')
    ylabel('IGD')
    figure(04)
    plot(store(2,:)/max(store(2,:)))
    title('Task 2 IGD convergence')
    xlabel('Generations')
    ylabel('IGD')
end