#include <iostream>
#include <fstream>
int main()
{
    std::ifstream ifile;
    ifile.open(__FILE__);
    std::cout << ifile.rdbuf();
    std::cout << std::flush;
    ifile.close();
    return 0;
}