clear
clc

load KP_sc_ak
load KP_uc_ak
load KP_wc_ak
load KP_wc_rk
load KP_sc_rk
load KP_uc_rk

allmodels = {};
save('allmodels','allmodels')

% build source probabilistic models
KP_BGA(KP_uc_rk,1000,true);
KP_BGA(KP_sc_rk,1000,true);
KP_BGA(KP_wc_rk,1000,true);
KP_BGA(KP_sc_ak,1000,true);

% AMTEA solving KP_wc_ak
reps = 30;
TrInt = 2;

trans.transfer = true;
trans.TrInt = TrInt;
[bestSol, fitness_hit, alpha] = AMT_BGA(KP_wc_ak, 1000, reps, trans);
% trans.transfer = false;
% [bestSol, fitness_hit, ~] = AMT_BGA(KP_wc_ak, 1000, reps, trans);
