% 画出每个测试用例的每个函数在1Dim上的图像
BM_NUM = 9;
benchNameList = {'CI-HS', 'CI-MS', 'CI-LS', 'PI-HS', 'PI-MS', 'PI-LS', 'NI-HS', 'NI-MS', 'NI-LS'};
lineColor = {'blue', 'red'};
markerColor = {'blue', 'red'};

mkdir('./Results_Figure')

for index = 1:BM_NUM
    Tasks = benchmark(index, 1);
    no_of_tasks = length(Tasks);

    fig = figure('Visible', 'off');
    x = 0:1/200:1;
    f = zeros(size(x));

    for no = 1:no_of_tasks

        for i = 1:length(x)
            f(i) = fnceval(Tasks(no), x(i));
        end

        % 绘制曲线
        fmin = min(f);
        fmax = max(f);
        f = (f - fmin) / (fmax - fmin);
        plot(x, f, ...
            'LineWidth', 1, ...
            'Color', lineColor{no})
        hold on

        % 绘制最低点
        xmin = x(f == min(f)); % f最小值所对应的x坐标
        fmin = min(f);
        plot(xmin, fmin, 'o', ...
            'MarkerEdgeColor', markerColor{no})

        hold on
    end

    title(benchNameList{index})
    legend('Task1 Line', 'Task1 Min Point', 'Task2 Line', 'Task2 Min Point')

    saveas(fig, ['./Results_Figure/', int2str(index), '_', benchNameList{index}, '.png'])
end
