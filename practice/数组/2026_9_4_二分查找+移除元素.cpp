// 输入: nums = [-1,0,3,5,9,12], target = 9     
// 输出: 4       
// 解释: 9 出现在 nums 中并且下标为 4     
// 给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // 二分查找
    // int search(vector<int>& nums, int target) {
    //     int left = 0;
    //     int right = nums.size() - 1; // 定义target在左闭右闭的区间里，[left, right]
    //     while (left <= right) { // 当left==right，区间[left, right]依然有效，所以用 <=
    //         int middle = left + ((right - left) / 2);// 防止溢出 等同于(left + right)/2
    //         if (nums[middle] > target) {
    //             right = middle - 1; // target 在左区间，所以[left, middle - 1]
    //         } else if (nums[middle] < target) {
    //             left = middle + 1; // target 在右区间，所以[middle + 1, right]
    //         } else { // nums[middle] == target
    //             return middle; // 数组中找到目标值，直接返回下标
    //         }
    //     }
    //     // 未找到目标值
    //     return -1;
    // }

    //删除数组元素
    int deletetarget(vector<int>& nums, int target){
        int slow = 0;
        int fast = 0;
        int size = nums.size();
        for(int fast = 0; fast <size; fast++){
            if(nums[fast] != target){
                nums[slow] = nums[fast];
                slow++;
            }
            else{
            }
        }
        return slow;
    }
};

int main(){
    vector<int> nums = {-1, 0, 3, 5, 9, 12, 9};
    int target = 9;
    Solution solution;
    int res = solution.deletetarget(nums, target);
    cout << res << endl;
    return 0;
}