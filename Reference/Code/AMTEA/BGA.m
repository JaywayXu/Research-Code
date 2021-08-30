function [bestSol, fitness_hist] = BGA(problem, dims, th_best) 
%[bestSol, fitness_hist] = BGA(problem,dims,th_best): simple binary GA with
%uniform crossover and bit-flip mutation. 
%INPUT:
% problem: problem type, 'onemax', 'onemin', or 'trap5'
% dims: problem dimensionality
% th_best: global best fitness value (used for early stop to build
% probabilistic models)
%
%OUTPUT:
% bestSol: best solution
% fitness: history of best fitness for each generation
    
    % allmodels should be initialized as an empty cell array where 
    % source probability distributions are gradually stored
    load('./allmodels.mat');
    
    pop = 200;
    gen = 1000;
    
    fitness_hist = zeros(gen, 1);
    population = round(rand(pop,dims));    
    fitness = funceval(population,problem,dims);
    buildmodel = true;
    fitness_hist(1) = max(fitness);
    disp(['Generation 1 best fitness = ',num2str(fitness_hist(1))]);
    
    for i = 2:gen
        parent1 = population(randperm(pop),:);
        parent2 = population(randperm(pop),:);
        tmp = rand(pop,dims);        
        offspring = zeros(pop,dims);
        index = tmp>=0.5;
        offspring(index) = parent1(index);
        index = tmp<0.5;
        offspring(index) = parent2(index);
        tmp = rand(pop,dims);
        index = tmp<(1/dims);
        offspring(index) = abs(1-offspring(index));
        cfitness = funceval(offspring,problem,dims);
        interpop = [population;offspring];
        interfitness = [fitness;cfitness];
        [interfitness,index] = sort(interfitness,'descend');
        fitness = interfitness(1:pop);
        interpop = interpop(index,:);        
        population = interpop(1:pop,:);
        fitness_hist(i) = fitness(1);
        disp(['Generation ', num2str(i), ' best fitness = ',num2str(fitness_hist(i))]); 
 
        if (fitness(1) >= th_best || i == gen) && buildmodel
            disp('Building probablistic model...')
            model = ProbabilityModel('umd');
            model = ProbabilityModel.buildmodel(model,population);
            allmodels{length(allmodels)+1} = model;
            save('allmodels.mat','allmodels')
            disp('Complete!')
            fitness_hist(i+1:end) = fitness(1);
            bestSol = population(1, :);
            break;
        end
    end
end

function fitness = funceval(population,problem,dims)
    if strcmp(problem,'onemax')
        fitness = sum(population,2);
    elseif strcmp(problem,'onemin')
        fitness = dims - sum(population,2);
    elseif strcmp(problem,'trap5')
        pop = size(population, 1);
        fitness = zeros(pop,1);
        index = 1:dims;
        index = vec2mat(index,5);
        rows = size(index,1);
        for i = 1:pop
            fitsum = 0;
            for j = 1:rows
                contri = sum(population(i,index(j,:)));
                if contri == 5
                    fitsum = fitsum+5;
                else
                    fitsum = fitsum+(4-contri);
                end
            end
            fitness(i) = fitsum;
        end
    else
        error('Function not implemented.')
    end
end