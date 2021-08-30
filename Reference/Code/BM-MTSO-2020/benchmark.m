function Tasks = benchmark(index)
%BENCHMARK function
%   Input
%   - index: the index number of problem set
%
%   Output:
%   - Tasks: benchmark problem set

    switch(index)
        case 1            
            dim = 50;
            Tasks(1).dim = dim;   
            Tasks(1).fnc = 6;   
            Tasks(1).Lb=-100*ones(1,dim);   
            Tasks(1).Ub=100*ones(1,dim);    
            Tasks(1).task_id = 1;
            Tasks(1).index = index;
            
            Tasks(2).dim = dim;   
            Tasks(2).fnc = 6;  
            Tasks(2).Lb=-100*ones(1,dim);   
            Tasks(2).Ub=100*ones(1,dim);     
            Tasks(2).task_id = 2;       
            Tasks(2).index = index;                
        case 2             
            dim = 50;
            Tasks(1).dim = dim;   
            Tasks(1).fnc = 7;
            Tasks(1).Lb=-100*ones(1,dim);   
            Tasks(1).Ub=100*ones(1,dim);    
            Tasks(1).task_id = 1;
            Tasks(1).index = index;

            Tasks(2).dim = dim;   
            Tasks(2).fnc = 7;
            Tasks(2).Lb=-100*ones(1,dim);   
            Tasks(2).Ub=100*ones(1,dim);               
            Tasks(2).task_id = 2;
            Tasks(2).index = index;
     
        case 3 
            dim = 50;
            Tasks(1).dim = dim;   
            Tasks(1).fnc = 17;
            Tasks(1).Lb=-100*ones(1,dim);   
            Tasks(1).Ub=100*ones(1,dim);    
            Tasks(1).task_id = 1;
            Tasks(1).index = index;

            Tasks(2).dim = dim;   
            Tasks(2).fnc = 17;
            Tasks(2).Lb=-100*ones(1,dim);   
            Tasks(2).Ub=100*ones(1,dim);                    
            Tasks(2).task_id = 2;    
            Tasks(2).index = index;   

        case 4 
            dim = 50;
            Tasks(1).dim = dim;   
            Tasks(1).fnc = 13;
            Tasks(1).Lb=-100*ones(1,dim);   
            Tasks(1).Ub=100*ones(1,dim);    
            Tasks(1).task_id = 1;
            Tasks(1).index = index;

            Tasks(2).dim = dim;   
            Tasks(2).fnc = 13;
            Tasks(2).Lb=-100*ones(1,dim);   
            Tasks(2).Ub=100*ones(1,dim);                     
            Tasks(2).task_id = 2;        
            Tasks(2).index = index;     

        case 5
            dim = 50;
            Tasks(1).dim = dim;   
            Tasks(1).fnc = 15;
            Tasks(1).Lb=-100*ones(1,dim);   
            Tasks(1).Ub=100*ones(1,dim);    
            Tasks(1).task_id = 1;
            Tasks(1).index = index;

            Tasks(2).dim = dim;   
            Tasks(2).fnc = 15;
            Tasks(2).Lb=-100*ones(1,dim);   
            Tasks(2).Ub=100*ones(1,dim);                       
            Tasks(2).task_id = 2;        
            Tasks(2).index = index;   

        case 6 
            dim = 50;
            Tasks(1).dim = dim;   
            Tasks(1).fnc = 21;
            Tasks(1).Lb=-100*ones(1,dim);   
            Tasks(1).Ub=100*ones(1,dim);   
            Tasks(1).task_id = 1; 
            Tasks(1).index = index;

            Tasks(2).dim = dim;   
            Tasks(2).fnc = 21;
            Tasks(2).Lb=-100*ones(1,dim);   
            Tasks(2).Ub=100*ones(1,dim);                      
            Tasks(2).task_id = 2;
            Tasks(2).index = index;
        case 7 
            dim = 50;
            Tasks(1).dim = dim;   
            Tasks(1).fnc = 22;
            Tasks(1).Lb=-100*ones(1,dim);   
            Tasks(1).Ub=100*ones(1,dim);   
            Tasks(1).task_id = 1; 
            Tasks(1).index = index;

            Tasks(2).dim = dim;   
            Tasks(2).fnc = 22;
            Tasks(2).Lb=-100*ones(1,dim);   
            Tasks(2).Ub=100*ones(1,dim);                   
            Tasks(2).task_id = 2;
            Tasks(2).index = index;
        case 8 
            dim = 50;
            Tasks(1).dim = dim;   
            Tasks(1).fnc = 5;
            Tasks(1).Lb=-100*ones(1,dim);   
            Tasks(1).Ub=100*ones(1,dim);    
            Tasks(1).task_id = 1;
            Tasks(1).index = index;

            Tasks(2).dim = dim;   
            Tasks(2).fnc = 5;
            Tasks(2).Lb=-100*ones(1,dim);   
            Tasks(2).Ub=100*ones(1,dim);                   
            Tasks(2).task_id = 2;
            Tasks(2).index = index;
        case 9 
            dim = 50;
            Tasks(1).dim = dim;   
            Tasks(1).fnc = 11;
            Tasks(1).Lb=-100*ones(1,dim);   
            Tasks(1).Ub=100*ones(1,dim);    
            Tasks(1).task_id = 1;
            Tasks(1).index = index;

            Tasks(2).dim = dim;   
            Tasks(2).fnc = 16;
            Tasks(2).Lb=-100*ones(1,dim);   
            Tasks(2).Ub=100*ones(1,dim);                          
            Tasks(2).task_id = 2;     
            Tasks(2).index = index;
        case 10 
            dim = 50;
            Tasks(1).dim = dim;   
            Tasks(1).fnc = 20;
            Tasks(1).Lb=-100*ones(1,dim);   
            Tasks(1).Ub=100*ones(1,dim);    
            Tasks(1).task_id = 1;
            Tasks(1).index = index;

            Tasks(2).dim = dim;   
            Tasks(2).fnc = 21;
            Tasks(2).Lb=-100*ones(1,dim);   
            Tasks(2).Ub=100*ones(1,dim);                   
            Tasks(2).task_id = 2;
            Tasks(2).index = index;
    end
end