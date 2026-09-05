// 给你一个按 非递减顺序 排序的整数数组 nums，返回 每个数字的平方 组成的新数组，要求也按 非递减顺序 排序。

// 示例 1：

// 输入：nums = [-4,-1,0,3,10]
// 输出：[0,1,9,16,100]
// 解释：平方后，数组变为 [16,1,0,9,100]，排序后，数组变为 [0,1,9,16,100]
// 示例 2：

// 输入：nums = [-7,-3,2,3,11]
// 输出：[4,9,9,49,121]
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        // for(int i = 0; i < nums.size(); i++){
        //     nums[i] *= nums[i];
        // }
        // sort(nums.begin(), nums.end());
        vector<int> res(nums.size());
        int left = 0;
        int right = nums.size() - 1;
        int k = right;
        while(left <= right){
            if(abs(nums[left]) > abs(nums[right])){
                res[k--] = nums[left] * nums[left];
                left++;
            }
            else {
                res[k--] = nums[right] * nums[right];
                right--;
            }
        }
        return res;
    }
};

int main(){
    vector<int> nums = {-4,-1,0,3,10};
    Solution solution;
    vector<int> res = solution.sortedSquares(nums);
    for(int i = 0; i < res.size(); i++){
        cout << res[i] << " ";
    }
    return 0;
}