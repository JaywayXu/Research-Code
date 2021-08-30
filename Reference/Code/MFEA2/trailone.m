function obj = trailone(var)

    fit = 0;

    for i = length(var):-1:1

        if var(i) == 0
            break;
        end

        fit = fit + var(i);
    end

    obj = -fit;

end
