clc, clear
file_name = '../../Data/data_A_all.xlsx';
matrix_A = readmatrix(file_name, 'Sheet', 1);
file_name = '../../Data/data_A_all_print.xlsx';
matrix_A_print = readmatrix(file_name, 'Sheet', 1);

sale_rate_all = matrix_A ./ matrix_A_print;
sale_rate_all(isnan(sale_rate_all)) = 0;

sale_rate = zeros(1, 5);

for i = 1:5

    if i == 2 || i == 5
        sale_rate(i) = mean(sale_rate_all(2:end, i));
    else
        sale_rate(i) = mean(sale_rate_all(:, i));
    end

end

writematrix(sale_rate, '../../Data/data_A_sale_rate.xlsx', 'Sheet', 1);
