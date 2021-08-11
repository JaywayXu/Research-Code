function [initPopulation] = predictPopulationKnee(tdX,tdY,tsX,tsY,testX,partNum,popSize)

    [predictModel, beta]=IKTrAdaBoostTrain(tdX,tdY,tsX,tsY,partNum);
    PredictVec=TrPredict(testX,predictModel,beta);

    
    initPopulation=[];
    j=0;
    for i=1:1:size(PredictVec,1)
        if PredictVec(i)==1
            j=j+1;
            initPopulation(j,:)=testX(i,:);
        end
    end
    predictPopX=initPopulation';
    
    initPopulation=predictPopX;
    if size(initPopulation,2)>popSize
        initPopulation=initPopulation(:,1:floor(popSize/1.2));
    elseif size(predictPopX,2)==0
        initPopulation=tsX';
        if size(initPopulation,2)>=floor(popSize/1.2)
            initPopulation=initPopulation(:,1:floor(popSize/1.2));
        else
            initPopulation=initPopulation(:,end);
        end
    end
    
end
