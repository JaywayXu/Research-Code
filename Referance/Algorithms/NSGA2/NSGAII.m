% ----------------------------------------------------------------------- %
% Function NSGAII performs a Non Sorting Genetic Algorithm-II over conti- %
% nous functions.                                                         %
%                                                                         %
%   Input parameters:                                                     %
%       - params:   Struct that contains the customized parameters.       %
%           * params.Np:        Number of chromosomes in the population.  %
%           * params.maxgen:    Maximum number of generations.            %
%           * params.pc:        Probability of crossover.                 %
%           * params.pm:        Probability of mutation.                  %
%           * params.ms:        Mutation strenght (around 2%-10% is fine).%
%       - MultiObj: Struct that contains the parameters relative to the   %
%                   optimization functions.                               %
%           * MultiObj.fun:     Anonymous multi-obj function to minimize. %
%           * MultiObj.nVar:    Number of variables.                      %
%           * MultiObj.var_min: Vector that indicates the minimum values  %
%                               of the search space in each dimension.    %
%           * MultiObj.var_max: Same than 'var_min' with the maxima.      %
% ----------------------------------------------------------------------- %
%   For an example of use, run 'example.m'.                               %
% ----------------------------------------------------------------------- %
%   Author:  Victor Martinez-Cagigal                                      %
%   Date:    25/11/2019                                                   %
%   E-mail:  vicmarcag (at) gmail (dot) com                               %
%   Version: 1.2                                                          %
%   Log:                                                                  %
%           - 1.0:  Initial version (21/12/2017).                         %
%           - 1.1:  Fast Non Sorting Algorithm is now vectorized for im-  %
%                   proving the performance (much less computation time)  %
%                   (22/12/2017).                                         %
%           - 1.2:  The old mutation operator is substituted by the adding%
%                   of a weighted normal distribution, as suggested by    %
%                   Alexander Hagg, which brings a better convergence     %
%                   (25/11/2019).                                         %
% ----------------------------------------------------------------------- %
%   References:                                                           %
%    [1] Deb, K., Pratap, A., Agarwal, S., & Meyarivan, T. A. M. T. (2002)%
%        A fast and elitist multiobjective genetic algorithm: NSGA-II.    %
%        IEEE transactions on evolutionary computation, 6(2), 182-197.    %
% ----------------------------------------------------------------------- %
function NSGAII(params, MultiObj)

    % Parameters
    Np = params.Np; % Number of chromosomes in the population
    maxgen = params.maxgen; % Maximum number of generations
    pc = params.pc; % Probability of crossover
    pm = params.pm; % Probability of mutation
    ms = params.ms; % Mutation strength
    fun = MultiObj.fun; % Objective function
    nVar = MultiObj.nVar; % Number of variables (dimensions or objectives)
    var_min = MultiObj.var_min(:); % Minimum value for each gen
    var_max = MultiObj.var_max(:); % Maximum value for each gen

    % Initialization
    gen = 1;
    P = repmat((var_max - var_min)', Np, 1) .* rand(Np, nVar) + repmat(var_min', Np, 1);
    Pfit = fun(P);
    Prank = FastNonDominatedSorting_Vectorized(Pfit);
    [P, ~] = selectParentByRank(P, Prank);
    Q = applyCrossoverAndMutation(P, pc, pm, ms, var_max, var_min);

    % Plotting and verbose
    if (size(Pfit, 2) == 2)
        h_fig = figure(1);
        h_par = scatter(Pfit(:, 1), Pfit(:, 2), 20, 'filled', 'markerFaceAlpha', 0.3, 'MarkerFaceColor', [128 193 219] ./ 255); hold on;
        h_rep = plot(Pfit(:, 1), Pfit(:, 2), 'ok'); hold on;
        grid on; xlabel('f1'); ylabel('f2');
        drawnow;
        axis square;
    end

    if (size(Pfit, 2) == 3)
        h_fig = figure(1);
        h_rep = plot3(Pfit(:, 1), Pfit(:, 2), Pfit(:, 3), 'ok'); hold on;
        grid on; xlabel('f1'); ylabel('f2'); zlabel('f3');
        drawnow;
        axis square;
    end

    display(['Generation #' num2str(gen) ' - First front size: ' num2str(sum(Prank == 1))]);

    % Main NSGA-II loop
    stopCondition = false;

    while ~stopCondition

        % Merge the parent and the children
        R = [P; Q];

        % Compute the new Pareto Fronts
        Rfit = real(fun(R));
        Rrank = FastNonDominatedSorting_Vectorized(Rfit);

        % Plotting and verbose
        if (size(Rfit, 2) == 2)
            figure(h_fig); delete(h_rep);
            h_par = scatter(Rfit(1:Np, 1), Rfit(1:Np, 2), 20, 'filled', 'markerFaceAlpha', 0.3, 'MarkerFaceColor', [128 193 219] ./ 255); hold on;
            h_rep = plot(Rfit(1:Np, 1), Rfit(1:Np, 2), 'ok'); hold on;

            if (isfield(MultiObj, 'truePF'))
                try delete(h_pf); end
                h_pf = plot(MultiObj.truePF(:, 1), MultiObj.truePF(:, 2), '.', 'color', 0.8 .* ones(1, 3)); hold on;
            end

            grid on; xlabel('f1'); ylabel('f2');
            drawnow;
            axis square;
        end

        if (size(Rfit, 2) == 3)
            figure(h_fig); delete(h_rep);
            h_rep = plot3(Rfit(1:Np, 1), Rfit(1:Np, 2), Rfit(1:Np, 3), 'ok'); hold on;

            if (isfield(MultiObj, 'truePF'))
                try delete(h_pf); end
                h_pf = plot3(MultiObj.truePF(:, 1), MultiObj.truePF(:, 2), MultiObj.truePF(:, 3), '.', 'color', 0.8 .* ones(1, 3)); hold on;
            end

            grid on; xlabel('f1'); ylabel('f2');
            drawnow;
            axis square;
        end

        display(['Generation #' num2str(gen) ' - First front size: ' num2str(sum(Rrank == 1))]);

        % Sort by rank
        [Rrank, idx] = sort(Rrank, 'ascend');
        Rfit = Rfit(idx, :);
        R = R(idx, :);

        % Compute the crowding distance index
        [Rcrowd, Rrank, ~, R] = crowdingDistances(Rrank, Rfit, R);

        % Select Parent
        P = selectParentByRankAndDistance(Rcrowd, Rrank, R);

        % Compute child
        Q = applyCrossoverAndMutation(P, pc, pm, ms, var_max, var_min);

        % Increment generation
        gen = gen + 1;
        if (gen > maxgen), stopCondition = true; end
    end

