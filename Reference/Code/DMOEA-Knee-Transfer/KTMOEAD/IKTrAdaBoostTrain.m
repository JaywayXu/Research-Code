function [model, beta ] = IKTrAdaBoostTrain(tdX,tdY,tsX,tsY,partNum)
    
    tX = [tdX ; tsX];
    tY = [tdY ; tsY];
    n = size(tdY,1);
    m = size(tsY,1);
    cnk=1;
    ck=(n-partNum)/partNum;
    T = 6  ;
    w = ones(m+n,1);
    model = cell(1,T);
    beta = zeros(1,T);
    for t = 1:T

   model{t} = svmtrain(w,tY,tX,'-t 0 -q £­h 0 -s 2 ');
        predict = svmpredict(tY,tX,model{t},'-q');
        if length(predict)==0
            break;
        end
        Ink=0;
        Ik=0;
        for checkp=1:n
            if checkp>length(predict)||checkp>length(tsX)
                break;
            end
        
            if predict(checkp)~=tsX(checkp) && tsX(checkp)==1
                Ik=Ik+1;
            end
            if predict(checkp)~=tsX(checkp) && tsX(checkp)==-1;
                Ink=Ink+1;
            end
        end
        sigama=(ck*Ik+0.001)/(cnk*Ink+0.001);
        sW = sum(w(n+1:m+n));
        et = sum(w(n+1:m+n).*(predict(n+1:m+n)~=tsY)/sW);
        if et >= 0.5
            et = 0.499;
        elseif et == 0
            et = 0.001;
        end
        bT = et/(1-et);
        beta(t) =bT;
        b = 1/(1+sqrt(2*log(n/T)));
        wUpdate = [(b*ones(n,1)).*sigama.^(predict(1:n)~=tdY) ; (bT*ones(m,1)).^(-(predict(n+1:m+n)~=tsY)) ];
        w = w.*wUpdate;
    end
end

