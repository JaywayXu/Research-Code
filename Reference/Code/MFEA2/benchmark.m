function [Tasks] = benchmark(index)

    % The following set of binary optimization examples appear in the supplemental material of the reference below.

    %       Bali, K. K., Ong, Y. S., Gupta, A., & Tan, P. S. Multifactorial Evolutionary Algorithm with Online Transfer Parameter Estimation: MFEA-II.
    %       IEEE Transactions on Evolutionary Computation, 2019.

    % The MAIN.m file can be used to specify additional parameters such as the
    % population size and generation count.

    %% benchmark function
    %   Input
    %   - index: the index number of problem set
    %
    %   Output:
    %   - Tasks: benchmark problem set

    switch (index)
        case 1 % trap-5 & onemax
            dim = 100;
            Tasks(1).dims = dim; % dimensionality of Task 1
            Tasks(1).fnc = @(x)trap5(x);

            Tasks(2).dims = dim; % dimensionality of Task 2
            p = 1; % probability of generating ones (p=1 --> onemax, p=0 --> zeromax)
            target = randsrc(1, Tasks(2).dims, [0 1; (1 - p) p]); % generating a random target string based on p
            Tasks(2).fnc = @(x)targetRan(x, target);

        case 2 % LeadingOnes and TrailingOnes
            dim = 50;
            Tasks(1).dims = dim; % dimensionality of Task 1
            Tasks(1).fnc = @(x)leadone(x);

            dim = 50;
            Tasks(2).dims = dim;
            Tasks(2).fnc = @(x)trailone(x);

    end

end
