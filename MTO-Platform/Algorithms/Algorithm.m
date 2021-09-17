classdef Algorithm

    properties
        pop_size = 100
        iter_num = 500
        eva_num = inf
    end

    methods

        function obj = setParameter(obj, pop_size, iter_num, eva_num)
            obj.pop_size = pop_size;
            obj.iter_num = iter_num;
            obj.eva_num = eva_num;
        end

        function data = run(obj, Tasks)

        end

    end

end
