function obj = targetRan(var, target)
    %minimizes the hamming distance to a given target string

    obj = pdist2(var, target, 'hamming');

end
