function con=configure()
con.T_parameter = [
    5 10 100
                    ];%% time parameters   nt tauT tau  

con.TestFunctions = {'DF1'};
con.popSize=100;
con.repeat=10;
con.dec=10; 
end