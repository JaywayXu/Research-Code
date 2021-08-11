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

function Grid=CreateGrid(pop,nGrid,alpha)


%     c=[pop.Cost];
    c=[];
    for i =1:size(pop)
        c = [c
            pop(i).Cost];
    end
    cmin=min(c,[],2);
    cmax=max(c,[],2);
    
    dc=cmax-cmin;
    cmin=cmin-alpha*dc;
    cmax=cmax+alpha*dc;
    
    nObj=size(c,1);
    
    empty_grid.LB=[];
    empty_grid.UB=[];
    Grid=repmat(empty_grid,nObj,1);
    
    for j=1:nObj
        
        cj=linspace(cmin(j),cmax(j),nGrid+1);
        
        Grid(j).LB=[-inf cj];
        Grid(j).UB=[cj +inf];
        
    end

end