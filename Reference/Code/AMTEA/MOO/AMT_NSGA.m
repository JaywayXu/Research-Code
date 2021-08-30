function [IGD_hist, alpha, bestSol]= AMT_NSGA(f,no_of_objs,L,U,pop,trans)
%[IGD_hist, alpha]= AMT_NSGA(f,no_of_objs,L,U,pop,transfer,TrInt): Adaptive
%Model-based Transfer NSGA_II with SBX crossover and polynomial mutation.
%INPUT:
% f: function to be optimized
% no_of_objs: number of objectives
% L: lower bound of box constraint
% U: upper bound of box constraint
% pop: population size
% trans:    trans.transfer: binary variable 
%           trans.TrInt: transfer interval for AMT
%
%OUTPUT:
% IGD_hist: history of IGD fitness for each generation
% alpha: transfer coefficient
% bestSol: final output solutions

load('./allmodels')
global maxdim;

gen=100;
muc=20;% crossover index SBX
mum=2;% mutation index (polynomial mutation)

if mod(pop,2)~=0
    pop=pop+1;
end
dim = length(L);

if dim < maxdim
    for i = 1:length(allmodels)
        allmodels{i}.mean_noisy = allmodels{i}.mean_noisy(1:dim);
        allmodels{i}.mean_true = allmodels{i}.mean_true(1:dim);
        allmodels{i}.covarmat_noisy = allmodels{i}.covarmat_noisy(1:dim, 1:dim);
        allmodels{i}.covarmat_true = allmodels{i}.covarmat_true(1:dim, 1:dim);
        allmodels{i}.vars = dim;
    end
end

IGD_hist = zeros(gen, 1);
alpha = [];
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

for generation=2:gen
    if trans.transfer && mod(generation, trans.TrInt)==0
        pop_model = round(1.1*pop);
        solutions = zeros(pop_model, dim);
        for i = 1:pop
            solutions(i,:) = population(i).rnvec;
        end
        solutions((pop+1):pop_model,:) = rand((pop_model-pop),dim);
        child = repmat(Chromosome, 1, pop);
        mmodel = MixtureModel(allmodels);
        mmodel = MixtureModel.createtable(mmodel, solutions, true, 'mvarnorm');
        mmodel = MixtureModel.EMstacking(mmodel);
        mmodel = MixtureModel.mutate(mmodel);
        alpha = [alpha; mmodel.alpha];
        offspring = MixtureModel.sample(mmodel,pop);
        offspring(offspring > 1) = 1;
        offspring(offspring < 0) = 0;
        for i = 1:pop
            child(i).rnvec = offspring(i,:);
        end
    else
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

    %  Convergence testing
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
if nargout == 3
    bestSol = population;
end
end