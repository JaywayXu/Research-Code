function model = BGA(problem,dims,th_best) % Simple Binary GA, with uniform crossover and bit-flip mutation
% Function returns a probability distribution model encapsulating the structure of the
% favorable regions of the search space.
    load allmodels_TS % allmodels should be initialized as an empty cell array where source probability distributions are gradually stored
    load allmodels_CBR

    pop = 100;
    gen = 1000;
    TrInt = 1;
    
    population = round(rand(pop,dims));    
    fitness = funceval(population,problem,dims);
    buildmodel = true;
    
    for i = 1:gen
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
        disp(['Best fitness = ',num2str(fitness(1))]);
        allmodels_CBR = [allmodels_CBR; population(1,:)];
        if fitness(1) == th_best && buildmodel
            model = ProbabilityModel('umd');
            noise = [];
            noise = round(rand(0.1*pop,dims));
            model = ProbabilityModel.buildmodel(model,[population;noise]);
            allmodels_TS{length(allmodels_TS)+1} = model;
            save('allmodels_TS.mat','allmodels_TS')
            buildmodel = false;

            allmodels_CBR = [allmodels_CBR; population(1,:)];
            break;
        end
    end
    save('allmodels_CBR.mat', 'allmodels_CBR');
end

function fitness = funceval(population,problem,dims)
    if strcmp(problem,'onemax')
        fitness = sum(population,2);
    elseif strcmp(problem,'onemin')
        fitness = dims - sum(population,2);
    end        
end