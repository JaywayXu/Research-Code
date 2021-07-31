function CrowdDis = CrowdingDistance(PopObj, FrontNo)
    [N, M] = size(PopObj);
    CrowdDis = zeros(1, N);
    Fronts = setdiff(unique(FrontNo), inf);

    for f = 1:length(Fronts)
        Front = find(FrontNo == Fronts(f));
        Fmax = max(PopObj(Front, :), [], 1);
        Fmin = min(PopObj(Front, :), [], 1);

        for i = 1:M
            [~, Rank] = sortrows(PopObj(Front, i));
            CrowdDis(Front(Rank(1))) = inf;
            CrowdDis(Front(Rank(end))) = inf;

            for j = 2:length(Front) - 1
                CrowdDis(Front(Rank(j))) = CrowdDis(Front(Rank(j))) + (PopObj(Front(Rank(j + 1)), i) - PopObj(Front(Rank(j - 1)), i)) / (Fmax(i) - Fmin(i));
            end

        end

    end

end
