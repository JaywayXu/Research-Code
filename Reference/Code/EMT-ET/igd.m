function rst = igd(problem, obj, pf)
    [n, t] = size(obj);

    if problem > 7 && t == 3
        load sp
        min = zeros(10000, 1);
        m = 10000;

        for i = 1:10000
            min(i) = 1e20;

            for j = 1:n

                if ((obj(j, 1) - sp(i, 1))^2 + (obj(j, 2) - sp(i, 2))^2 + (obj(j, 3) - sp(i, 3))^2) < min(i)
                    min(i) = sum((obj(j, :) - sp(i, :)).^2);
                    %                 min(i) = (obj(j,1)-sphere(i,1))^2 + (obj(j,2)-sphere(i,2))^2 + (obj(j,3)-sphere(i,3))^2;
                end

            end

        end

    else

        [m, ~] = size(pf);

        for i = 1:m
            min(i) = 1e20;

            if t < 3

                for j = 1:n

                    if ((obj(j, 1) - pf(i, 1))^2 + (obj(j, 2) - pf(i, 2))^2) < min(i)
                        min(i) = (obj(j, 1) - pf(i, 1))^2 + (obj(j, 2) - pf(i, 2))^2;
                    end

                end

            else

                for j = 1:n

                    if ((obj(j, 1) - pf(i, 1))^2 + (obj(j, 2) - pf(i, 2))^2 + (obj(j, 3) - pf(i, 3))^2) < min(i)
                        min(i) = (obj(j, 1) - pf(i, 1))^2 + (obj(j, 2) - pf(i, 2))^2 + (obj(j, 3) - pf(i, 3))^2;
                    end

                end

            end

        end

    end

    rst = sqrt(sum(min)) / m;
end
