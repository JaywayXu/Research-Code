%function obj = Rosenbrock(var,M,opt)
function obj = Rosenbrock(x,M,opt)
%ROSENBROCK function
%   - var: design variable vector
    var = x;
    dim = length(var);
    var = (M*(var-opt)')';
    sum = 0;
    for ii = 1:(dim-1)
        xi = var(ii);
        xnext = var(ii+1);
        new = 100*(xnext-xi^2)^2 + (xi-1)^2;
        sum = sum + new;
    end
    obj = sum  ;
end