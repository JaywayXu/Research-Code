function GenKnapsack()
    n = 1000;
    v=10;
    r=5;
    type_wp = 'uc'; % strong or weakly or un-correlated
    type_c = 'rk'; % average or restrictive knapsack --- ALWAYS we choose average
    w = 1+round(rand(1,n)*(v-1));
    if strcmp(type_wp,'uc')
        p = 1+round(rand(1,n)*(v-1));
    elseif strcmp(type_wp,'wc')
        p = w + round(r - 2*r*rand(1,n));
        p(p <= 0) = w(p <= 0);
    elseif strcmp(type_wp,'sc')
        p = w+r;
    end
    if strcmp(type_c,'rk')
        cap = 2*v;
    elseif strcmp(type_c,'ak')
        cap = 0.5*sum(w);
    end
    
    th_best = knapsack(w,p,cap)
    
    KP_uc_rk.w = w;
    KP_uc_rk.p = p;
    KP_uc_rk.cap = cap;
    KP_uc_rk.opt = th_best;
    
    save('KP_uc_rk','KP_uc_rk')
end