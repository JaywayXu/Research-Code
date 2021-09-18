% mfea = MFEA;

% [Tasks, ~] = benchmark(1);

% data = mfea.run(Tasks);

% data = singleRun('MFEA', 'CI_H')

addpath('../Utils')
m = Management(2, 2, 100, 500, inf)
% m.singleRun('MFEA', 'CI_H')
m.start({'MFEA'}, {'CI_H', 'CI_M'})
