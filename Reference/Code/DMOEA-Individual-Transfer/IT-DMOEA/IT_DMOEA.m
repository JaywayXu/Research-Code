function res=IT_DMOEA(Problem,popSize,MaxIt,T_parameter,group)
prePopSize=ceil(popSize/2);
for T = 1:floor(T_parameter(group,3)/T_parameter(group,2))
        t = 1/T_parameter(group,1)*T;
        fprintf(' %d',T);
        if T==1
            [PopX,Pareto,POF_iter] = RMMEDA( Problem,popSize,30, t);     
            sourcePopX=[addNoise(PopX, popSize*1.5, size(PopX,1)) Pareto.X];
            negtiveLabel=-1.*ones(1,size(sourcePopX,2)-size(Pareto.X,2));
            sourceRank=[negtiveLabel,ones(1,size(Pareto.X,2))]; 
        else
        %per-search satge
            prepop=presearch(Problem,t,prePopSize,MaxIt);
            prepopX=getPopEle(prepop,'Position')';
            targetPopX=[addNoise(prepopX, floor(prePopSize*1.5), size(prepopX,1)) prepopX];
            targetRank=computeRank(targetPopX,Problem,t);
            
        %prediction stage
            testPopX=[];
            for i = 1:popSize*100
                testPopX(:,i) = unifrnd(0, 1, [1 size(Problem.XLow,1)]);
            end
            testPopX=[testPopX targetPopX  generateRandomPoints(targetPopX)];
            initPop=predictPopulation(sourcePopX',sourceRank',targetPopX',targetRank',testPopX',popSize);
              
        %evolution 
           [PopX,Pareto,POF_iter] = RMMEDA( Problem,popSize,MaxIt, t,initPop'); 
            sourcePopX=[addNoise(PopX, popSize*1.5, size(PopX,1)) Pareto.X];
            negtiveLabel=-1.*ones(1,size(sourcePopX,2)-size(Pareto.X,2));
            sourceRank=[negtiveLabel,ones(1,size(Pareto.X,2))]; 
            
        end%end 
            
        res{T}.turePOF=getBenchmarkPOF(Problem.Name,group,T,T_parameter );
        res{T}.POF_iter=POF_iter;
        res{T}.POS=PopX;
    end
end





                    