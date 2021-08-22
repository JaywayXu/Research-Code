clc, clear
file_name = '../../Data/A_all_print.xlsx';
% file_name = 'A_all_print.xlsx';
data_A = readmatrix(file_name);
matrix_A = zeros(8, 5);

for column = 1:size(data_A, 2)
    i = 1;

    if column == 2 || column == 5
        i = 2;
    end

    for row = 1:3:size(data_A, 1)
        year = data_A(row, column);

        if ~isnan(year)
            matrix_A(i, column) = data_A(row + 1, column);
            i = i + 1;
        end

    end

end

writematrix(matrix_A, '../../Data/data_A_all_print.xlsx', 'Sheet', 1);
