function fitness = trap5(vars)
    % % % %     The trap-5 function
    dims = length(vars);
    index = 1:dims;
    index = vec2mat(index, 5);
    rows = size(index, 1);
    fitsum = 0;

    for j = 1:rows
        contri = sum(vars(index(j, :)));

        if contri == 5
            fitsum = fitsum + 5;
        else
            fitsum = fitsum + (4 - contri);
        end

    end

    fitness = -fitsum;
end
