classdef Chromosome
    properties
        rnvec;
        objectives;
        convio;
        front;
        CD;
        dominationcount=0;
        dominatedset=[];
        dominatedsetlength=0;
    end
    methods
        function object = initialize(object,dim)
            object.rnvec=rand(1,dim);
        end
                
        function object = evaluate(object,f,L,U)
            var=L+object.rnvec.*(U-L);
            if ischar(f)
                [object.objectives,object.convio] = mo_test_function(var,f);
            else
                error('Function not implemented!')
            end
        end
        
        function object=reset(object)
            object.dominationcount=0;
            object.dominatedset=[];
            object.dominatedsetlength=0;
        end
    end
end