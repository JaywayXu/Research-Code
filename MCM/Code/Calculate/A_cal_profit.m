% model_name = {'grey', 'interp'};
model_name = {'grey'};

for model = 1:length(model_name)
    profit_A = zeros(1, 5);
    file_name = ['../../Data/data_A_predict_season_', model_name{model}, '.xlsx'];
    N_A = readmatrix(file_name, 'Sheet', 1); % 3*5
    N_A = sum(N_A);
    file_name = ['../../Data/data_A_cost_season_', model_name{model}, '.xlsx'];
    cost_A = readmatrix(file_name, 'Sheet', 1); % 3*5
    file_name = '../../Data/A_price.xlsx';
    price_A = readmatrix(file_name, 'Sheet', 1); % 1*5
    discount = 0.48;
    file_name = '../../Data/data_A_sale_rate.xlsx';
    sale_rate = readmatrix(file_name, 'Sheet', 1); %1*5
    shipe_rate = 0.0273;

    for i = 1:5
        shipe_cost = N_A(i) * price_A(i) * shipe_rate;
        profit_A(i) = price_A(i) * N_A(i) * (1 - discount) * sale_rate(i) - (sum(cost_A(:, i)) + shipe_cost);
    end

    writematrix(profit_A, ['../../Data/data_A_profit_', model_name{model}, '.xlsx'], 'Sheet', 1);
end