end

% Function that selects a new parent based on the crowding distance
% operator
function [newParent] = selectParentByRankAndDistance(Rcrowd, Rrank, R)

    % Initialization
    N = length(Rcrowd) / 2;
    Npf = length(unique(Rrank));
    newParent = zeros(N, size(R, 2));

    % Selecting the chromosomes
    pf = 1;
    numberOfSolutions = 0;

    while pf <= Npf
        % If there is enough space, select solutions based on rank
        if numberOfSolutions + sum(Rrank == pf) <= N
            newParent(numberOfSolutions + 1:numberOfSolutions + sum(Rrank == pf), :) = R(Rrank == pf, :);
            numberOfSolutions = numberOfSolutions + sum(Rrank == pf);
            % If there isn't enugh space, sort by crowding distances
        else
            rest = N - numberOfSolutions;
            lastPF = R(Rrank == pf, :);
            lastPFdist = Rcrowd(Rrank == pf);
            [~, idx] = sort(lastPFdist, 'descend');
            lastPF = lastPF(idx, :);
            newParent(numberOfSolutions + 1:numberOfSolutions + rest, :) = lastPF(1:rest, :);
            numberOfSolutions = numberOfSolutions + rest;
        end

        pf = pf + 1;
    end

end

% Function that computes the crowding distances of every single ParetoFront
function [sortCrowd, sortRank, sortFit, sortPop] = crowdingDistances(rank, fitness, pop)

    % Initialize
    sortPop = [];
    sortFit = [];
    sortRank = [];
    sortCrowd = [];

    Npf = length(unique(rank));

    for pf = 1:1:Npf
        index = find(rank == pf);
        temp_fit = fitness(index, :);
        temp_rank = rank(index, :);
        temp_pop = pop(index, :);

        % Sort by first dimension
        [temp_fit, sort_idx] = sortrows(temp_fit, 1);
        temp_rank = temp_rank(sort_idx);
        sortFit = [sortFit; temp_fit];
        sortRank = [sortRank; temp_rank];
        sortPop = [sortPop; temp_pop(sort_idx, :)];

        % Crowded distances
        temp_crowd = zeros(size(temp_rank));

        for m = 1:1:size(fitness, 2)
            temp_max = max(temp_fit(:, m));
            temp_min = min(temp_fit(:, m));

            for l = 2:1:length(temp_crowd) - 1
                temp_crowd(l) = temp_crowd(l) + (abs(temp_fit(l - 1, m) - temp_fit(l + 1, m))) ./ (temp_max - temp_min);
            end

        end

        temp_crowd(1) = Inf;
        temp_crowd(length(temp_crowd)) = Inf;
        sortCrowd = [sortCrowd; temp_crowd];
    end

end

