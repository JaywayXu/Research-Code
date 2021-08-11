function res=DRM(Problem,popSize,MaxIt,T_parameter,group,path)
 for T =1:T_parameter(group,3)/T_parameter(group,2)
        t = 1/T_parameter(group,1)*(T-1);
        fprintf(' %d',T);
        tic;
        [PopX,Pareto,POF_iter,Pareto_iter,runTime] = RMMEDA( Problem,popSize,MaxIt, t);
%          fprintf('\n run:%f;',runTime);
         res{T}.rt=toc;
        res{T}.turePOF=getBenchmarkPOF(Problem.Name,group,T,T_parameter );
        res{T}.POF_iter=POF_iter;
        res{T}.POS=PopX;
 end
end