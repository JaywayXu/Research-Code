classdef Algorithm < handle

    properties
        name
        pop_size
        iter_num
        eva_num
    end

    methods

        function obj = Algorithm(name, pop_size, iter_num, eva_num)
            obj.name = name;
            obj.pop_size = pop_size;
            obj.iter_num = iter_num;
            obj.eva_num = eva_num;
        end

        function name = getName(obj)
            name = obj.name;
        end

        function setName(obj, name)
            obj.name = name;
        end

        function parameter = getParameter(obj)

        end

        function obj = setParameter(obj)

        end

        function data = run(obj, Tasks)

        end

    end

end
