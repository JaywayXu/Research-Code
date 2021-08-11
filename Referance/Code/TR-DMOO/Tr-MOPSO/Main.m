%%
% <html><h2>Main function for Tr-MOPSO</h2></html>

clear
clc

function_name = {'FDA4', 'FDA5', 'FDA5_iso', 'FDA5_dec', 'DIMP2', 'dMOP2', ...
    'dMOP2_iso', 'dMOP2_dec', 'dMOP3', 'HE2', 'HE7', 'HE9'};

for testfunc = 1:1
    clearvars -except testfunc function_name
    
    %% step 1. Initialize objective functions
    [n, Fn, Ft] = getFunc(function_name{testfunc});
    T_parameter = [
        10 5 100
        10 10 200
        10 25 500
        10 50 1000
        1 10 200
        1 50 1000
        20 10 200
        20 50 1000];
    
    nVar    = n;            % Number of Decision Variables
    VarSize = [1 nVar];     % Size of Decision Variables Matrix
    VarMin  = 0;            % Lower Bound of Variables
    VarMax  = 1;            % Upper Bound of Variables
    MaxIt   = 200;          % Max iteration
    nPop    = 200;          % Population Size
    
    %% step 2. Iterate through enviroment parameters
    for group = 1:size(T_parameter,1)
        mkdir(['.\Results\' function_name{testfunc} '\group' num2str(group)]);
        fprintf('running %s \n',function_name{testfunc});
        
        t0 = 0;             % the initial moment
        CostFunction = @(x)Ft(x, t0);
        
        %% step 3. use the MOPSO to get a POF at the initial moment with randomly generated population
        POF = MOPSO(CostFunction, VarMin, VarMax, VarSize, nPop, MaxIt);
        
        % Iterate through time steps
        for T = 1:T_parameter(group,3)/T_parameter(group,2)
           %% step 4. use TCA to get the initial population at the next moment

           % Initialize random populations 
           sampleN = 400;
            for i=1:sampleN
                tempParticle = unifrnd(VarMin, VarMax, VarSize);
                Fs(:,i) = CostFunction(tempParticle);
            end
            t = 1/T_parameter(group,1)*(T-1); % next moment
            CostFunction = @(x)Ft(x, t);
            for i = 1:sampleN
                tempParticle = unifrnd(VarMin, VarMax, VarSize);
                Fa(:,i) = CostFunction(tempParticle);
            end
            
            % Find the latent space of domain adaptation
            mu = 0.5;
            lambda = 'unused';
            dim = 20;           % Deduced dimension
            kind = 'Gaussian';  % The dimension of Gaussian Kernel feature space is inifinite,
            p1 = 1;
            p2 = 'unused';
            p3 = 'unused';
            W = getW(Fs, Fa, mu, lambda, dim, kind, p1, p2, p3);
            POF_deduced = getNewY(Fs, Fa, POF', W, kind, p1, p2, p3);
            
            % Get initial population by POF_deduced
            dis_px = @(p, x)sum((getNewY(Fs, Fa, CostFunction(x)', W, kind, p1, p2, p3) - p).^2);
            initn = size(POF_deduced, 2);
            init_population = zeros(initn, n);
            for i = 1:initn
                init_population(i,:) = fmincon(@(x)dis_px(POF_deduced(:,i), x), rand(1,n), ...
                    [], [], [], [], zeros(1,n), ones(1,n), [], optimset('display', 'off'));
            end
            
            %% step 5. use MOPSO to get the POF at every moment with the initial population
            TruePOF = getBenchmarkPOF(testfunc,group,T);
            FILEPATH = ['.\Results\' function_name{testfunc} '\group' num2str(group) '\'];
            POF = MOPSO(CostFunction, VarMin, VarMax, VarSize, nPop, MaxIt,TruePOF, T, FILEPATH, init_population);
        end
    end
end