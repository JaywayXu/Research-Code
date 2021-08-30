% clear 
clc
allmodels = {};
save('allmodels','allmodels');

reps = 30;
TrInt = 2;

% build source probabilistic models 
BGA('onemax',100,100);
BGA('onemin',100,100);

% AMTEA
trans.transfer = true;
trans.TrInt = TrInt;
[bestSol, fitness_hist, alpha] = AMT_BGA('trap5', 100, reps, trans);
% trans.transfer = false;
% [bestSol, fitness_hist, alpha] = AMT_BGA('trap5', 100, reps, trans);