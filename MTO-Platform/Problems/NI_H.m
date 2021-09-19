classdef NI_H < Problem

    properties
    end

    methods

        function Tasks = getTasks(obj)
            load('NI_H.mat') % loading data from folder ./Tasks
            dim = 50;
            Tasks(1).dims = dim;
            Tasks(1).fnc = @(x)Rosenbrock(x);
            Tasks(1).Lb = -50 * ones(1, dim);
            Tasks(1).Ub = 50 * ones(1, dim);

            Tasks(2).dims = dim;
            Tasks(2).fnc = @(x)Rastrigin(x, Rotation_Task2, GO_Task2);
            Tasks(2).Lb = -50 * ones(1, dim);
            Tasks(2).Ub = 50 * ones(1, dim);
        end

    end

end
