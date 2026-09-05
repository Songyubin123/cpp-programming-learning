// 给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的 连续 子数组，并返回其长度。如果不存在符合条件的子数组，返回 0。

// 示例：

// 输入：s = 7, nums = [2,3,1,2,4,3]
// 输出：2
// 解释：子数组 [4,3] 是该条件下的长度最小的子数组。
// 提示：

// 1 <= target <= 10^9
// 1 <= nums.length <= 10^5
// 1 <= nums[i] <= 10^5

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        // int size = nums.size();
        // int res = INT32_MAX;
        // for(int i = 0; i <= size-1 ;  i++){
        //     int val = 0;
        //     for(int j = i; j<= size-1; j++){
        //         val += nums[j];
        //         if(val >= target){
        //             res = min(res, j-i+1);
        //             break;
        //         }
        //     }
        // }
        // return res;

        //双指针 滑动窗口
        int left = 0;
        int right = 0;
        int sum = 0;
        int res = INT32_MAX;
        while(right < nums.size()){
            sum += nums[right];
            while(sum >= target){
                res = min(res,right-left+1);
                sum -= nums[left];
                left++;
            }
            right++;
        }
        return res == INT32_MAX ? 0 : res;
    }
};

int main(){
    Solution solution;
    vector<int> nums = {2,3,1,2,4,3};
    int target = 7;
    int res = solution.minSubArrayLen(target,nums);
    cout << res << endl;
    return 0;
}