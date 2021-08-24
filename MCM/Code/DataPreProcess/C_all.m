clc, clear
file_name = '../../Data/C_all.xlsx';
data_C = readmatrix(file_name);
data_C(isnan(data_C)) = 0;
row_num = [4, 4, 4, 3, 3, 3, 6, 6, 6];
year_num = [2018, 2018, 2018, 2019, 2019, 2019, 2016, 2016, 2016];
col_num = 12;

row_now = 1;
year_begin = 2016;
matrix_C = zeros(1, 12 * (2021 - 2016 + 1));

for i = 1:9

    c_i = [];

    for row_i = 1:row_num(i)
        c_i = [c_i data_C(row_now, :)];
        row_now = row_now +1;
    end

    matrix_C(i, ((year_num(i) - year_begin) * 12 +1):end) = c_i;

end

matrix_C = matrix_C';

writematrix(matrix_C, '../../Data/data_C_all.xlsx', 'Sheet', 1);
