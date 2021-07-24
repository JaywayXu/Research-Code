% ----------------------------------------------------------------------- %
% Example of use of the funcion NSGAII.m, which performs a Non Sorting Gene-
% tic Algorithm II (NSGA-II), based on Deb2002.                           %
% ----------------------------------------------------------------------- %
%   Author:  Victor Martinez Cagigal                                      %
%   Date:    22/12/2017                                                   %
%   E-mail:  vicmarcag (at) gmail (dot) com                               %
% ----------------------------------------------------------------------- %
%   References:                                                           %
%    [1] Deb, K., Pratap, A., Agarwal, S., & Meyarivan, T. A. M. T. (2002)%
%        A fast and elitist multiobjective genetic algorithm: NSGA-II.    %
%        IEEE transactions on evolutionary computation, 6(2), 182-197.    %
% ----------------------------------------------------------------------- %
clear all; clc; close all;

% Multi-objective function

MultiObjFnc = 'Schaffer';
% MultiObjFnc = 'Kursawe';
% MultiObjFnc = 'Poloni';
% MultiObjFnc = 'Viennet2';
% MultiObjFnc = 'Viennet3';
% MultiObjFnc = 'ZDT1';
% MultiObjFnc = 'ZDT2';
% MultiObjFnc = 'ZDT3';
% MultiObjFnc = 'ZDT6';

