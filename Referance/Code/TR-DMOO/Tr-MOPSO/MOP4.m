%
% Copyright (c) 2015, Yarpiz (www.yarpiz.com)
% All rights reserved. Please read the "license.txt" for license terms.
%
% Project Code: YPEA121
% Project Title: Multi-Objective Particle Swarm Optimization (MOPSO)
% Publisher: Yarpiz (www.yarpiz.com)
% 
% Developer: S. Mostapha Kalami Heris (Member of Yarpiz Team)
% 
% Contact Info: sm.kalami@gmail.com, info@yarpiz.com
%

function z=MOP4(x)

    a=0.8;
    
    b=3;
    
    z1=sum(-10*exp(-0.2*sqrt(x(1:end-1).^2+x(2:end).^2)));
    
    z2=sum(abs(x).^a+5*(sin(x)).^b);
    
    z=[z1 z2]';

end