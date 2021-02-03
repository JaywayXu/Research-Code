#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 
     * @param a int整型vector<vector<>> 第一个矩阵
     * @param b int整型vector<vector<>> 第二个矩阵
     * @return int整型vector<vector<>>
     */
    vector<vector<int> > solve(vector<vector<int> >& a, vector<vector<int> >& b) {
        // write code here
        vector<vector<int>> resault;
        int n = a.size();
        for (int i=0; i<n; i++) { // 行
            vector<int> v; resault.push_back(v);
            for (int j=0; j<n; j++) { //列
                int sum = 0;
                for (int x=0; x<n; x++) {
                    sum += a[i][x] * b[x][j];
                }
                resault[i].push_back(sum);
            }
        }
        return resault;
    }
};

int main() {
    
    return 0;
}