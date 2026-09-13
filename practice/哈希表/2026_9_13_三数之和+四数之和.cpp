
//三数之和
// 给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有满足条件且不重复的三元组。

// 注意： 答案中不可以包含重复的三元组。

// 示例：

// 给定数组 nums = [-1, 0, 1, 2, -1, -4]，

// 满足要求的三元组集合为： [ [-1, 0, 1], [-1, -1, 2] ]

#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector< vector<int>> res;
        sort(nums.begin(), nums.end());
        for(int a = 0; a < nums.size() ; a++){
            int b = a + 1;
            int c = nums.size() - 1;
            if(a > 0 && nums[a] == nums[a - 1]) continue;
            while(c > b){
                if(nums[a] + nums[b] + nums[c] > 0){
                    c--;
                }
                else if(nums[a] + nums[b] + nums[c] < 0){
                    b++;
                }
                else{
                    res.push_back({nums[a], nums[b], nums[c]});
                    c--;
                    b++;
                    while(b < c && nums[b] == nums[b - 1]) b++;
                    while(b < c && nums[c] == nums[c + 1]) c--;
                }
            }

        }
        return res;
    }

    //四数之和
    // 题意：给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。
    // 注意：
    // 答案中不可以包含重复的四元组。
    // 示例： 给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。 满足要求的四元组集合为： [ [-1, 0, 0, 1], [-2, -1, 1, 2], [-2, 0, 0, 2] ]
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        for(int a = 0; a < nums.size(); a++){
            if(a > 0 && nums[a] == nums[a - 1]) continue;
            for(int b = a + 1; b < nums.size(); b++){
                if(b > a + 1 && nums[b] == nums[b - 1]) continue;
                int c = b + 1;
                int d = nums.size() - 1;
                while(c < d){
                    if(nums[a] + nums[b] + nums[c] + nums[d] > target){
                        d--;
                    }
                    else if(nums[a] + nums[b] + nums[c] + nums[d] < target){
                        c++;
                    }
                    else{
                        res.push_back({nums[a],nums[b],nums[c],nums[d]});
                        c++;
                        d--;
                        while(c < d && nums[c] == nums[c - 1]) c++;
                        while(c< d && nums[d] == nums[d + 1]) d--;
                    }
                }
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    // vector<int> nums = {-1, 0, 1, 2, -1, -4};
    // vector<vector<int>> result = s.threeSum(nums);
    // for(int i = 0; i < result.size(); i++){
    //     for(int j = 0; j < result[i].size(); j++){
    //         cout << result[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    vector <int> nums = {1, 0, -1, 0, -2, 2};
    int target = 0;
    vector<vector<int>> result = s.fourSum(nums, target);
    for(int i = 0; i < result.size(); i++){
        for(int j = 0; j < result[i].size(); j++){
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
}