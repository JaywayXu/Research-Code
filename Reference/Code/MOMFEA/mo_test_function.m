function [obj, convio] = mo_test_function(x, fun)

    D = length(x);
    convio = 0;
    % ZDT4
    if strcmp(fun, 'ZDT4-R')
        y = x(2:end);
        gx = 1 + 10 * (D - 1) + sum(y .* y - 10 * cos(4 * pi * y));
        obj(1) = x(1);
        obj(2) = gx * (1 - sqrt(x(1) / gx));
    end

    if strcmp(fun, 'ZDT4-A')
        y = x(2:end);
        gx = -20 * exp(-0.2 * sqrt(sum(y.^2) / (D - 1))) - exp(sum(cos(2 * pi * y)) / (D - 1)) + 21 + exp(1);
        obj(1) = x(1);
        obj(2) = gx * (1 - sqrt(x(1) / gx));
    end

    if strcmp(fun, 'ZDT4-G')
        y = x(2:end);
        gx = 2 + sum(y.^2) / 4000;
        gx_2 = 1;

        for i = 2:D
            gx_2 = gx_2 * cos(x(i) / sqrt(i));
        end

        gx = gx - gx_2;
        obj(1) = x(1);
        obj(2) = gx * (1 - sqrt(x(1) / gx));
    end

    if strcmp(fun, 'ZDT4-RC')
        y = x(2:end);
        gx = 1 + 10 * (D - 1) + sum(y .* y - 10 * cos(4 * pi * y));
        obj(1) = x(1);
        obj(2) = gx * (1 - sqrt(x(1) / gx));
        f1 = obj(1);
        f2 = obj(2);
        theta = -0.05 * pi;
        a = 40;
        b = 5;
        c = 1;
        d = 6;
        e = 0;
        convio = (a * abs(sin(b * pi * (sin(theta) * (f2 - e) + cos(theta) * f1)^c))^d) - cos(theta) * (f2 - e) + sin(theta) * f1;

        if convio <= 0
            convio = 0;
        end

    end

end
