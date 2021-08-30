function obj = Rastrigin(x,M,opt)
%Rastrigin function
%   - var: design variable vector
%   - M: rotation matrix
%   - opt: shift vector
    var = x;
    dim = length(var);
    var = (M*(var-opt)')';
    obj = 10*dim;
    for i=1:dim
        obj=obj+(var(i)^2 - 10*(cos(2*pi*var(i))));
    end
end