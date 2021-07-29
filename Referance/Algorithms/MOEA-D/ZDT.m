%
% Copyright (c) 2015, Yarpiz (www.yarpiz.com)
% All rights reserved. Please read the "license.txt" for license terms.
%
% Project Code: YPEA124
% Project Title: Implementation of MOEA/D
% Muti-Objective Evolutionary Algorithm based on Decomposition
% Publisher: Yarpiz (www.yarpiz.com)
%
% Developer: S. Mostapha Kalami Heris (Member of Yarpiz Team)
%
% Contact Info: sm.kalami@gmail.com, info@yarpiz.com
%

function z = ZDT(x)

    n = numel(x);

    f1 = x(1);

    g = 1 + 9 / (n - 1) * sum(x(2:end));

    h = 1 - sqrt(f1 / g);

    f2 = g * h;

    z = [f1
        f2];

end
