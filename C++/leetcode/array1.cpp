#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int x = -999999, count = 0;
        int len = nums.size();
        for (int i=0; i<len; i++) {
            if (x == nums[i]) {
                for (int j=i; j<len-1; j++) {
                    nums[j] = nums[j+1];
                }
                len--; i--;
            }
            else {
                x = nums[i];
                count++;
            }
        }
        return count;
    }
};

int main() {
    Solution so;
    vector<int> arr = {1,1};
    int l = so.removeDuplicates(arr);
    cout << l << endl;
    for (int i=0; i<l; i++) cout << arr[i];
    return 0;
}