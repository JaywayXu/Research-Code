clc, clear
file_name = '../../Data/data_A_season.xlsx';
% file_name = 'data_A_season.xlsx';
matrix_A = zeros(3, 5);

for i = 1:5
    as = readmatrix(file_name, 'Sheet', i);
    as(isnan(as)) = 0;
    sum3 = sum(as);
    sum3 = sum3(1:3);
    sum_all = sum(sum3);
    per3 = sum3 ./ sum_all;
    matrix_A(:, i) = per3';
end

writematrix(matrix_A, '../../Data/data_A_season_proportion.xlsx', 'Sheet', 1);
