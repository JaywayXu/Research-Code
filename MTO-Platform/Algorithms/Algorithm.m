classdef Algorithm

    properties
        pop_size
        iter_num
        eva_num
    end

    methods

        function obj = Algorithm(pop_size, iter_num, eva_num)
            obj.pop_size = pop_size;
            obj.iter_num = iter_num;
            obj.eva_num = eva_num;
        end

        function obj = setParameter(obj)

        end

        function data = run(obj, Tasks)

        end

    end

end
