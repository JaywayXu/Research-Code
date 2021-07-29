%
% Copyright (c) 2015, Yarpiz (www.yarpiz.com)
% All rights reserved. Please read the "license.txt" for license terms.
%
% Project Code: YPEA124
% Project Title: Implementation of MOEA/D
% Muti-Objective Evolutionary Algorithm based on Decomposition
% Publisher: Yarpiz (www.yarpiz.com)
%
% Developer: S. Mostapha Kalami Heris (Member of Yarpiz Team)
%
% Contact Info: sm.kalami@gmail.com, info@yarpiz.com
%

clc;
clear;
close all;

%% Problem Definition

CostFunction = @(x) ZDT(x); % Cost Function

nVar = 3; % Number of Decision Variables

VarSize = [nVar 1]; % Decision Variables Matrix Size

VarMin = 0; % Decision Variables Lower Bound
VarMax = 1; % Decision Variables Upper Bound

nObj = numel(CostFunction(unifrnd(VarMin, VarMax, VarSize)));

%% MOEA/D Settings

MaxIt = 100; % Maximum Number of Iterations

nPop = 50; % Population Size (Number of Sub-Problems)

nArchive = 50;

T = max(ceil(0.15 * nPop), 2); % Number of Neighbors
T = min(max(T, 2), 15);

crossover_params.gamma = 0.5;
crossover_params.VarMin = VarMin;
crossover_params.VarMax = VarMax;

%% Initialization

% Create Sub-problems
sp = CreateSubProblems(nObj, nPop, T);

% Empty Individual
empty_individual.Position = [];
empty_individual.Cost = [];
empty_individual.g = [];
empty_individual.IsDominated = [];

% Initialize Goal Point
%z=inf(nObj,1);
z = zeros(nObj, 1);

% Create Initial Population
pop = repmat(empty_individual, nPop, 1);

for i = 1:nPop
    pop(i).Position = unifrnd(VarMin, VarMax, VarSize);
    pop(i).Cost = CostFunction(pop(i).Position);
    z = min(z, pop(i).Cost);
end

for i = 1:nPop
    pop(i).g = DecomposedCost(pop(i), z, sp(i).lambda);
end

% Determine Population Domination Status
pop = DetermineDomination(pop);

% Initialize Estimated Pareto Front
EP = pop(~[pop.IsDominated]);

%% Main Loop

for it = 1:MaxIt

    for i = 1:nPop

        % Reproduction (Crossover)
        K = randsample(T, 2);

        j1 = sp(i).Neighbors(K(1));
        p1 = pop(j1);

        j2 = sp(i).Neighbors(K(2));
        p2 = pop(j2);

        y = empty_individual;
        y.Position = Crossover(p1.Position, p2.Position, crossover_params);

        y.Cost = CostFunction(y.Position);

        z = min(z, y.Cost);

        for j = sp(i).Neighbors
            y.g = DecomposedCost(y, z, sp(j).lambda);

            if y.g <= pop(j).g
                pop(j) = y;
            end

        end

    end

    % Determine Population Domination Status
    pop = DetermineDomination(pop);

    ndpop = pop(~[pop.IsDominated]);

    EP = [EP
        ndpop]; %#ok

    EP = DetermineDomination(EP);
    EP = EP(~[EP.IsDominated]);

    if numel(EP) > nArchive
        Extra = numel(EP) - nArchive;
        ToBeDeleted = randsample(numel(EP), Extra);
        EP(ToBeDeleted) = [];
    end

    % Plot EP
    figure(1);
    PlotCosts(EP);
    pause(0.01);

    % Display Iteration Information
    disp(['Iteration ' num2str(it) ': Number of Pareto Solutions = ' num2str(numel(EP))]);

end

%% Reults

disp(' ');

EPC = [EP.Cost];

for j = 1:nObj

    disp(['Objective #' num2str(j) ':']);
    disp(['      Min = ' num2str(min(EPC(j, :)))]);
    disp(['      Max = ' num2str(max(EPC(j, :)))]);
    disp(['    Range = ' num2str(max(EPC(j, :)) - min(EPC(j, :)))]);
    disp(['    St.D. = ' num2str(std(EPC(j, :)))]);
    disp(['     Mean = ' num2str(mean(EPC(j, :)))]);
    disp(' ');

end
