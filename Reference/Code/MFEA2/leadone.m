function obj = leadone(var)

    fit = 0;

    for i = 1:length(var)

        if var(i) == 0
            break;
        end

        fit = fit + var(i);
    end

    obj = -fit;

end
