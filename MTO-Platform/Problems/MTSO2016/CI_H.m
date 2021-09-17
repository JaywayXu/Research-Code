function Tasks = CI_H
    load('CI_H.mat') % loading data from folder ./Tasks
    dim = 50;
    Tasks(1).dims = dim; % dimensionality of Task 1
    Tasks(1).fnc = @(x)Griewank(x, Rotation_Task1, GO_Task1);
    Tasks(1).Lb = -100 * ones(1, dim); % Upper bound of Task 1
    Tasks(1).Ub = 100 * ones(1, dim); % Lower bound of Task 1

    Tasks(2).dims = dim; % dimensionality of Task 2
    Tasks(2).fnc = @(x)Rastrigin(x, Rotation_Task2, GO_Task2);
    Tasks(2).Lb = -50 * ones(1, dim); % Upper bound of Task 2
    Tasks(2).Ub = 50 * ones(1, dim); % Lower bound of Task 2
end
