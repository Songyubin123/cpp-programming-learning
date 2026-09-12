// 两数之和
// 力扣题目链接(opens new window)

// 给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。

// 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。

// 示例:

// 给定 nums = [2, 7, 11, 15], target = 9

// 因为 nums[0] + nums[1] = 2 + 7 = 9

// 所以返回 [0, 1]

// 四数相加
// 给定四个包含整数的数组列表 A , B , C , D ,计算有多少个元组 (i, j, k, l) ，使得 A[i] + B[j] + C[k] + D[l] = 0。

// 为了使问题简单化，所有的 A, B, C, D 具有相同的长度 N，且 0 ≤ N ≤ 500 。所有整数的范围在 -2^28 到 2^28 - 1 之间，最终结果不会超过 2^31 - 1 。

// 例如:

// 输入:

// A = [ 1, 2]
// B = [-2,-1]
// C = [-1, 2]
// D = [ 0, 2]
// 输出:

// 2

// 解释:

// 两个元组如下:

// (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
// (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0
#include <iostream>
using namespace std;
#include <vector>
#include <unordered_map>
#include <string>
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> num_map;
        for(int i = 0; i < nums.size(); i++){
            // target - nums[i];
            // if(num_map.find(complement) != num_map.end()){
            //     return {num_map[complement], i};
            // }
            // num_map[nums[i]] = i;
            auto iter = num_map.find(target - nums[i]);
            if(iter != num_map.end()){
                return {iter->second, i};
            }
            num_map.insert({nums[i], i});
        }
        return {};
    }

    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int, int> sum_map;
        for(int i = 0; i < nums1.size(); i++){
            for(int j = 0; j < nums2.size(); j++){
                sum_map[nums1[i] + nums2[j]]++;
            }
        }
        int count = 0;
        for(int i = 0; i < nums3.size(); i++){
            for(int j = 0; j < nums4.size(); j++){
                auto iter = sum_map.find(-nums3[i] - nums4[j]);
                if(iter != sum_map.end()){
                    count += iter->second;
                }
            }
        }
        return count;
    }

    //给定一个赎金信 (ransom) 字符串和一个杂志(magazine)字符串，判断第一个字符串 ransom 能不能由第二个字符串 magazines 里面的字符构成。如果可以构成，返回 true ；否则返回 false。

    // (题目说明：为了不暴露赎金信字迹，要从杂志上搜索各个需要的字母，组成单词来表达意思。杂志字符串中的每个字符只能在赎金信字符串中使用一次。)

    // 注意：

    // 你可以假设两个字符串均只含有小写字母。

    // canConstruct("a", "b") -> false
    // canConstruct("aa", "ab") -> false
    // canConstruct("aa", "aab") -> true
    // };
    bool canConstruct(string ransomNote, string magazine) {
        // unordered_map<char, int> char_map;
        // for(int i = 0; i < magazine.size(); i++){
        //     char_map[magazine[i]]++;
        // }
        // for(int i = 0; i < ransomNote.size(); i++){
        //     auto iter = char_map.find(ransomNote[i]);
        //     if(iter == char_map.end() || iter->second == 0){
        //         return false;
        //     }
        //     iter->second--;
        // }
        // return true;
        int nums[26] = {0};
        if(ransomNote.length() > magazine.length()){
            return false;
        }
        for(int i = 0; i < ransomNote.length(); i++){
            nums[ransomNote[i] - 'a']++; 
        }
        for(int i = 0; i < ransomNote.length(); i++){
            nums[ransomNote[i] - 'a']--;
        }
        for(int i = 0; i < 26; i++){
            if(nums[i] < 0) return false;
        }
        return true;
    }
};

int main(){
    Solution s;
    // vector<int> nums = {8, 8, 11, 15};
    // int target = 16;
    // vector<int> res = s.twoSum(nums, target);
    // for(int i = 0; i < res.size(); i++){
    //     cout << res[i] << " ";
    // }


    // vector<int> A = {1, 2};
    // vector<int> B = {-2, -1};
    // vector<int> C = {-1, 2};
    // vector<int> D = {0, 2};
    // cout << s.fourSumCount(A, B, C, D) << endl;

    string ranom = {'a', 'a'};

    string magazine = {'a', 'b', 'a'};
    cout << s.canConstruct(ranom, magazine) << endl;
}