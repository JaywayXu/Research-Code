classdef Management

    properties
        reps = 20
        no_of_tasks = 2
        pop_size = 100
        iter_num = 1000
        eva_num = inf
    end

    methods

        function obj = Management(varargin)

            if nargin == 5
                obj.reps = varargin{1};
                obj.no_of_tasks = varargin{2};
                obj.pop_size = varargin{3};
                obj.iter_num = varargin{4};
                obj.eva_num = varargin{5};
            end

        end

        function data = singleRun(obj, Algorithm, Tasks)
            addpath(genpath('../Algorithms'))
            addpath(genpath('../Problems'))
            eval(['tasks = ', Tasks, ';']);
            eval(['algo = ', Algorithm, '(obj.pop_size, obj.iter_num, obj.eva_num);']);
            data = algo.run(tasks);
        end

        function obj = start(obj, Algo_list, Prob_list)
            % initialize the data properties
            for prob = 1:length(Prob_list)

                for algo = 1:length(Algo_list)
                    eval(['data_', Algo_list{algo}, '_', Prob_list{prob}, '.clock = 0;']);
                    eval(['data_', Algo_list{algo}, '_', Prob_list{prob}, '.convergence = [];']);
                end

            end

            for prob = 1:length(Prob_list)

                for rep = 1:obj.reps

                    for algo = 1:length(Algo_list)
                        data = obj.singleRun(Algo_list{algo}, Prob_list{prob});
                        eval(['data_reps = data_', Algorithm, '_', Tasks, ';']);
                        obj.data_reps.clock_time = data_reps + data.clock_time;
                        obj.data_reps.convergence = [data_reps.convergence; data.convergence];
                        eval(['data_', Algo_list{algo}, '_', Prob_list{prob}, '= data_reps;']);
                    end

                end

            end

        end

    end

end
