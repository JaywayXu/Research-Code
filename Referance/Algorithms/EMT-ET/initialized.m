function population = initialized(ini_pop, NVARS, LBOUND, UBOUND)
    population = struct('x', [], 'f', [], 'rank', [], 'sign', []);
    population.x = rand(ini_pop, NVARS) .* repmat((UBOUND - LBOUND)', ini_pop, 1) + repmat(LBOUND', ini_pop, 1);
    population.sign = zeros(ini_pop, 1);
end
