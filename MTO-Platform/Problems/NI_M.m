classdef NI_M < Problem

    properties
    end

    methods

        function Tasks = getTasks(obj)
            load('NI_M.mat') % loading data from folder ./Tasks
            dim = 50;
            Tasks(1).dims = dim;
            Tasks(1).fnc = @(x)Griewank(x, Rotation_Task1, GO_Task1);
            Tasks(1).Lb = -100 * ones(1, dim);
            Tasks(1).Ub = 100 * ones(1, dim);

            Tasks(2).dims = dim;
            Tasks(2).fnc = @(x)Weierstrass(x, Rotation_Task2, GO_Task2);
            Tasks(2).Lb = -0.5 * ones(1, dim);
            Tasks(2).Ub = 0.5 * ones(1, dim);
        end

    end

end
