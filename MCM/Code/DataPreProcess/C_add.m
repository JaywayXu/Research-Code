clc, clear
file_name = '../../Data/data_C_all.xlsx';
data_C = readmatrix(file_name);
data_C(isnan(data_C)) = 0;

for column = 1:size(data_C, 2)
    sum_now = 0;

    for row = 1:size(data_C, 1)
        sum_now = sum_now + data_C(row, column);
        data_C(row, column) = sum_now;
    end

end

writematrix(data_C, '../../Data/data_C_all_add.xlsx', 'Sheet', 1);
