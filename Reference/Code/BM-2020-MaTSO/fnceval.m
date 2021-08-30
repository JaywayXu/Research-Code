function [objective,funcCount] = fnceval(Task,rnvec)
    d = Task.dim;
    nvars = rnvec(1:d);
    %minrange = Task.Lb(1:d);
    %maxrange = Task.Ub(1:d);
    %y=maxrange-minrange;
    %vars = y.*nvars + minrange; % decoding
    x=nvars;
    objective=Task.fnc(x);
    funcCount=1;
end