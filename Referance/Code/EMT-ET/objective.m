function f = objective(x, Problem, T)

    if Problem == 1

        if T == 1
            [n, ~] = size(x);
            q = ones(n, 1) + sum(x(:, 2:end).^2, 2);
            f = [q .* cos(x(:, 1) .* pi / 2), q .* sin(x(:, 1) .* pi / 2)];
        else
            [n, r] = size(x);
            q = ones(n, 1) + 9 / (r - 1) * sum(abs(x(:, 2:end)), 2);
            f = [x(:, 1), q .* (ones(size(q)) - (x(:, 1) ./ q).^2)];
        end

    end

    if Problem == 2

        if T == 1
            [n, ~] = size(x);
            q = ones(n, 1) + sum(100 * ((x(:, 2:end - 1).^2 - x(:, 3:end)).^2 + (ones(size(x(:, 2:end - 1))) - x(:, 2:end - 1)).^2), 2);
            f = [x(:, 1), q .* (ones(size(q)) - (x(:, 1) ./ q).^2)];
        else
            load Mcm2
            load Scm2
            [n, r] = size(x);

            for i = 1:n
                z(i, :) = (Mcm2 * (x(i, 2:end) - Scm2)')';
            end

            q = ones(n, 1) + 9 / (r - 1) * sum(abs(z), 2);
            f = [q .* cos(x(:, 1) .* pi / 2), q .* sin(x(:, 1) .* pi / 2)];
        end

    end

    if Problem == 3

        if T == 1
            [n, ~] = size(x);
            q = ones(n, 1) + sum(x(:, 2:end).^2 - 10 * cos(2 * pi * x(:, 2:end)) + 10 * ones(size(x(:, 2:end))), 2);
            f = [q .* cos(x(:, 1) .* pi / 2), q .* sin(x(:, 1) .* pi / 2)];
        else
            [n, r] = size(x);
            g = 21 + exp(1) - 20 * exp(-0.2 * sqrt(1 / (r - 1) * sum(x(:, 2:end).^2, 2))) - exp(1 / (r - 1) * sum(cos(2 * pi * x(:, 2:end)), 2));
            %         q = 21*ones(n,1) + exp(1)*ones(n,1) - 20*exp(-0.2*sqrt(1/(r-1)*sum(x(:,2:end).^2,2))) - exp(1/(r-1)*sum(cos(2*pi*x(:,2:end)),2));
            f = [x(:, 1), g .* (1 - sqrt(x(:, 1) ./ g))];
        end

    end

    if Problem == 4

        if T == 1
            [n, ~] = size(x);
            q = ones(n, 1) + sum(x(:, 2:end).^2, 2);
            f = [x(:, 1), q .* (ones(size(q)) - sqrt(x(:, 1) ./ q))];
        else
            load Sph2
            [n, ~] = size(x);

            for i = 1:n
                z(i, :) = x(i, 2:end) - Sph2;
            end

            q = ones(n, 1) + sum(z.^2 - 10 * cos(2 * pi * z) + 10 * ones(size(z)), 2);
            f = [x(:, 1), q .* (ones(size(q)) - sqrt(x(:, 1) ./ q))];
        end

    end

    if Problem == 5

        if T == 1
            load Mpm1
            load Spm1
            [n, ~] = size(x);

            for i = 1:n
                z(i, :) = (Mpm1 * (x(i, 2:end) - Spm1)')';
            end

            q = ones(n, 1) + sum(z.^2, 2);
            f = [q .* cos(x(:, 1) .* pi / 2), q .* sin(x(:, 1) .* pi / 2)];
        else
            load Mpm2
            [n, ~] = size(x);

            for i = 1:n
                z(i, :) = (Mpm2 * x(i, 2:end)')';
            end

            q = ones(n, 1) + sum(z.^2 - 10 * cos(2 * pi * z) + 10 * ones(size(z)), 2);
            f = [x(:, 1), q .* (ones(size(q)) - (x(:, 1) ./ q).^2)];
        end

    end

    if Problem == 6

        if T == 1
            [n, r] = size(x);
            a = repmat(1:r - 1, n, 1);
            q = 2 * ones(n, 1) + 1/4000 * sum(x(:, 2:end).^2, 2) - prod(cos(x(:, 2:end) ./ sqrt(a)), 2);
            f = [q .* cos(x(:, 1) .* pi / 2), q .* sin(x(:, 1) .* pi / 2)];
        else
            load Spl2
            [n, r] = size(x);
            z = x(:, 2:end) - repmat(Spl2, n, 1);
            q = 21 * ones(n, 1) + exp(1) * ones(n, 1) - 20 * exp(-0.2 * sqrt(1 / (r - 1) * sum(z.^2, 2))) - exp(1 / (r - 1) * sum(cos(2 * pi * z), 2));
            f = [q .* cos(x(:, 1) .* pi / 2), q .* sin(x(:, 1) .* pi / 2)];
        end

    end

    if Problem == 7

        if T == 1
            [n, ~] = size(x);
            q = ones(n, 1) + sum(100 * (x(:, 2:end - 1).^2 - x(:, 3:end)).^2 + (ones(size(x(:, 2:end - 1))) - x(:, 2:end - 1)).^2, 2);
            f = [q .* cos(x(:, 1) .* pi / 2), q .* sin(x(:, 1) .* pi / 2)];
        else
            [n, ~] = size(x);
            q = ones(n, 1) + sum(x(:, 2:end).^2, 2);
            f = [x(:, 1), q .* (ones(size(q)) - sqrt(x(:, 1) ./ q))];
        end

    end

    if Problem == 8

        if T == 1
            [n, ~] = size(x);
            q = ones(n, 1) + sum(100 * (x(:, 3:end - 1).^2 - x(:, 4:end)).^2 + (ones(size(x(:, 3:end - 1))) - x(:, 3:end - 1)).^2, 2);
            f = [q .* cos(x(:, 1) .* pi / 2) .* cos(x(:, 2) .* pi / 2), q .* cos(x(:, 1) .* pi / 2) .* sin(x(:, 2) .* pi / 2), q .* sin(x(:, 1) .* pi / 2)];
        else
            load Mnm2
            [n, ~] = size(x);

            for i = 1:n
                z(i, :) = Mnm2 * x(i, 3:end)';
            end

            q = ones(n, 1) + sum(z.^2, 2);
            f = [1/2 * sum(x(:, 1:2), 2), q .* (ones(size(q)) - (sum(x(:, 1:2), 2) ./ q / 2).^2)];
        end

    end

    if Problem == 9

        if T == 1
            load Snl1
            [n, ~] = size(x);
            z = x(:, 3:25) - repmat(Snl1, n, 1);
            a = repmat(1:23, n, 1);
            q = 2 * ones(n, 1) + 1/4000 * sum(z.^2, 2) - prod(cos(z ./ sqrt(a)), 2);
            f = [q .* cos(x(:, 1) .* pi / 2) .* cos(x(:, 2) .* pi / 2), q .* cos(x(:, 1) .* pi / 2) .* sin(x(:, 2) .* pi / 2), q .* sin(x(:, 1) .* pi / 2)];
        else
            [n, r] = size(x);
            q = 21 * ones(n, 1) + exp(1) * ones(n, 1) - 20 * exp(-0.2 * sqrt(1 / (r - 2) * sum(x(:, 3:end).^2, 2))) - exp(1 / (r - 2) * sum(cos(2 * pi * x(:, 3:end)), 2));
            f = [1/2 * sum(x(:, 1:2), 2), q .* (ones(size(q)) - (sum(x(:, 1:2), 2) ./ q / 2).^2)];
        end

    end

end
