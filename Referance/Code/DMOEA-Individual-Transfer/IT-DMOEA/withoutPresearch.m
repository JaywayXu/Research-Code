function res=withoutPresearch(Problem,popSize,MaxIt,T_parameter,group)
prePopSize=ceil(popSize/2);
for T = 1:floor(T_parameter(group,3)/T_parameter(group,2))
    t = 1/T_parameter(group,1)*T;
    fprintf(' %d',T);
    if T~=1 
        %prediction stage
        prepop=presearch(Problem,t,prePopSize,0); %notice that the iteration number is 0 so that it outputs a random population directly without optimizing
        prepopX=getPopEle(prepop,'Position')';
        targetPopX=[addNoise(prepopX, floor(prePopSize*1.5), size(prepopX,1)) prepopX];
        targetRank=computeRank(targetPopX,Problem,t);
        testPopX=[ targetPopX   generateRandomPoints(PopX) ];
        initPop=predictPopulation(sourcePopX',sourceRank',targetPopX',targetRank',testPopX',popSize);
    else
        DX = size(Problem.XLow,1);     
        for i=1:1:DX
            LInd(i,:)= randperm(popSize);
        end
        initPop = (LInd - rand(DX,popSize))/popSize .* ((Problem.XUpp-Problem.XLow)*ones(1,popSize)) + Problem.XLow*ones(1,popSize);
        initPop=initPop';
    end
    %evolution 
    [PopX,Pareto,POF_iter] = RMMEDA( Problem,popSize,MaxIt, t,initPop');           
    sourcePopX=[addNoise(PopX, popSize*1.5, size(PopX,1)) Pareto.X];
    negtiveLabel=-1.*ones(1,size(sourcePopX,2)-size(Pareto.X,2));
    sourceRank=[negtiveLabel,ones(1,size(Pareto.X,2))]; 

    res{T}.turePOF=getBenchmarkPOF(Problem.Name,group,T,T_parameter );
    res{T}.POF_iter=POF_iter;
    res{T}.POS=PopX;
end
end





                    