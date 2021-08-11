function [PopX,Pareto,POF_iter] = RMMEDA( Problem, NIni, MaxIter, t,init_population)

            Generator.Name  = 'LPCA';       % name of generator
            Generator.NClu  = 5;            % parameter of generator, the number of clusters(default) 
            Generator.Iter  = 50;           % maximum trainning steps in LPCA
                                            % usually, LPCA stops less than 10
                                            % iterations
            Generator.Exte  = 0.25;         % parameter of generator, extension rate(default)
%%
%% Step 0: define and set algorithm parameters
assert(nargin >= 4);
Pareto.Neva     = 0;                        % function evaluations
DX              = size(Problem.XLow,1);     % dimension of decision variables
PopF            = ones(Problem.NObj, NIni); % population (F)
PopV            = ones(1, NIni);            % constraint vialation
TriF            = ones(Problem.NObj, NIni); % trial population (F)
TriV            = ones(1, NIni);            % constraint vialation
DLat            = Problem.NObj-1;           % dimension of latent variable space
LInd    = ones(DX,NIni);
%% Step 1: initialize population
if nargin == 4
    for i=1:1:DX
        LInd(i,:)   = randperm(NIni);
    end
    PopX    = (LInd - rand(DX,NIni))/NIni .* ((Problem.XUpp-Problem.XLow)*ones(1,NIni)) + Problem.XLow*ones(1,NIni);
    for i=1:1:NIni
        [PopF(:,i),PopV(:,i)] = Problem.FObj(PopX(:,i)',t);
    end
end
if nargin == 5
    if size(init_population,2) < NIni
        PopX(:,1:size(init_population,2)) = init_population;
        %设计一个增加个体的方案
        newpop = addNoise(init_population, NIni, size(init_population,1));
        PopX(:,size(init_population,2)+1:NIni) = newpop;
    else
        PopX = init_population;
    end
    for i=1:NIni
        [PopF(:,i),PopV(:,i)] = Problem.FObj(PopX(:,i)',t);
    end  
    
    
end

Pareto.Neva    = Pareto.Neva + NIni;
clear LInd;
%% Step 2: main iterations
for iter=1:MaxIter
    % Step 2.1: generate new trial solutions
    TriX = LPCAGenerator(PopX, Problem.XLow, Problem.XUpp, NIni, DX, DLat, Generator.NClu, Generator.Iter, Generator.Exte);   
    % Step 2.2: evaluate new trial solutions
    for i=1:1:NIni
        [TriF(:,i),TriV(:,i)] = Problem.FObj(TriX(:,i)',t);
    end
    Pareto.Neva    = Pareto.Neva + NIni;
    % Step 2.3: selecte some points to be evaluated by the true objective
    F       = [PopF,TriF];
    X       = [PopX,TriX];
    V       = [PopV,TriV];
    [PopF,PopX,PopV]   = MOSelector( F, X, V, NIni ); 
    [Pareto.F,Pareto.X,Pareto.V] = ParetoFilter(PopF,PopX,PopV);
    POF_iter{iter} = Pareto.F;
end

