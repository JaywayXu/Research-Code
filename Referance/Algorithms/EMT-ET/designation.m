function [r, individuals, ns] = designation(Tpopulation, Spopulation, G, source, LBOUND1, UBOUND1, LBOUND2, UBOUND2)
    s = (Tpopulation.sign == 1 & Tpopulation.rank < 2); % 目标问题中的非支配迁移解
    % str=['the number of survived transferred individuals of problem ' num2str(Problem) ' is : ' num2str(sum(s))];
    % disp(str);
    r = sum(s);

    if sum(s) == 0
        %[~,j] = sort(Spopulation.rank);
        individuals = struct('x', [], 'f', [], 'rank', [], 'sign', []);
        ns = 1:G;
        individuals.x = Spopulation.x(1:G, :); % S种群中选取G个个体作为迁移解
        %individuals.x = Spopulation.x(j(1:G),:);
        z = Tpopulation.x(1:G, :);
        individuals.sign = ones(G, 1);
        h = min(length(UBOUND1), length(UBOUND2));

        if source == 1
            % S种群的迁移解线性映射到T种群
            individuals.x(:, 1:h) = (individuals.x(:, 1:h) - repmat(LBOUND1(1:h), G, 1)) ./ repmat(UBOUND1(1:h) - LBOUND1(1:h), G, 1) .* repmat(UBOUND2(1:h) - LBOUND2(1:h), G, 1) + repmat(LBOUND2(1:h), G, 1);

            if min(length(UBOUND1), length(UBOUND2)) < max(length(UBOUND1), length(UBOUND2))
                individuals.x = [individuals.x, z(:, h + 1:end)]; % 用T种群中高维数据补上S种群迁移解中不足的维度
            end

        else
            individuals.x(:, 1:h) = (individuals.x(:, 1:h) - repmat(LBOUND2(1:h), G, 1)) ./ repmat(UBOUND2(1:h) - LBOUND2(1:h), G, 1) .* repmat(UBOUND1(1:h) - LBOUND1(1:h), G, 1) + repmat(LBOUND1(1:h), G, 1);

            if min(length(UBOUND1), length(UBOUND2)) < max(length(UBOUND1), length(UBOUND2))
                individuals.x = individuals.x(:, 1:h);
            end

        end

        %     i = find(Spopulation.rank > 1);
        %     if length(i)>(number-3)
        %         h = 1:(max(round(length(i)/(number-3))-1,1)):length(i);
        %         %     individuals.x = Spopulation.x(j(randi(length(j),1,number)),:);
        %         individuals.x = Spopulation.x([j(1:3);i(h(1:(number-3)))],:);
        %         individuals.sign = ones(number,1);
        %     else
        %         individuals.x = Spopulation.x(j(1:number),:);
        %         individuals.sign = ones(number,1);
        %     end
        %         individuals.x = Spopulation.x(j(1:number),:);
        %         individuals.sign = ones(number,1);
    else
        % T种群中有非支配迁移解
        x = Tpopulation.x(s, :);
        y = Spopulation.x;
        h = min(length(UBOUND1), length(UBOUND2));
        [n, ~] = size(y);

        if source == 1
            x(:, 1:h) = (x(:, 1:h) - repmat(LBOUND2(1:h), r, 1)) ./ repmat(UBOUND2(1:h) - LBOUND2(1:h), r, 1) .* repmat(UBOUND1(1:h) - LBOUND1(1:h), r, 1) + repmat(LBOUND1(1:h), r, 1);
            x = x(:, 1:h);
        else
            x(:, 1:h) = (x(:, 1:h) - repmat(LBOUND1(1:h), r, 1)) ./ repmat(UBOUND1(1:h) - LBOUND1(1:h), r, 1) .* repmat(UBOUND2(1:h) - LBOUND2(1:h), r, 1) + repmat(LBOUND2(1:h), r, 1);
            x = [x, y(1:sum(s), h + 1:end)];
        end

        for t = 1:sum(s)
            % 对T中每个非支配的迁移解，求在原种群S中距离最近的解的索引
            [~, d(:, t)] = sort(sqrt(sum((repmat(x(t, :), n, 1) - y).^2, 2)));
        end

        d = d'
        ns = d(1:G); % 取G个S种群中距离非支配迁移解最近的解，进行本次迁移
        size(ns)
        individuals = struct('x', [], 'f', [], 'rank', [], 'sign', []);
        individuals.x = Spopulation.x(ns, :);
        individuals.sign = ones(G, 1);
        z = Tpopulation.x(1:G, :);
        h = min(length(UBOUND1), length(UBOUND2));

        if source == 1
            individuals.x(:, 1:h) = (individuals.x(:, 1:h) - repmat(LBOUND1(1:h), G, 1)) ./ repmat(UBOUND1(1:h) - LBOUND1(1:h), G, 1) .* repmat(UBOUND2(1:h) - LBOUND2(1:h), G, 1) + repmat(LBOUND2(1:h), G, 1);

            if min(length(UBOUND1), length(UBOUND2)) < max(length(UBOUND1), length(UBOUND2))
                individuals.x = [individuals.x, z(:, h + 1:end)];
            end

        else
            individuals.x(:, 1:h) = (individuals.x(:, 1:h) - repmat(LBOUND2(1:h), G, 1)) ./ repmat(UBOUND2(1:h) - LBOUND2(1:h), G, 1) .* repmat(UBOUND1(1:h) - LBOUND1(1:h), G, 1) + repmat(LBOUND1(1:h), G, 1);

            if min(length(UBOUND1), length(UBOUND2)) < max(length(UBOUND1), length(UBOUND2))
                individuals.x = individuals.x(:, 1:h);
            end

        end

        %     if source == 1
        %         individuals.x = (individuals.x - repmat(LBOUND1,G,1))./repmat(UBOUND1 - LBOUND1,G,1).*repmat(UBOUND2 - LBOUND2,G,1) + repmat(LBOUND2,G,1);
        %     else
        %         individuals.x = (individuals.x - repmat(LBOUND2,G,1))./repmat(UBOUND2 - LBOUND2,G,1).*repmat(UBOUND1 - LBOUND1,G,1) + repmat(LBOUND1,G,1);
        %     end
    end

end
