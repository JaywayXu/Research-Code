function [initPopulation] = predictPopulation(tdX,tdY,tsX,tsY,testX,popSize)
   

    tX = [tdX ; tsX];
    tY = [tdY ; tsY];
    n = size(tdY,1);
    m = size(tsY,1);
    w = ones(m+n,1);
    predictModel = cell(1,3);
    beta = zeros(1,3);
    for t = 1:3
        p = w./(sum(abs(w)));
        predictModel{t} = svmtrain(w,tY,tX,'-t 0 -q £­h 0 -s 2 ');
        predict = svmpredict(tY,tX,predictModel{t},'-q');
        sW = sum(w(n+1:m+n));
        et = sum(w(n+1:m+n).*(predict(n+1:m+n)~=tsY)/sW);
        if et >= 0.5
            et = 0.499;
        elseif et == 0
            et = 0.001;
        end
        bT = et/(1-et);
        beta(t) =bT;
        b = 1/(1+sqrt(2*log(n/3)));
        wUpdate = [(b*ones(n,1)).^(predict(1:n)~=tdY) ; (bT*ones(m,1)).^(-(predict(n+1:m+n)~=tsY)) ];
        w = w.*wUpdate;
    end
    N = length(predictModel);
    start = ceil(N/2);
    l = size(testX,1);
    yOne = ones(l,1);
    yTwo = ones(l,1);
    PredictVec = ones(l,1);
    for i = start:N
        predict = svmpredict(yOne,testX,predictModel{i},'-q');
        %predict = predict == 1;
        yOne = yOne.*((beta(i)*ones(l,1)).^(-predict));
        yTwo = yTwo.*((beta(i)*ones(l,1)).^(-0.5));
    end
    PredictVec(yOne < yTwo) = -1;
  
    initPopulation=[];
    j=0;
    for i=1:1:size(PredictVec,1)
        if PredictVec(i)==1
            j=j+1;
            initPopulation(j,:)=testX(i,:);
        end
    end
    initPopulation=initPopulation';
    if size(initPopulation,2)>popSize
        initPopulation=initPopulation';
        initPopulation=initPopulation(1:popSize,:);
    elseif size(initPopulation,2)==0
        initPopulation=tsX;
    else
        initPopulation=[initPopulation'];
    end  
    
end
