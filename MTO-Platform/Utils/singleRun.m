function data = singleRun(Algorithm, Tasks)
    addpath(genpath('../Algorithms'))
    addpath(genpath('../Problems'))
    eval(['tasks = ', Tasks, ';']);
    eval(['algo = ', Algorithm, ';']);
    data = algo.run(tasks);
end
