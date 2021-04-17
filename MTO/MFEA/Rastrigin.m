function obj = Rastrigin(var,M)
    dim = length(var);
    opt=0*ones(1,dim);
    var = (M*(var-opt)')';
    obj = 10*dim;
    for i=1:dim
        obj=obj+(var(i)^2 - 10*(cos(2*pi*var(i))));
    end
end