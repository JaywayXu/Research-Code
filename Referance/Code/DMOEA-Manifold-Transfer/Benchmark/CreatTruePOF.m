function CreatTruePOF()
clc
clear
close all
warning('off')
con=configure();
T_parameter=con.T_parameter;
functions=con.TestFunctions;
    cnt = 100; 
    for func = 1:size(functions,2)
        funcName=functions{func};
        for group = 1:size(T_parameter,1)
          
            for T = 1:T_parameter(group,3)/T_parameter(group,2)
      
                    dirPath='./Benchmark/pof/';
                    mkdir(dirPath);
                    filename = [dirPath 'POF-nt' num2str(T_parameter(group,1)) '-taut' num2str(T_parameter(group,2)) '-' funcName '-' num2str(T) '.txt'];
                    t = 1/T_parameter(group,1)*(T-1);
                    
                    switch funcName
                        case 'dMOP1'
                            %% dMOP1
                            N = 10;
                            PS = zeros(cnt,N);
                            PF = zeros(cnt,2);
                            PS(:,1) = linspace(0,1,cnt);
                            for i = 1:cnt
                                [PF(i,:),~] = dMOP1(PS(i,:),t);
                            end
                            PF = rm_dominated(PF);
                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'dMOP2'%df1
                            N = 10;
                            G = abs(sin(pi*t/2));
                            H = 0.75*sin(pi*t/2)+1.25;
                            PS=[];
                            PS(:,1) = linspace(0,1,cnt);
                            PS(:,2:N) = G;                         
                            PF = zeros(cnt,2);      
                            for i = 1:cnt
                                [PF(i,:),~] = dMOP2(PS(i,:),t);
                            end
                                                     
                            PF = rm_dominated(PF);
                            
                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y           
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        
                        case 'dMOP3'
                            data=importdata('POF-DMOP3.txt');
                            fid = fopen(filename,'w');
                            for row=1:size(data,1)
                                for col=1:size(data,2)
                                    fprintf(fid,'%f\t',data(row,col));
                                end
                                fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'FDA1'
                            %% FDA1
                            N = 11;
                            PS = zeros(cnt,N) + sin(0.5*pi*t);
                            PF = zeros(cnt,2);
                            PS(:,1) = linspace(0,1,cnt);
                            for i = 1:cnt
                                [PF(i,:),~] = FDA1(PS(i,:),t);
                            end

                            PF = rm_dominated(PF);
                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'FDA2'
                            %% FDA2
                            N = 13;
                            PS = zeros(cnt,N);
                            PF = zeros(cnt,2);
                            PS(:,1) = linspace(0,1,cnt);
                            H = 2*sin(0.5*pi*(t-1));
                            PS(:,N-7:end) = repmat(H/4,cnt,8);
                            for i = 1:cnt
                                [PF(i,:),~] = FDA2(PS(i,:),t);
                            end

                            PF = rm_dominated(PF);
                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'FDA3'
                        %% FDA3
                            N = 10;
                            PS = zeros(cnt,N) + abs(sin(0.5*pi*t));
                            PF = zeros(cnt,2);
                            PS(:,1:2) = repmat(linspace(0,1,cnt)',1,2);
                            for i = 1:cnt
                                [PF(i,:),~] = FDA3(PS(i,:),t);
                            end

                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                         case 'FDA4'
                            data=importdata('POF-FDA4.txt');
                            fid = fopen(filename,'w');
                            for row=1:size(data,1)
                                for col=1:size(data,2)
                                    fprintf(fid,'%f\t',data(row,col));
                                end
                                fprintf(fid,'\r\n');
                            end
                            fclose(fid); 
                            
                           case 'FDA5'
                            N = 12;
                            PS = zeros(100,N);
                            PF = zeros(cnt,3);
                            G = sin(0.5*pi*t);
                            H = 1.25+0.75*sin(pi*t);
                            [X,Y] = meshgrid(0:.01:1, 0:.01:1);
                            PS = [];
                            for i = 1:size(X,1)
                                PS = [PS
                                    [X(:,i) Y(:,i)]];
                            end
                            for i = 1:size(PS,1)
                                PS(i,3:N) = repmat(((PS(i,1)+PS(i,2))/2)^H+G,1,N-2);
                            end
                            for i = 1:size(PS,1)
                                [PF(i,:),~] = FDA5(PS(i,:),t);
                            end

                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                       
                        
                        
                    end
           
            end
        end
    end


end

function [F,V]  = FDA1(X,t)
%% FDA1
    N = 11;
    M = 2;
%     X(2:N) = X(2:N)*2-1;    %X[2:N]属于区间[-1,1]
    f1 = X(1);
    G = sin(0.5*pi*t);
    g = 1 + sum((X(2:N) - G).^2);
    h = 1-sqrt(f1/g);
    F = [f1
        g*h];
    V = 0.0;
end

function [F,V]  = FDA2(X,t)
%% FDA2
    N = 13;
    M = 2;
%     X(2:end) = X(2:end)*2-1;
    f1 = X(1);
    g = 1+sum(X(2:N-8).^2);
    H = 2*sin(0.5*pi*(t-1));
    h = 1-(f1/g)^(2^(H+sum((X(N-7:end)-H/4).^2)));
    F = [f1
        g*h];
    V = 0.0;
end

function [F,V]  = FDA3(X,t)
%% FDA3
    N = 10;
    M = 2;
%     X(3:N) = X(3:N)*2-1;    %X[3:N]属于区间[-1,1]
    F = 10^(2*sin(0.5*pi*t));
    f1 = sum(X(1:2).^F)/2;
    G = abs(sin(0.5*pi*t));
    g = 1 + G +sum((X(3:N)-G).^2);
    h = 1 - sqrt(f1/g);
    F = [f1
        g*h];
    V = 0.0;
end

function [F,V]  = FDA4(X,t)
%% FDA4
    N = 12;
    M = 3;
    G = abs(sin(pi*t/2));
    g = sum((X(M:N) - G).^2);
    F = [(1+g)*prod(cos(X(1:M-1)*pi/2))
        (1+g)*prod(cos(X(1:M-2)*pi/2))*sin(X(M-1)*pi/2)
        (1+g)*sin(X(1)*pi/2)];
    V = 0.0;

end
function [F,V] = FDA5(X,t)
%% FDA5
    N = 12;
    M = 3;    
    G = abs(sin(pi*t/2));
    g = G+sum((X(M:N)-G).^2);
    F = 1+100*sin(pi*t/2)^4;
    y1 = X(1:M-1).^F;
    y2 = X(1:M-2).^F;
    y3 = X(M-1).^F;
    y4 = X(1).^F;
    F = [(1+g)*prod(cos(y1.*pi/2))
        (1+g)*prod(cos(y2*pi/2))*sin(y3*pi/2)
        (1+g)*sin(y4*pi/2)];        
    V = 0.0;
end

function [F,V] = dMOP1(X,t)
%% dMOP1
    N = 10;
    Fn = 2;
    f1 = X(1);
    H = 1.25 + 0.75*sin(0.5*pi*t);
    g = 1+9*sum(X(2:end).^2)/(N-1);
    h = 1-(f1/g)^H;
    F = [f1
        g*h];
    V = 0.0;
    
end


function [F,V] = dMOP2(X,t)
    %% dMOP2
    N = 10;
    Fn = 2;
    H = 0.75*sin(pi*t/2)+1.25;
    G = abs(sin(pi*t/2));
    f1 = X(1);
    g = 1+sum((X(2:end)-G).^2);
    h = 1-(f1/g)^H;    
    F = [f1
        g*h];    
    V = 0.0;
    
end

function [F,V] = dMOP3(X,t)
    %% dMOP3
    n = 10;
    Fn = 2;
    G = abs(sin(pi*t/2));
    f1 = X(1);
    g = 1+sum((X(2:end)-G).^2);
    h = 1-sqrt(f1/g);
    
    F = [f1
        g*h];
    V = 0.0;
end


