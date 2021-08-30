function [objective,funcCount] = fnceval(Task,rnvec)
    d = Task.dim;
    nvars = rnvec(1:d);
    %minrange = Task.Lb(1:d);
    %maxrange = Task.Ub(1:d);
    %y=maxrange-minrange;
    %vars = y.*nvars + minrange; % decoding
    x=nvars;
    objective=cec14_func(x', Task.fnc, Task.index, Task.task_id);
    funcCount=1;
end