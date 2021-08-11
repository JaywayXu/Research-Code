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

function particle=FindGridIndex(particle,Grid)

    nObj=numel(particle.Cost);
    
    nGrid=numel(Grid(1).LB);
    
    particle.GridSubIndex=zeros(1,nObj);
    
    for j=1:nObj
        
        particle.GridSubIndex(j)=...
            find(particle.Cost(j)<Grid.UB,1,'first');
        
    end

    particle.GridIndex=particle.GridSubIndex(1);
    for j=2:nObj
        particle.GridIndex=particle.GridIndex-1;
        particle.GridIndex=nGrid*particle.GridIndex;
        particle.GridIndex=particle.GridIndex+particle.GridSubIndex(j);
    end
    
end