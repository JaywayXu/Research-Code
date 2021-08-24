clc, clear
file_name = '../../Data/data_C_predict.xlsx';
data_C = readmatrix(file_name);
data_C(isnan(data_C)) = 0;
data_C = data_C';
matrix_C = zeros(size(data_C, 1), 9);

col_now = 1;

for column = 1:3:size(data_C, 2)
    matrix_C(:, col_now) = data_C(:, column);
    col_now = col_now + 1;
end

% for row = size(matrix_C, 1):-1:2
%     matrix_C(row, :) = matrix_C(row, :) - matrix_C(row - 1, :);
% end

writematrix(matrix_C, '../../Data/data_C_predict_del.xlsx', 'Sheet', 1);
