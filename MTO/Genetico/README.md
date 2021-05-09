# Genetic Algorithms

Please put cec14_func.cpp and input_data folder with your algorithm in the same folder. Set this folder as the current path.

1. run the following command in Matlab window:
   mex cec14_func.cpp -DWINDOWS
   
2. Then you can use the test functions as the following example:
   f = cec14_func(x,func_num); 
   here x is a D*pop_size matrix.
f= cec14_func([3.3253000e+000, -1.2835000e+000]', 1)

3. main.m is an example test code with PSO algorithm.

## Links
- [CEC 2014][1]
- [CFP-CEC 2014][2]

- [Original Files][3]


[1]:http://www.ntu.edu.sg/home/EPNSugan/index_files/CEC2014/CEC2014.htm
[2]:http://www.ntu.edu.sg/home/EPNSugan/index_files/CEC2014/CFP-CEC2014.htm
[3]:http://web.mysites.ntu.edu.sg/epnsugan/PublicSite/Shared%20Documents/Forms/AllItems.aspx?RootFolder=%2fepnsugan%2fPublicSite%2fShared%20Documents%2fCEC-2014&FolderCTID=&View=%7bDAF31868-97D8-4779-AE49-9CEC4DC3F310%7d

