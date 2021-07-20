% 画出每个测试用例的每个函数在1Dim上的图像
BM_NUM = 9;
benchNameList = {'CI-HS', 'CI-MS', 'CI-LS', 'PI-HS', 'PI-MS', 'PI-LS', 'NI-HS', 'NI-MS', 'NI-LS'};

for index = 1:BM_NUM
    Tasks = benchmark(index);
    no_of_tasks = length(Tasks);

    fig = figure('Visible', 'on');
    x = 0:1/100:1;
    y = x;
    [xx, yy] = meshgrid(x, y);
    f = zeros(size(xx));

    for no = 1:no_of_tasks

        for i = 1:size(xx, 1)

            for j = 1:size(xx, 2)
                f(i, j) = fnceval(Tasks(no), [xx(i, j), yy(i, j)]);
            end

        end

        mesh(xx, yy, f, ...
            'LineWidth', 1)
        hold on
    end

    title(benchNameList{index})
    legend(['Task1', 'Task2'])
end