% Function that calculates a child population by applying crossover and mutation
function Q = applyCrossoverAndMutation(parent, pc, pm, ms, var_max, var_min)
    % Params
    N = size(parent, 1);
    nVar = size(parent, 2);

    % Child initialization
    Q = parent;

    % Crossover
    cross_idx = rand(N, 1) < pc;
    cross_idx = find(cross_idx);

    for c = 1:1:length(cross_idx)
        selected = randi(N, 1, 1);

        while selected == c
            selected = randi(N, 1, 1);
        end

        cut = randi(nVar, 1, 1);
        Q(c, :) = [parent(c, 1:cut), parent(selected, cut + 1:nVar)];
    end

    % Mutation population with Gaussian distribution
    mutatedPop = Q + ms .* repmat((var_max - var_min)', N, 1) .* randn(N, nVar);
    minVal = repmat(var_min', N, 1);
    maxVal = repmat(var_max', N, 1);
    mutatedPop(mutatedPop < minVal) = minVal(mutatedPop < minVal);
    mutatedPop(mutatedPop > maxVal) = maxVal(mutatedPop > maxVal);

    % Mutate the children with probability pm
    mut_idx = rand(N, nVar) < pm;
    Q(mut_idx) = mutatedPop(mut_idx);
end

% Function that performs a binary tournament selection and extracts one
% parent from the initial population based on their ranks.
function [P1, P1rank] = selectParentByRank(P, Prank)
    % Take the couples
    N = length(Prank);
    left_idx = randi(N, N, 1);
    right_idx = randi(N, N, 1);

    while sum(left_idx == right_idx) > 0
        right_idx(left_idx == right_idx) = randi(N, sum(left_idx == right_idx), 1);
    end

    % Make the tournament
    winners = zeros(N, 1);
    winners(Prank(left_idx) <= Prank(right_idx)) = left_idx(Prank(left_idx) <= Prank(right_idx));
    winners(Prank(right_idx) < Prank(left_idx)) = right_idx(Prank(right_idx) < Prank(left_idx));

    % Select both populations
    P1 = P(winners, :);
    P1rank = Prank(winners, :);
end

% Funtion that performs a Fast Non Dominated Sorting algorithm of the input
% fitnesses. Note: the code is not vectorized, its programming is just
% based on Deb2002.
function [RANK] = FastNonDominatedSorting_Loop(fitness)
    % Initialization
    Np = size(fitness, 1);
    N = zeros(Np, 1);
    S{Np, 1} = [];
    PF{Np, 1} = [];
    RANK = NaN(Np, 1);

    % Main algorithm
    for p_idx = 1:1:Np
        p = fitness(p_idx, :);

        for q_idx = 1:1:Np
            q = fitness(q_idx, :);

            if dominates(p, q)
                S{p_idx, 1} = [S{p_idx, 1}; q_idx];
            elseif dominates(q, p)
                N(p_idx) = N(p_idx) + 1;
            end

        end

        if N(p_idx) == 0
            RANK(p_idx) = 1;
            PF{1, 1} = [PF{1, 1}; p_idx];
        end

    end

    i = 1;

    while ~isempty(PF{i, 1})
        Q = [];
        currPF = PF{i, 1};

        for p_idx = 1:1:length(currPF)
            Sp = S{currPF(p_idx), 1};

            for q_idx = 1:1:length(Sp)
                N(Sp(q_idx)) = N(Sp(q_idx)) - 1;

                if (N(Sp(q_idx)) == 0)
                    RANK(Sp(q_idx)) = i + 1;
                    Q = [Q; Sp(q_idx)];
                end

            end

        end

        i = i + 1;
        PF{i, 1} = Q;
    end

end

% Function that performs a vectorized version of the Fast Non Dominated Sorting
% algorithm which speeds up the computation time
function [RANK] = FastNonDominatedSorting_Vectorized(fitness)
    % Initialization
    Np = size(fitness, 1);
    RANK = zeros(Np, 1);
    current_vector = [1:1:Np]';
    current_pf = 1;
    all_perm = [repmat([1:1:Np]',Np', 1), reshape(repmat([1:1:Np], Np, 1), Np^2, 1)];
    all_perm(all_perm(:, 1) == all_perm(:, 2), :) = [];

    % Computing each Pareto Front
    while ~isempty(current_vector)

        % Check if there is only a single particle
        if length(current_vector) == 1
            RANK(current_vector) = current_pf;
            break;
        end

        % Non-dominated particles
        % Note: nchoosek has an exponential grow in computation time, so
        % it's better to take all the combinations including repetitions using a
        % loops (quasi-linear grow) or repmats (linear grow)
        %all_perm = nchoosek(current_vector,2);
        %all_perm = [all_perm; [all_perm(:,2) all_perm(:,1)]];
        d = dominates(fitness(all_perm(:, 1), :), fitness(all_perm(:, 2), :));
        dominated_particles = unique(all_perm(d == 1, 2));

        % Check if there is no room for more Pareto Fronts
        if sum(~ismember(current_vector, dominated_particles)) == 0
            break;
        end

        % Update ranks and current_vector
        non_dom_idx = ~ismember(current_vector, dominated_particles);
        RANK(current_vector(non_dom_idx)) = current_pf;
        all_perm(ismember(all_perm(:, 1), current_vector(non_dom_idx)), :) = [];
        all_perm(ismember(all_perm(:, 2), current_vector(non_dom_idx)), :) = [];
        current_vector(non_dom_idx) = [];
        current_pf = current_pf + 1;
    end

end

% Function that returns true if x dominates y and false otherwise
function d = dominates(x, y)
    d = (all(x <= y, 2) & any(x < y, 2));
end
