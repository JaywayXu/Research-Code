clc, clear
file_name = '../../Data/data_C_predict_del.xlsx';
data_C = readmatrix(file_name);
data_C(isnan(data_C)) = 0;
matrix_C = data_C;

for row = size(matrix_C, 1):-1:2
    matrix_C(row, :) = round(matrix_C(row, :) - matrix_C(row - 1, :));
end

writematrix(matrix_C, '../../Data/data_C_predict_process.xlsx', 'Sheet', 1);
