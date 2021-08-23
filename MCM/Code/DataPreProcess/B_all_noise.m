clc, clear
file_name = '../../Data/B_all.xlsx';
data_B = readmatrix(file_name, 'Sheet', 1);
data_B(isnan(data_B)) = 0;
% matrix_B = zeros(8, 5);

end_month = [9, 4];

for column = 2:size(data_B, 2)

    if column <= 6 % B1
        flag = 1;
    else
        flag = 2;
    end

    for row = 1:4 * 12 + 3
        month_now = mod(row - 1, 12) + 1;

        if month_now == end_month(flag)
            row_i = row;
            sum = 0;

            for i = 0:5
                sum = sum + data_B(row_i + i, column);
                data_B(row_i + i, column) = 0;
            end

            data_B(row_i, column) = sum;

        end

    end

end

writematrix(data_B, '../../Data/data_B_all.xlsx', 'Sheet', 1);
