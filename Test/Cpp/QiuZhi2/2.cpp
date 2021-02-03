#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 
     * @param a string字符串 待计算字符串
     * @return int整型
     */
    int solve(string a) {
        // write code here
        // 舍弃：从步长为2开始增加
        // int max = 0;
        // int step_len = 2;
        // for (int i=0; i<a.length()-step_len+1; i++) {
        //     for (int j=step_len; j<=a.length()-i; j+=2) {
        //         int begin_1 = i;
        //         int begin_2 = i+j/2;
        //         int t = 0;
        //         int x;
        //         for (x=0; x<j/2; x++) {
        //             if (a[begin_1+x] == a[begin_2+x]) {
        //                 t++;
        //             } else break;
        //         }
        //         if(x == j/2) {
        //             if (max < t*2) max = t*2;
        //             step_len = t+1;
        //         }
        //     }
        // }
        // return max;

        // 使用：从步长最大开始减少
        int max = 0;
        int step = a.length()%2?a.length()-1:a.length();
        int flag = 0;
        for (; step>1; step-=2) {
            for (int i=0; i+step<=a.length(); i++) {
                int begin_1 = i;
                int begin_2 = i+step/2;
                int x=0;
                while (a[begin_1+x] == a[begin_2+x]) {
                    x++;
                }
                if (x == step/2) {
                    max = step;
                    flag = 1;
                    break;
                }
            }
            if (flag) break;
        }
        return max;
    }
};

int main() {
    string a; a="q1qwertyuiopasdfghjklzxcvbnmq1qwertyuiopasdfghjklzxcvbnmabc";
    Solution s;
    cout << s.solve(a) << endl;
    return 0;
}