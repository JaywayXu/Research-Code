function [IGD_hist, bestSol]= NSGA_II(f,no_of_objs,L,U,pop)
%[IGD_hist, alpha]= NSGA_II(f,no_of_objs,L,U,pop,transfer,TrInt): 
%NSGA_II with SBX crossover and polynomial mutation.
%INPUT:
% f: function to be optimized
% no_of_objs: number of objectives
% L: lower bound of box constraint
% U: upper bound of box constraint
% pop: population size
%
%OUTPUT:
% IGD_hist: history of IGD fitness for each generation
% bestSol: final output solutions
    
load('./allmodels')
global maxdim;

gen=250;
muc=15;% crossover index SBX
mum=20;% mutation index (polynomial mutation)

if mod(pop,2)~=0
    pop=pop+1;
end
dim = length(L);

IGD_hist = zeros(gen, 1);
pf = load([f, '.pf']);  % stored pareto front
    
for i =1:pop
    population(i)=Chromosome;
    population(i)=initialize(population(i),dim);
end
for i=1:pop
	population(i)=evaluate(population(i),f,L,U);
end 
[population,frontnumbers]=SolutionComparison.nondominatedsort(population,pop,no_of_objs);
[population,minimums]=SolutionComparison.diversity(population,frontnumbers,pop,no_of_objs);
for generation=1:gen
    for i = 1:pop
        parent(i)=Chromosome();
        p1=1+round(rand(1)*(pop-1));
        p2=1+round(rand(1)*(pop-1));
        if population(p1).front < population(p2).front
            parent(i).rnvec=population(p1).rnvec;
        elseif population(p1).front == population(p2).front
            if population(p1).CD > population(p2).CD
                parent(i).rnvec=population(p1).rnvec;
            else 
                parent(i).rnvec=population(p2).rnvec;
            end
        else
        	parent(i).rnvec=population(p2).rnvec;
        end
    end
    solutions = zeros(pop, dim);
    for i = 1:pop
        solutions(i,:) = parent(i).rnvec;
    end
    count=1;
    for i=1:2:pop-1
        child(count)=Chromosome;
        child(count+1)=Chromosome;
        p1=i;
        p2=i+1;
        [child(count).rnvec,child(count+1).rnvec]=Evolve.crossover(parent(p1).rnvec,parent(p2).rnvec,muc,dim);
        child(count).rnvec = Evolve.mutate(child(count).rnvec,mum,dim);
        child(count+1).rnvec=Evolve.mutate(child(count+1).rnvec,mum,dim);
        count=count+2;
    end

    for i = 1:pop
        child(i).rnvec(child(i).rnvec < 0) = 0;
        child(i).rnvec(child(i).rnvec > 1) = 1;
    end

    for i=1:pop
        child(i)=evaluate(child(i),f,L,U);
    end
    clear intpopulation
    for i=1:2*pop
        if i <= pop
            population(i)=reset(population(i));
            intpopulation(i)=population(i);
        else
            intpopulation(i)=child(i-pop);
        end
    end

    [intpopulation,frontnumbers]=SolutionComparison.nondominatedsort(intpopulation,2*pop,no_of_objs);
    [intpopulation,minimums]=SolutionComparison.diversity(intpopulation,frontnumbers,2*pop,no_of_objs);           
    population(1:pop)=intpopulation(1:pop);

    % Convergence testing
    obj_data = vec2mat([population.objectives],no_of_objs);           
    IGD = 0;
    if no_of_objs == 2
        for i = 1:size(pf,1)
            c1 = pf(i,1)*ones(pop,1);
            c2 = pf(i,2)*ones(pop,1);
            IGD = IGD + sqrt(min(sum((obj_data-[c1 c2]).^2,2)));
        end
    elseif no_of_objs == 3
        for i = 1:size(pf,1)
            c1 = pf(i,1)*ones(pop,1);
            c2 = pf(i,2)*ones(pop,1);
            c3 = pf(i,3)*ones(pop,1);
            IGD = IGD + sqrt(min(sum((obj_data-[c1 c2 c3]).^2,2)));
        end
    else
        error('Too many objectives.');
    end
    IGD_hist(generation)=IGD/size(pf,1);  
    disp(['Generation ', num2str(generation), ' IGD score: ', num2str(IGD_hist(generation))]);
end
if nargout == 2
    bestSol = population;
end

% collect the genotype for building source probabilistic model
disp('Building probablistic model...')
pop_model = pop;
solutions = zeros(pop_model, dim);
for i = 1:pop_model
    if i <= pop
        solutions(i,:) = population(i).rnvec;
    else
        solutions(i,:) = rand(1,dim);
    end
end
if dim ~= maxdim
	solutions = [solutions, rand(size(solutions, 1), maxdim - dim)];
end
model = ProbabilityModel('mvarnorm');
model = ProbabilityModel.buildmodel(model, solutions);
allmodels{length(allmodels)+1} = model;
save('allmodels','allmodels');
disp('Complete!')
end