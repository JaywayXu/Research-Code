% 画出每个测试用例的每个函数在1Dim上的图像
BM_NUM = 9;
benchNameList = {'CI-HS', 'CI-MS', 'CI-LS', 'PI-HS', 'PI-MS', 'PI-LS', 'NI-HS', 'NI-MS', 'NI-LS'};
faceColor = {'b', 'g'};
markerColor = {'red', 'black'};

mkdir('./Results_Figure_3D')

for index = 1:BM_NUM
    Tasks = benchmark(index, 2);
    no_of_tasks = length(Tasks);

    fig = figure('Visible', 'on');
    x = 0:1/200:1;
    y = x;
    [xx, yy] = meshgrid(x, y);
    f = zeros(size(xx));

    for no = 1:no_of_tasks

        for i = 1:size(xx, 1)

            for j = 1:size(xx, 2)
                f(i, j) = fnceval(Tasks(no), [xx(i, j), yy(i, j)]);
            end

        end

        % 绘制曲面
        fmin = min(min(f));
        fmax = max(max(f));
        f = (f - fmin) / (fmax - fmin);
        surf(xx, yy, f, ...
            'FaceAlpha', 0.5, ...
            'FaceColor', faceColor{no}, ...
            'EdgeColor', 'none')

        % shading interp
        hold on

        % 绘制最低点
        xmin = xx(f == min(min(f))); % f最小值所对应的x坐标；
        ymin = yy(f == min(min(f))); % f最小值所对应的y坐标
        fmin = min(min(f));
        plot3(xmin, ymin, fmin, 'v', ...
            'MarkerSize', 6, ...
            'MarkerEdgeColor', markerColor{no}, ...
            'MarkerFaceColor', markerColor{no})

        hold on
    end

    title(benchNameList{index})
    legend('Task1 Surf', 'Task1 Min Point', 'Task2 Surf', 'Task2 Min Point')

    savefig(fig, ['./Results_Figure_3D/', int2str(index), '_', benchNameList{index}, '.fig'])
end
