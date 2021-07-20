function objective = fnceval(Task, rnvec)
    %FNCEVAL function: evaluate function in the unified search space
    d = Task.dims;
    nvars = rnvec(1:d);
    minrange = Task.Lb(1:d);
    maxrange = Task.Ub(1:d);
    y = maxrange - minrange;
    vars = y .* nvars + minrange; % decoding
    x = vars;
    objective = Task.fnc(x);
end
