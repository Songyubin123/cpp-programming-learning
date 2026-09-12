// 有效的字母异位词
// 给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。

// 示例 1: 输入: s = "anagram", t = "nagaram" 输出: true

// 示例 2: 输入: s = "rat", t = "car" 输出: false

// 说明: 你可以假设字符串只包含小写字母。

#include <iostream>
using namespace std;
#include <vector>
//两个数组的交集
#include <unordered_set>
// 给定两个数组 nums1 和 nums2 ，返回 它们的 交集 。输出结果中的每个元素一定是 唯一 的。我们可以 不考虑输出结果的顺序 。
// 例 1
// 输入：nums1 = [1,2,2,1], nums2 = [2,2]
// 输出：[2]
// 示例 2：
// 输入：nums1 = [4,9,5], nums2 = [9,4,9,8,4]
// 输出：[9,4]
// 解释：[4,9] 也是可通过的
class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.length() != t.length()) return false;
        int count[26] = {0};
        for(int i = 0; i < s.length(); i++){
            count[s[i] - 'a']++;
            count[t[i] - 'a']--;
        }
        for(int i = 0; i < 26; i++) {
            if(count[i] != 0) return false;
        }
        return true;
    }

    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> result_set;
        unordered_set<int> num_set(nums1.begin(), nums1.end());
        for(int num : nums2){
            if(num_set.find(num) != num_set.end()){
                result_set.insert(num);
            }
        }
        return vector<int>(result_set.begin(), result_set.end());  
    }
};

int main(){
    Solution s;
    string str1 = "anagram";
    string str2 = "nagara";
    cout << s.isAnagram(str1, str2) << endl;

    vector<int> nums1 = {1,2,2,1};
    vector<int> nums2 = {2,2};
    vector<int> res = s.intersection(nums1, nums2);
    for(int i = 0; i < res.size(); i++) {
        cout << res[i] << " ";
    }
    cout << endl;
    return 0;
}