function [bestSol, fitness_hist, alpha] = AMT_BGA(problem, dims, reps, trans)
%[bestSol, fitness_hist, alpha] = TSBGA(problem, dims, reps, trans): Adaptive
%Model-based Transfer Binary GA. The crossover and mutation for this simple
%binary GA are uniform crossover and bit-flip mutation.
%INPUT:
% problem: problem type, 'onemax', 'onemin', or 'trap5'
% dims: problem dimensionality
% reps: number of repeated trial runs
% trans:    trans.transfer: binary variable 
%           trans.TrInt: transfer interval for AMT
%
%OUTPUT:
% bestSol: best solution for each repetiion
% fitness: history of best fitness for each generation
% alpha: transfer coefficient

    pop = 50;
    gen = 100;
    transfer = trans.transfer;
    if transfer
        TrInt = trans.TrInt;
        load('./allmodels.mat');
    end
    fitness_hist = zeros(reps, gen);
    bestSol = zeros(reps, dims);
    alpha = cell(reps);
    
    for rep = 1:reps
        alpha_rep = [];
        population = round(rand(pop, dims));
        fitness = funceval(population,problem,dims);
        [best_fit, ind] = max(fitness);
        disp(['Generation 1 best fitness = ',num2str(best_fit)]); 
        fitness_hist(rep, 1) = max(fitness);
        
        for i = 2:gen
            if transfer && mod(i,TrInt) == 0
                mmodel = MixtureModel(allmodels);
                mmodel = MixtureModel.createtable(mmodel, population, true, 'umd');
                mmodel = MixtureModel.EMstacking(mmodel); %Recombination of probability models
                mmodel = MixtureModel.mutate(mmodel); % Mutation of stacked probability model
                offspring = MixtureModel.sample(mmodel, pop);
                alpha_rep = [alpha_rep; mmodel.alpha];
                disp(['Transfer coefficient at generation ', num2str(i), ': '...
                    mat2str(mmodel.alpha(1:end-1))])
            else
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
            end        
            cfitness = funceval(offspring,problem,dims);
            interpop = [population;offspring];
            interfitness = [fitness;cfitness];
            [interfitness,index] = sort(interfitness,'descend');
            fitness = interfitness(1:pop);
            interpop = interpop(index,:);        
            population = interpop(1:pop,:);
            disp(['Generation ', num2str(i), ' best fitness = ',num2str(max(fitness))]); 
            fitness_hist(rep, i) = max(fitness);
        end 
        alpha{rep} = alpha_rep;
        bestSol(rep, :) = population(ind, :);
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