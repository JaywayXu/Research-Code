%%
% <html><h2>Main function for Tr-NSGA-II</h2></html>

clear
clc

functions = {'FDA4', 'FDA5', 'FDA5_iso', 'FDA5_dec', 'DIMP2', 'dMOP2', ...
    'dMOP2_iso', 'dMOP2_dec', 'dMOP3', 'HE2', 'HE7', 'HE9'};

for testfunc = 1:1
    clearvars -except functions testfunc
    
    %% step 1. Initialize objective functions
    T_parameter = [
        10 5 100
        10 10 200
        10 25 500
        10 50 1000
        1 10 200
        1 50 1000
        20 10 200
        20 50 1000];
    mkdir(['.\Results\' functions{testfunc}]);
    
    %% step 2. Iterate through enviroment parameters
    for group =1:size(T_parameter,1)
        mkdir(['.\Results\' functions{testfunc} '\group' num2str(group)]);
        fprintf('running %s \n',functions{testfunc});
        
        %% step 3. use the NSGA-II to get a POF at the initial moment with randomly generated population
        t0 = 0;         % the initial moment
        [n, Fn, Ft] = getFunc(functions{testfunc});
        CostFunction = @(x)Ft(x, t0);
        pop = 200;      % poplation number
        gen = 200;      % max generations of evolution
        
        M = Fn;         % number of objects
        V = n;          % number of decision variables
        min_range = zeros(1,V);
        max_range = ones(1,V);
        chromosome = initialize_variables(pop, M, V, min_range, max_range,testfunc,t0); % Initialize the population randomly
        chromosome = non_domination_sort_mod(chromosome, M, V);
        
        for i = 1:gen
            pool = round(pop/2);
            tour = 2;
            parent_chromosome = tournament_selection(chromosome, pool, tour);
            mu = 20;
            mum = 20;
            
            offspring_chromosome = genetic_operator(parent_chromosome, M, V, mu, mum, min_range, max_range,testfunc,t0);
            [main_pop,~] = size(chromosome);
            [offspring_pop,~] = size(offspring_chromosome);
            inter_chromosome(1:main_pop,:) = chromosome;
            inter_chromosome(main_pop + 1 : main_pop + offspring_pop,1 : M+V) = offspring_chromosome;
            inter_chromosome = non_domination_sort_mod(inter_chromosome, M, V);
            chromosome = replace_chromosome(inter_chromosome, M, V, pop);
        end
        POF = chromosome(:,V+1:V+M);
        
        % Iterate through time steps
        for T = 1:T_parameter(group,3)/T_parameter(group,2)
            %% step 4. use TCA to get the initial population at the next moment
            
            % Initialize random populations
            sampleN = 400;
            for i=1:sampleN
                tempParticle = rand(1,V)*(max(max_range)-min(min_range));
                Fs(:,i)=CostFunction(tempParticle);
            end
            t = 1/T_parameter(group,1)*(T-1);   % next moment
            CostFunction = @(x)Ft(x, t);
            for i=1:sampleN
                tempParticle = rand(1,V)*(max(max_range)-min(min_range));
                Fa(:,i)=CostFunction(tempParticle);
            end
            
            % Find the latent space of domain adaptation
            mu = 0.5;
            lambda = 'unused';
            dim = 20;           % Deduced dimension
            kind = 'Gaussian';  % The dimension of Gaussian Kernel feature space is inifinite, so the deduced dimension can be 20.
            p1 = 1;
            p2 = 'unused';
            p3 = 'unused';
            W = getW(Fs, Fa, mu, lambda, dim, kind, p1, p2, p3);
            POF_deduced = getNewY(Fs, Fa, POF', W, kind, p1, p2, p3);
            
            % Get initial population by POF_deduced
            dis_px = @(p, x)sum((getNewY(Fs, Fa, CostFunction(x)', W, kind, p1, p2, p3) - p).^2);
            initn = size(POF_deduced, 2);
            init_population = zeros(initn, n);
            for i = 1:initn
                init_population(i,:) = fmincon(@(x)dis_px(POF_deduced(:,i), x), rand(1,n), ...
                    [], [], [], [], zeros(1,n), ones(1,n), [], optimset('display', 'off'));
            end
            POF = getbatchoutput(CostFunction, init_population);
            clear chromosome
            
            %% step 5. use MOPSO to get the POF at every moment with the initial population
            chromosome = [init_population POF];
            chromosome = non_domination_sort_mod(chromosome, M, V);
            for i = 1 : gen
                pool = round(pop/2);
                tour = 2;
                parent_chromosome = tournament_selection(chromosome, pool, tour);
                mu = 20;
                mum = 20;
                
                offspring_chromosome = genetic_operator(parent_chromosome, M, V, mu, mum, min_range, max_range,testfunc,t);
                [main_pop,~] = size(chromosome);
                [offspring_pop,~] = size(offspring_chromosome);
                inter_chromosome(1:main_pop,:) = chromosome;
                inter_chromosome(main_pop + 1 : main_pop + offspring_pop,1 : M+V) = offspring_chromosome;
                inter_chromosome = non_domination_sort_mod(inter_chromosome, M, V);
                chromosome = replace_chromosome(inter_chromosome, M, V, pop);
                POF_iter = chromosome(:,V+1:V+M);
                
                TruePOF = getBenchmarkPOF(testfunc,group,T);
                iterIGD(i) = IGD(POF_iter,TruePOF);
            end
            
            %% step 6. Save Metrics to flies
            FILEPATH = ['.\Results\' functions{testfunc} '\group' num2str(group) '\'];
            filename = ['iterIGD-T' num2str(T) '.txt'];
            save([FILEPATH,filename],'iterIGD','-ascii');
        end
    end
end