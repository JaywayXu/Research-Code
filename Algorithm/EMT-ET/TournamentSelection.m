function index = TournamentSelection(K,N,varargin)
    varargin = cellfun(@(S)reshape(S,length(varargin{1}),1),varargin,'UniformOutput',false);
    [~,rank] = sortrows([varargin{:}]);
    [~,rank] = sort(rank);
    Parents  = randi(length(varargin{1}),K,N);
    [~,best] = min(rank(Parents),[],1);
    index    = Parents(best+(0:N-1)*K);
end