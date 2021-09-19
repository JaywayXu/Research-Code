classdef Problem < handle

    properties
        name
    end

    methods

        function obj = Problem(name)
            obj.name = name;
        end

        function obj = setName(obj, name)
            obj.name = name;
        end

        function name = getName(obj, name)
            name = obj.name;
        end

        function parameter = getParameter(obj)

        end

        function obj = setParameter(obj, parameter_cell)

        end

        function Tasks = getTasks(obj)

        end

    end

end
