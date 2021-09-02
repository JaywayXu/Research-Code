% 画出每个测试用例的每个函数在1Dim上的图像
funcNameList = {'Ackley', 'Griewank', 'Rastrigin', 'Rosenbrock', 'Schwefel', 'Weierstrass'};

mkdir('./Results_Figure_ST')

for index = 1:length(funcNameList)

    fig = figure('Visible', 'off');
    x = 0:1/200:1;
    f = zeros(size(x));

    for i = 1:length(x)
        f(i) = func(funcNameList{index}, x(i));
    end

    % 绘制曲线
    plot(x, f, ...
        'LineWidth', 1, ...
        'Color', 'blue')
    hold on

    % 绘制最低点
    xmin = x(f == min(f)); % f最小值所对应的x坐标
    fmin = min(f);
    plot(xmin, fmin, 'o', ...
        'MarkerEdgeColor', 'red')

    hold on

    title(funcNameList{index})

    saveas(fig, ['./Results_Figure_ST/', funcNameList{index}, '.png'])
end
