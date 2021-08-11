
function [pop, params] = SortAndSelectIndividuals(pop, params)

    [pop, params] = NormalizePopulation(pop, params);
    nPop = params.nPop;
    [pop, d, rho] = AssociateToReferencePoint(pop, params);

    zmin=params.zmin;
    for refNo=1:params.nZr
        groupByRef{refNo}=[];
    end
    
    for i=1:size(pop,1)
        groupByRef{pop(i).AssociatedRef}=[groupByRef{pop(i).AssociatedRef},pop(i)];
    end
    
    for refNo=1:params.nZr
        if size(groupByRef{refNo},2)==0
            cur=1;
            while refNo+cur<=length(groupByRef)  
                if size(groupByRef{refNo+cur},2)~=0
                    groupByRef{refNo}=groupByRef{refNo+cur};
                    break;
                end   
                cur=cur+1;
            end   
        end 
    end
    
    for refNo=1:params.nZr
        if size(groupByRef{refNo},2)==0
        cur=params.nZr;
            while refNo-cur>=1 
                if size(groupByRef{refNo-cur},2)~=0
                    groupByRef{refNo}=groupByRef{refNo-cur};
                    break;
                end
                cur=cur-1;
            end 
        end
    end
    
    for refNo=1:params.nZr
         if size(groupByRef{refNo},2)==1      
            groupByRef{refNo}=[groupByRef{refNo} groupByRef{refNo}];
        end
    end
    
    for refNo=1:params.nZr
        for i=1:size(groupByRef{refNo},2)
            d2=groupByRef{refNo}(i).DistanceToAssociatedRef;
            d1=norm(zmin-groupByRef{refNo}(i).NormalizedCost);
            groupByRef{refNo}(i).gpbi=d1+(1/6)*d2;
        end            
    end
    
    newpop=[];
    for refNo=1:params.nZr
        if size(groupByRef{refNo},2)>=2      
            gpbivalue=[groupByRef{refNo}.gpbi];
            [~,pos]=sort(gpbivalue);
            individual1=rmfield(groupByRef{refNo}(pos(1)),'gpbi');
            individual2=rmfield(groupByRef{refNo}(pos(2)),'gpbi');
            newpop=[newpop,individual1,individual2];
        end
    end

    pop=newpop;   
  %  [pop, F] = NonDominatedSorting(newpop);

end
