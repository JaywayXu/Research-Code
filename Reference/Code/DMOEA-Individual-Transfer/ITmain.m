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
    for testFuncNo=14:size(functions,2)
        Problem=TestFunctions(functions{testFuncNo});
        if Problem.NObj==3 
            popSize=200;
        end 
        for group=1:size(T_parameter,1) 
            MaxIt=T_parameter(group,2);
            fprintf('\n ITDMOEA rep:%d runing on: %s, configure: %d, environment:',rep,Problem.Name,group);
            res=IT_DMOEA(Problem,popSize,MaxIt,T_parameter,group);
            [resIGD,resMS]=computeMetrics(res);
            fprintf('\n %.3d   %.3d',resIGD,resMS);
    
        end %configure
    end%testF
end%rep




function [resIGD,resMS]=computeMetrics(resStruct)
     for T=1:size(resStruct,2)
        POFIter=resStruct{T}.POF_iter;
        POFbenchmark=resStruct{T}.turePOF;
        for it=1:size(POFIter,2)
            pof=POFIter{it};
            pof(imag(pof)~=0) = abs(pof(imag(pof)~=0));
            igd(it)=IGD(pof',POFbenchmark);
             ms(it)=MS(pof',POFbenchmark);
        end
        IGD_T(T)=igd(end);  
        mstemp=ms(ms<=1&ms>0);
        if length(mstemp)==0
            MS_T(T)=0;
        else
            MS_T(T)=mstemp(end); 
        end
        
     end
     resIGD=mean(IGD_T);
     resMS=mean(MS_T);
end



                    