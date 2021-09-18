classdef Management

    properties
        reps = 20
        pop_size = 100
        iter_num = 1000
        eva_num = inf
        result
    end

    methods

        function obj = Management(varargin)

            if nargin == 5
                obj.reps = varargin{1};
                obj.pop_size = varargin{3};
                obj.iter_num = varargin{4};
                obj.eva_num = varargin{5};
            end

        end

        function data = singleRun(obj, Algorithm, Tasks)
            addpath(genpath('./Algorithms'));
            addpath(genpath('./Problems'));
            addpath(genpath('../Algorithms'));
            addpath(genpath('../Problems'));
            eval(['tasks = ', Tasks, ';']);
            eval(['algo = ', Algorithm, '(obj.pop_size, obj.iter_num, obj.eva_num);']);
            data = algo.run(tasks);
        end

        function obj = start(obj, Algo_list, Prob_list, app)
            % initialize the result properties
            for algo = 1:length(Algo_list)

                for prob = 1:length(Prob_list)
                    obj.result(algo, prob).clock_time = 0;
                    obj.result(algo, prob).convergence = [];
                end

            end

            % main test loop
            for prob = 1:length(Prob_list)

                for rep = 1:obj.reps

                    for algo = 1:length(Algo_list)
                        data = obj.singleRun(Algo_list{algo}, Prob_list{prob});
                        obj.result(algo, prob).clock_time = obj.result(algo, prob).clock_time + data.clock_time;
                        obj.result(algo, prob).convergence = [obj.result(algo, prob).convergence; data.convergence];

                    end

                end

            end

            % save the data
            savedata.reps = obj.reps;
            savedata.no_of_tasks = obj.no_of_tasks;
            savedata.pop_size = obj.pop_size;
            savedata.iter_num = obj.iter_num;
            savedata.algo_list = Algo_list';
            savedata.prob_list = Prob_list;
            savedata.result = obj.result;
            save('D:\savedata', 'savedata');

        end

    end

end
