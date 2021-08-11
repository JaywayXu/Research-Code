
function res=TrKneeDMOEA(Problem,popSize,MaxIt,T_parameter,group)
    partNum=10;
    for T = 1:T_parameter(group,3)/T_parameter(group,2)
        t= 1/T_parameter(group,1)*(T-1);   
        fprintf(' %d',T);
        
        if T==1 || T==2
            [PopX,Pareto,POF_iter]=moead( Problem,popSize,MaxIt, t);       
            [kneeF,kneeS]=getKneeGroup(Pareto,partNum);
            LastPopX=PopX;
            LastRank=asignRank(PopX,kneeS);
            kneeArray{T}=kneeS;
        else
   
            kneeS=TPM(kneeArray,T,partNum);
            [PopX,~,~]=moead( Problem,popSize,1, t, kneeS);
            
            Rank=asignRank([PopX kneeS],kneeS);
            PopX=[PopX kneeS];
            testPopX=[generateRandomPoints(PopX) generateRandomPoints(PopX)];
            [initPopulation]=predictPopulationKnee(LastPopX',LastRank',PopX',Rank',testPopX',partNum,popSize);
            [PopX,Pareto,POF_iter]=moead( Problem,popSize,MaxIt, t, initPopulation); 
            [~,kneeS]=getKneeGroup(Pareto,partNum);
            LastPopX=PopX;
            LastRank=asignRank(PopX,kneeS); 
            kneeArray{T}=kneeS;
            
        end
    
        res{T}.POF_iter=POF_iter;
        res{T}.POS=PopX;
        res{T}.turePOF=getBenchmarkPOF(Problem.Name,group,T,T_parameter );
    end

end

function [kneeF,kneeS]=getKneeGroup(Pareto,partNum)
    [boundaryS,boundaryF]=getBoundary(Pareto.X,Pareto.F);
    [posArr,pofArr]=partition(1,Pareto.X,Pareto.F,partNum,boundaryF);
    for partNo=1:partNum
        [kneeS,kneeF]=getKnees(posArr{partNo},pofArr{partNo});
        kneeSArr{partNo}=kneeS;
        kneeFArr{partNo}=kneeF;
    end
    kneeS=cell2mat(kneeSArr);
    kneeF=cell2mat(kneeFArr);
end

% function [resF,resS]=getKneeGroupAllObjective(Pareto,partNum)
%     [boundaryS,boundaryF]=getBoundary(Pareto.X,Pareto.F);
%     for obj=1:size(Pareto.F,1)
%         [posArr,pofArr]=partition(obj,Pareto.X,Pareto.F,partNum,boundaryF);
%         for partNo=1:partNum
%             [kneeS,kneeF]=getKnees(posArr{partNo},pofArr{partNo});
%             kneeSArr{partNo}=kneeS;
%             kneeFArr{partNo}=kneeF;
%         end
%         
%         kneeObj{obj}.S=kneeSArr;
%         kneeObj{obj}.F=kneeFArr;
%     end
%     
%     for obj=2:size(Pareto.F,1)
%         for i=1:size(kneeObj{obj}.F,2)
%              if sum(cell2mat(kneeObj{obj}.F(:,i)))<sum(cell2mat(  kneeObj{1}.F(:,size(kneeObj{obj}.F,2)-i+1)   ))
%                  resF(:,i)=kneeObj{obj}.F(:,i);
%                  resS(:,i)=kneeObj{obj}.S(:,i);
%              else
%                  resF(:,i)=kneeObj{1}.F(:,size(kneeObj{obj}.F,2)-i+1);
%                  resS(:,i)=kneeObj{1}.S(:,size(kneeObj{obj}.F,2)-i+1);
%              end
%         end
%     end
%      resS=cell2mat(resS);
%      resF=cell2mat(resF);
% end

function Rank=asignRank(PopX,KneeX)
for i=1:size(PopX,2)
    for j=1:size(KneeX,2)
        if isequal(PopX(:,i),KneeX(:,j))==1
            Rank(i)=1;
            break;
        else
            Rank(i)=-1;
        end
    end
end
end
