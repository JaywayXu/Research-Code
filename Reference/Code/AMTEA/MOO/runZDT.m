clc

global maxdim;
f_functions = {'ZDT1', 'ZDT2', 'ZDT3', 'ZDT4', 'ZDT6'};
result_TS = {};
alpha = {};
result_NSGA = {};
maxdim = 30;
trans.TrInt = 10;
reps = 30;

for prob = 1:length(f_functions)
    f_source = f_functions;
    f_source(prob) = [];
    f_target = f_functions{prob};

    allmodels = {}; % transfer stacking models
    save('allmodels','allmodels')
    
    % First source optimization task
    f = f_source{1};
    [L, U] = searchspace(f);
    pop = 100;
    no_of_objs = 2;
    NSGA_II(f, no_of_objs, L, U, pop);

    % second source optimization task
    f = f_source{2};
    [L, U] = searchspace(f);
    pop = 100;
    no_of_objs = 2;
    NSGA_II(f, no_of_objs, L, U, pop);
    
    % third source optimization task
    f = f_source{3};
    [L, U] = searchspace(f);
    pop = 100;
    no_of_objs = 2;
    NSGA_II(f, no_of_objs, L, U, pop);
    
    % fourth source optimization task
    f = f_source{4};
    [L, U] = searchspace(f);
    pop = 100;
    no_of_objs = 2;
    NSGA_II(f, no_of_objs, L, U, pop);

    % target optimization task
    f =f_target;
    [L, U] = searchspace(f);
    pop = 100;
    no_of_objs = 2;

    result_AMT_prob = [];
    alpha_prob = [];
    result_NSGA_prob = [];
    for rep = 1:reps
        disp('AMT enabled')
        trans.transfer = true;
        [score_AMT, alpha_rep] = AMT_NSGA(f, no_of_objs, L, U, pop, trans);
        result_AMT_prob = [result_AMT_prob; score_AMT];
        alpha_prob = [alpha_prob; alpha_rep];

        disp('AMT disabled')
        trans.transfer = false;
        score_NSGA = AMT_NSGA(f, no_of_objs, L, U, pop, trans);
        result_NSGA_prob = [result_NSGA_prob; score_NSGA];
    end

    result_TS{prob} = result_AMT_prob;
    alpha{prob} = alpha_prob;
    result_NSGA{prob} = result_NSGA_prob;

end