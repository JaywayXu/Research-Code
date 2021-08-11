function con=configure()
con.T_parameter = [
    5 10 500
                    ];%% time parameters   nt tauT tau  T=p3/p2 

con.TestFunctions = {'DF1','DF2','DF3','DF4','DF5','DF6','DF7','DF8','DF9','DF10','DF11','DF12','DF13','DF14','F5','F6','F7','F8','F9','F10'};
con.popSize=100;
con.repeat=1;
con.dec=10;


end