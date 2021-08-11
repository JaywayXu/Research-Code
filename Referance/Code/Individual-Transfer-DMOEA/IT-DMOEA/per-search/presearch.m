function pop=presearch(Problem,t,nPop,MaxIt)

CostFunction = @(x,t)Problem.FObj(x,t);

nVar = size(Problem.XLow,1);    % Number of Decision Variables

VarSize = [1 nVar]; % Size of Decision Variables Matrix

VarMin = 0;   % Lower Bound of Variables
VarMax = 1;   % Upper Bound of Variables

nObj =Problem.NObj;

% Generating Reference Points
if nObj==2
    nDivision = 24;
else
    nDivision = 9;
end

Zr = GenerateReferencePoints(nObj, nDivision);


pCrossover = 0.5;       % Crossover Percentage
nCrossover = 2*round(pCrossover*nPop/2); % Number of Parnets (Offsprings)
pMutation = 0.5;       % Mutation Percentage
nMutation = round(pMutation*nPop);  % Number of Mutants
mu = 0.02;     % Mutation Rate
sigma = 0.1*(VarMax-VarMin); % Mutation Step Size

params.nPop = nPop;
params.Zr = Zr;
params.nZr = size(Zr,2);
params.zmin = [];
params.zmax = [];
params.smin = [];

empty_individual.Position = [];
empty_individual.Cost = [];
empty_individual.Rank = [];
empty_individual.DominationSet = [];
empty_individual.DominatedCount = [];
empty_individual.NormalizedCost = [];
empty_individual.AssociatedRef = [];
empty_individual.DistanceToAssociatedRef = [];

pop = repmat(empty_individual, nPop, 1);


for i = 1:nPop
    pop(i).Position = unifrnd(VarMin, VarMax, VarSize);
    pop(i).Cost = CostFunction(pop(i).Position,t);
end

% Sort Population and Perform Selection
[pop, params] = SortAndSelectIndividuals(pop, params);


for it = 1:MaxIt

    nPop=size(pop,1);
    % Crossover
    
    popc = repmat(empty_individual, nCrossover/2, 2);
    for k = 1:nCrossover/2
        i1 = randi([1 nPop]);
        p1 = pop(i1);

        i2 = randi([1 nPop]);
        p2 = pop(i2);

        [popc(k, 1).Position, popc(k, 2).Position] = Crossover(p1.Position, p2.Position);

        popc(k, 1).Cost = CostFunction(popc(k, 1).Position,t);
        popc(k, 2).Cost = CostFunction(popc(k, 2).Position,t);
    end
   
    popc = popc(:);

    % Mutation
    popm = repmat(empty_individual, nMutation, 1);
    for k = 1:nMutation
        i = randi([1 nPop]);
        p = pop(i);
        popm(k).Position = Mutate(p.Position, mu, sigma);
        popm(k).Cost = CostFunction(popm(k).Position,t);
    end
    
    if size(pop,1)==1
        pop=pop';
    end 
    % Merge
    pop = [pop
           popc
           popm]; 
  
    % Sort Population and Perform Selection
    [pop, params] = SortAndSelectIndividuals(pop, params);

    pop=pop';
    
     if it>2 && Coverage([lastPop.Cost]',[pop.Cost]')<0.9
        break;
     end
    lastPop=pop;
end

end

