function [objective] = func(func_name, rnvec)

    switch (func_name)
        case 'Ackley'
            lb = -50;
            ub = 50;
            f = @(x)Ackley(x, -0.15, 0);
        case 'Griewank'
            lb = -100;
            ub = 100;
            f = @(x)Griewank(x, -0.15, 0);
        case 'Rastrigin'
            lb = -50;
            ub = 50;
            f = @(x)Rastrigin(x, -0.15, 0);
        case 'Rosenbrock'
            lb = -50;
            ub = 50;
            f = @(x)Rosenbrock(x);
        case 'Schwefel'
            lb = -500;
            ub = 500;
            f = @(x)Schwefel(x);
        case 'Weierstrass'
            lb = -0.5;
            ub = 0.5;
            f = @(x)Weierstrass(x, -0.15, 0);
    end

    y = ub - lb;
    x = y .* rnvec + lb;
    objective = f(x);

end
