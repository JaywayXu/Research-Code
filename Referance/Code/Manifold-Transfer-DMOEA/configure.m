function con=configure()
con.T_parameter = [
    10 10 100
                    ];%% time parameters   nt tauT tau  

con.TestFunctions = {'FDA1','FDA2','FDA3','FDA4','FDA5','dMOP1','dMOP2','dMOP3'};
con.popSize=100;
con.repeat=1;
con.dec=10; 
end