file_name = '../../Data/data_A_all.xlsx';
% file_name = 'data_A_all.xlsx';
fig_dict = '../../Figure/';
mA = readmatrix(file_name, 'Sheet', 1);

predict_A = zeros(1, 5);
predict_list = zeros(9, 5);

for ai = 1:5 % A1-A5
    y = mA(:, ai)';
    year_x = 2012; % 坐标偏移（年份）

    if ai == 2 || ai == 5
        y = y(2:end);
        year_x = 2014;
    end

    % 灰色预测
    n = length(y);
    yy = ones(n, 1);
    yy(1) = y(1);

    for i = 2:n
        yy(i) = yy(i - 1) + y(i);
    end

    B = ones(n - 1, 2);
    YN = zeros(1, n - 1);

    for i = 1:(n - 1)
        B(i, 1) = -(yy(i) + yy(i + 1)) / 2;
        B(i, 2) = 1;
    end

    BT = B';

    for j = 1:(n - 1)
        YN(j) = y(j + 1);
    end

    YN = YN';
    A = inv(BT * B) * BT * YN;
    a = A(1);
    u = A(2);
    t = u / a;
    t_test = 1; % 需要预测的个数
    i = 1:t_test + n;
    yys(i + 1) = (y(1) - t) .* exp(-a .* i) + t;
    yys(1) = y(1);

    for j = n + t_test:-1:2
        ys(j) = yys(j) - yys(j - 1);
    end

    x = 1:n;
    xs = 2:n + t_test;
    yn = ys(2:n + t_test);
    % plot(x, y, '^r', xs, yn, '*-b');
    det = 0;

    for i = 2:n
        det = det + abs(yn(i) - y(i));
    end

    det = det / (n - 1);
    % disp(['百分绝对误差为：', num2str(det), '%']);
    % disp(['预测值为：', num2str(ys(n + 1:n + t_test))]);

    % 绘制保存
    x = 1:length(y) + 1;
    t(1:length(x) - 1) = y;
    t(length(x)) = ys(n + 1);

    fig = figure('Visible', 'off');
    plot(x(1:length(y)) + year_x, y, 'ro', 'MarkerSize', 7)
    hold on
    plot(xs + year_x, yn, 'b-^', 'MarkerSize', 7)
    hold on
    xlabel('年份'), ylabel('订单报数')
    title(['A', int2str(ai), '\_灰色预测模型'])
    saveas(fig, [fig_dict, 'A_predict_grey_A', int2str(ai), '.png'])

    predict_A(1, ai) = round(t(end));
    predict_A(2, ai) = det * 100;

    if ai == 2 || ai == 5
        predict_list(1, ai) = 0;
        predict_list(2:end, ai) = ys(1:n + 1)';
    else
        predict_list(:, ai) = ys(1:n + 1)';
    end

end

writematrix(predict_A, '../../Data/data_A_predict_grey.xlsx', 'Sheet', 1);
writematrix(predict_list, '../../Data/data_A_predict_grey_list.xlsx', 'Sheet', 1);
