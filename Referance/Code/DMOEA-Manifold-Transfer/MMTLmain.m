clc
clear
close all
warning('off')
CreatTruePOF()
con=configure();
repeatMax=con.repeat;
functions=con.TestFunctions;
T_parameter=con.T_parameter;
popSize=con.popSize;

for rep=1:repeatMax
    for testFuncNo=1:size(functions,2)
        Problem=TestFunctions(functions{testFuncNo});
        if Problem.NObj==3
            popSize=150;
        end 
        for group=1:size(T_parameter,1) 
          MaxIt=T_parameter(group,2);
         fprintf('\n MMTL dec:%d runing on: %s, configure: %d, environment:',con.dec,Problem.Name,group);
         res=MMTLMOEAD(Problem,popSize,MaxIt,T_parameter,group);
         [resIGD]=computeMetrics(res);
         fprintf('\n %.3d',resIGD);
        end %configure
    end%testF
end%rep

function [resIGD]=computeMetrics(resStruct)
     for T=1:size(resStruct,2)
        POFIter=resStruct{T}.POF_iter;
        POFbenchmark=resStruct{T}.turePOF;
        for it=1:size(POFIter,2)
            pof=POFIter{it};
            pof(imag(pof)~=0) = abs(pof(imag(pof)~=0));
            igd(it)=IGD(pof',POFbenchmark);
        end
        IGD_T(T)=igd(end);    
     end
     resIGD=mean(IGD_T);
end

