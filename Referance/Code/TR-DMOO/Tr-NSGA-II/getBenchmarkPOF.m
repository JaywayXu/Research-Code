function POF_Benchmark = getBenchmarkPOF( testfunc,group,T )
     T_paramiter = [10 5 100
           10 10 200
           10 25 500
           10 50 1000
           1 10 200
           1 50 1000
           20 10 200
           20 50 1000];
           
    switch testfunc
        case 1
            tempFuncName = 'FDA4';
        case 2
            tempFuncName = 'FDA5';
        case 3
            tempFuncName = 'FDA5';
        case 4
            tempFuncName = 'FDA5';      
        case 5
            tempFuncName = 'DIMP2';
        case 6
            tempFuncName = 'DMOP2';
        case 7
            tempFuncName = 'DMOP2';
        case 8
            tempFuncName = 'DMOP2';
        case 9
            tempFuncName = 'DMOP3';
        case 10
            tempFuncName = 'HE2';
        case 11
            tempFuncName = 'HE7';
        case 12
            tempFuncName = 'HE9';
    end
    tempPosition = T_paramiter(group,2)*T-1;
    POF_Benchmark = importdata(['..\TruePOF\pof\measures\pof\' 'POF-nt' num2str(T_paramiter(group,1)) '-taut' num2str(T_paramiter(group,2)) '-' tempFuncName '-' num2str(tempPosition) '.txt']);
end

