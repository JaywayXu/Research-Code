classdef Chromosome

    properties
        rnvec;
        objs_T1;
        objs_T2;
        convio;
        skill_factor;
        front;
        CD;
        rank;
        dominationcount = 0;
        dominatedset = [];
        dominatedsetlength = 0;
    end

    methods

        function object = initialize(object, dim)
            object.rnvec = rand(1, dim);
        end

        function object = evaluate(object, L1, U1, f1, L2, U2, f2, dim1, dim2, M1, M2)

            if object.skill_factor == 1
                xtemp = object.rnvec(1:dim1);
                x = L1 + xtemp .* (U1 - L1);
                x(2:dim1) = M1 * x(2:dim1)';
                [object.objs_T1, object.convio] = mo_test_function(x, f1);
                % % % % % % %                 if dim1 < dim2 % Perform random association between genes for tasks with different chromosome lengths if no prior domain knowledge available
                % % % % % % %                     for i = dim1+1:dim2
                % % % % % % %                         object.rnvec(i) = object.rnvec(round(rand(1)*(dim1-1))+1);
                % % % % % % %                     end
                % % % % % % %                 end
            else
                xtemp = object.rnvec(1:dim2);
                x = L2 + xtemp .* (U2 - L2);
                x(2:dim2) = M2 * x(2:dim2)';
                [object.objs_T2, object.convio] = mo_test_function(x, f2);
                % % % % % % %                 if dim2 < dim1 % Perform random association between genes for tasks with different chromosome lengths if no prior domain knowledge available
                % % % % % % %                     for i = dim2+1:dim1
                % % % % % % %                         object.rnvec(i) = object.rnvec(round(rand(1)*(dim2-1))+1);
                % % % % % % %                     end
                % % % % % % %                 end
            end

        end

        function population = reset(population, pop)

            for i = 1:pop
                population(i).dominationcount = 0;
                population(i).dominatedset = [];
                population(i).dominatedsetlength = 0;
            end

        end

    end

end
