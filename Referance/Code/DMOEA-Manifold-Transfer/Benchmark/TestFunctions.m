function Problem=TestFunctions(testfunc)
con=configure();
DEC=con.dec;
switch testfunc
    case  'FDA1'
        Problem.Name    = 'FDA1';        % name of test problem
        Problem.NObj    = 2;            % number of objectives                               
        Problem.XLow    = zeros(11,1);  % lower boundary of decision variables, it also defines the number of decision variables
        Problem.XUpp    = ones(11,1);   % upper boundary of decision variables
        Problem.FObj    = @FDA1;          % Objective function, please read the definition
    case 'FDA2'
        Problem.Name    = 'FDA2';        % name of test problem
        Problem.NObj    = 2;            % number of objectives                               
        Problem.XLow    = zeros(13,1);  % lower boundary of decision variables, it also defines the number of decision variables
        Problem.XUpp    = ones(13,1);   % upper boundary of decision variables
        Problem.FObj    = @FDA2;          % Objective function, please read the definition
    case  'FDA3'
        Problem.Name    = 'FDA3';        % name of test problem
        Problem.NObj    = 2;            % number of objectives                               
        Problem.XLow    = zeros(10,1);  % lower boundary of decision variables, it also defines the number of decision variables
        Problem.XUpp    = ones(10,1);   % upper boundary of decision variables
        Problem.FObj    = @FDA3;          % Objective function, please read the definition
    case  'FDA4'
        Problem.Name    = 'FDA4';        % name of test problem
        Problem.NObj    = 3;            % number of objectives                               
        Problem.XLow    = zeros(12,1);  % lower boundary of decision variables, it also defines the number of decision variables
        Problem.XUpp    = ones(12,1);   % upper boundary of decision variables
        Problem.FObj    = @FDA4;          % Objective function, please read the definition
    case 'FDA5'
        Problem.Name    = 'FDA5';        % name of test problem
        Problem.NObj    = 3;            % number of objectives                               
        Problem.XLow    = zeros(12,1);  % lower boundary of decision variables, it also defines the number of decision variables
        Problem.XUpp    = ones(12,1);   % upper boundary of decision variables
        Problem.FObj    = @FDA5;          % Objective function, please read the definition
    
    
    case 'dMOP2'
        Problem.Name    = 'dMOP2';        % name of test problem
        Problem.NObj    = 2;            % number of objectives                               
        Problem.XLow    = zeros(10,1);  % lower boundary of decision variables, it also defines the number of decision variables
        Problem.XUpp    = ones(10,1);   % upper boundary of decision variables
        Problem.FObj    = @dMOP2;          % Objective function, please read the definition
    
    case 'dMOP3'
        Problem.Name    = 'dMOP3';        % name of test problem
        Problem.NObj    = 2;            % number of objectives                               
        Problem.XLow    = zeros(10,1);  % lower boundary of decision variables, it also defines the number of decision variables
        Problem.XUpp    = ones(10,1);   % upper boundary of decision variables
        Problem.FObj    = @dMOP3;          % Objective function, please read the definition
    
    
    case 'dMOP1'
        Problem.Name    = 'dMOP1';        % name of test problem
        Problem.NObj    = 2;            % number of objectives                               
        Problem.XLow    = zeros(10,1);  % lower boundary of decision variables, it also defines the number of decision variables
        Problem.XUpp    = ones(10,1);   % upper boundary of decision variables
        Problem.FObj    = @dMOP1;          % Objective function, please read the definition
    
end
end
               

%% test functions
function [F,V]  = FDA1(X,t)
%% FDA1
    N = 11;
    M = 2;
    X(2:N) = X(2:N)*2-1;    %X[2:N]属于区间[-1,1]
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
    X(2:end) = X(2:end)*2-1;
   
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
    X(3:N) = X(3:N)*2-1;    %X[3:N]属于区间[-1,1]
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
    X=X';
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