switch MultiObjFnc
    case 'Schaffer' % Schaffer
        MultiObj.fun = @(x) [x(:).^2, (x(:) - 2).^2];
        MultiObj.nVar = 1;
        MultiObj.var_min = -5;
        MultiObj.var_max = 5;
        load('Schaffer.mat');
        MultiObj.truePF = PF;
    case 'Kursawe' % Kursawe
        MultiObj.fun = @(x) [-10 .* (exp(-0.2 .* sqrt(x(:, 1).^2 + x(:, 2).^2)) + exp(-0.2 .* sqrt(x(:, 2).^2 + x(:, 3).^2))), ...
                            sum(abs(x).^0.8 + 5 .* sin(x.^3), 2)];
        MultiObj.nVar = 3;
        MultiObj.var_min = -5 .* ones(1, MultiObj.nVar);
        MultiObj.var_max = 5 .* ones(1, MultiObj.nVar);
        load('Kursawe.mat');
        MultiObj.truePF = PF;
    case 'Poloni' % Poloni's two-objective
        A1 = 0.5 * sin(1) - 2 * cos(1) + sin(2) - 1.5 * cos(2);
        A2 = 1.5 * sin(1) - cos(1) + 2 * sin(2) - 0.5 * cos(2);
        B1 = @(x, y) 0.5 .* sin(x) - 2 .* cos(x) + sin(y) - 1.5 .* cos(y);
        B2 = @(x, y) 1.5 .* sin(x) - cos(x) + 2 .* sin(y) - 0.5 .* cos(y);
        f1 = @(x, y) 1 + (A1 - B1(x, y)).^2 + (A2 - B2(x, y)).^2;
        f2 = @(x, y) (x + 3).^2 + (y + 1).^2;
        MultiObj.fun = @(x) [f1(x(:, 1), x(:, 2)), f2(x(:, 1), x(:, 2))];
        MultiObj.nVar = 2;
        MultiObj.var_min = -pi .* ones(1, MultiObj.nVar);
        MultiObj.var_max = pi .* ones(1, MultiObj.nVar);
    case 'Viennet2' % Viennet2
        f1 = @(x, y) 0.5 .* (x - 2).^2 + (1/13) .* (y + 1).^2 + 3;
        f2 = @(x, y) (1/36) .* (x + y - 3).^2 + (1/8) .* (-x + y + 2).^2 - 17;
        f3 = @(x, y) (1/175) .* (x + 2 .* y - 1).^2 + (1/17) .* (2 .* y - x).^2 - 13;
        MultiObj.fun = @(x) [f1(x(:, 1), x(:, 2)), f2(x(:, 1), x(:, 2)), f3(x(:, 1), x(:, 2))];
        MultiObj.nVar = 2;
        MultiObj.var_min = [-4, -4];
        MultiObj.var_max = [4, 4];
        load('Viennet2.mat');
        MultiObj.truePF = PF;
    case 'Viennet3' % Viennet3
        f1 = @(x, y) 0.5 .* (x.^2 + y.^2) + sin(x.^2 + y.^2);
        f2 = @(x, y) (1/8) .* (3 .* x - 2 .* y + 4).^2 + (1/27) .* (x - y + 1).^2 +15;
        f3 = @(x, y) (1 ./ (x.^2 + y.^2 + 1)) - 1.1 .* exp(-(x.^2 + y.^2));
        MultiObj.fun = @(x) [f1(x(:, 1), x(:, 2)), f2(x(:, 1), x(:, 2)), f3(x(:, 1), x(:, 2))];
        MultiObj.nVar = 2;
        MultiObj.var_min = [-3, -10];
        MultiObj.var_max = [10, 3];
        load('Viennet3.mat');
        MultiObj.truePF = PF;
    case 'ZDT1' % ZDT1 (convex)
        g = @(x) 1 + 9 .* sum(x(:, 2:end), 2) ./ (size(x, 2) - 1);
        MultiObj.fun = @(x) [x(:, 1), g(x) .* (1 - sqrt(x(:, 1) ./ g(x)))];
        MultiObj.nVar = 30;
        MultiObj.var_min = zeros(1, MultiObj.nVar);
        MultiObj.var_max = ones(1, MultiObj.nVar);
        load('ZDT1.mat');
        MultiObj.truePF = PF;
    case 'ZDT2' % ZDT2 (non-convex)
        f = @(x) x(:, 1);
        g = @(x) 1 + 9 .* sum(x(:, 2:end), 2) ./ (size(x, 2) - 1);
        h = @(x) 1 - (f(x) ./ g(x)).^2;
        MultiObj.fun = @(x) [f(x), g(x) .* h(x)];
        MultiObj.nVar = 30;
        MultiObj.var_min = zeros(1, MultiObj.nVar);
        MultiObj.var_max = ones(1, MultiObj.nVar);
        load('ZDT2.mat');
        MultiObj.truePF = PF;
    case 'ZDT3' % ZDT3 (discrete)
        f = @(x) x(:, 1);
        g = @(x) 1 + (9 / size(x, 2) - 1) .* sum(x(:, 2:end), 2);
        h = @(x) 1 - sqrt(f(x) ./ g(x)) - (f(x) ./ g(x)) .* sin(10 .* pi .* f(x));
        MultiObj.fun = @(x) [f(x), g(x) .* h(x)];
        MultiObj.nVar = 30;
        MultiObj.var_min = 0 .* ones(1, MultiObj.nVar);
        MultiObj.var_max = 1 .* ones(1, MultiObj.nVar);
        load('ZDT3.mat');
        MultiObj.truePF = PF;
    case 'ZDT6' % ZDT6 (non-uniform)
        f = @(x) 1 - exp(-4 .* x(:, 1)) .* sin(6 .* pi .* x(:, 1));
        g = @(x) 1 + 9 .* (sum(x(:, 2:end), 2) ./ (size(x, 2) - 1)).^0.25;
        h = @(x) 1 - (f(x) ./ g(x)).^2;
        MultiObj.fun = @(x) [f(x), g(x) .* h(x)];
        MultiObj.nVar = 10;
        MultiObj.var_min = 0 .* ones(1, MultiObj.nVar);
        MultiObj.var_max = 1 .* ones(1, MultiObj.nVar);
        load('ZDT6.mat');
        MultiObj.truePF = PF;
end

% Parameters
params.Np = 200; % Population size
params.pc = 0.9; % Probability of crossover
params.pm = 0.5; % Probability of mutation
params.maxgen = 100; % Maximum number of generations
params.ms = 0.05; % Mutation strength

% NSGA-II algorithm
NSGAII(params, MultiObj);
