% model_name = {'grey', 'interp'};
model_name = {'grey'};

for model = 1:length(model_name)
    file_name = ['../../Data/data_A_predict_', model_name{model}, '.xlsx'];
    predict_A = readmatrix(file_name, 'Sheet', 1);
    prop_A = readmatrix('../../Data/data_A_season_proportion.xlsx', 'Sheet', 1);

    for i = 1:5
        predict_season_A(:, i) = round(predict_A(1, i) * prop_A(:, i));
        predict_season_A(end, i) = predict_A(1, i) - sum(predict_season_A(1:end - 1, i));

        remain = 0;

        for j = 1:size(predict_season_A, 1)
            predict_season_A(j, i) = predict_season_A(j, i) - remain;
            remain = 0;

            if predict_season_A(j, i) >= 1500 && predict_season_A(j, i) < 2000
                remain = 2000 - predict_season_A(j, i);
                predict_season_A(j, i) = 2000;
            end

        end

    end

    writematrix(predict_season_A, ['../../Data/data_A_predict_season_', model_name{model}, '.xlsx'], 'Sheet', 1);
end
