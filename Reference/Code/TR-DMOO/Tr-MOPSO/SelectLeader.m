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

function leader=SelectLeader(rep,beta)

    % Grid Index of All Repository Members
    GI=[rep.GridIndex];
    
    % Occupied Cells
    OC=unique(GI);
    
    % Number of Particles in Occupied Cells
    N=zeros(size(OC));
    for k=1:numel(OC)
        N(k)=numel(find(GI==OC(k)));
    end
    
    % Selection Probabilities
    P=exp(-beta*N);
    P=P/sum(P);
    
    % Selected Cell Index
    sci=RouletteWheelSelection(P);
    
    % Selected Cell
    sc=OC(sci);
    
    % Selected Cell Members
    SCM=find(GI==sc);
    
    % Selected Member Index
    smi=randi([1 numel(SCM)]);
    
    % Selected Member
    sm=SCM(smi);
    
    % Leader
    leader=rep(sm);

end