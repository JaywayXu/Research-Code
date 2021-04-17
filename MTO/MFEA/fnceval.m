function [objective,rnvec,funcCount] = fnceval(Task,rnvec,p_il,options)
    d = Task.dims;
    nvars = rnvec(1:d);
    minrange = Task.Lb(1:d);
    maxrange = Task.Ub(1:d);
    y=maxrange-minrange;
    vars = y.*nvars + minrange;
    if rand(1)<=p_il
        [x,objective,exitflag,output] = fminunc(Task.fnc,vars,options);
        nvars= (x-minrange)./y;
        m_nvars=nvars;
        m_nvars(nvars<0)=0;
        m_nvars(nvars>1)=1;
        if ~isempty(m_nvars~=nvars)
            nvars=m_nvars;
            x=y.*nvars + minrange;
            objective=Task.fnc(x);
        end
        rnvec(1:d)=nvars;
        funcCount=output.funcCount;
    else
        x=vars;
        objective=Task.fnc(x);
        funcCount=1;
    end
end