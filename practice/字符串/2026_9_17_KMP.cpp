#include <iostream>
using namespace std;
#include <vector>
//1. KMP 算法 strStr() 函数实现

class Solution {
public:
    void getNext(const string &s, vector<int> &next){
        int j = 0;
        for(int i = 1; i < s.size(); i++){
            while(j > 0 && s[i] != s[j]){
                j = next[j - 1]; 
                // next[j-1] 的值 k：
                // 1. 表示下标j-1及其之前的字符串可以保留的相同前后缀长度是 k
                // 2. 因为已经匹配了 k 个字符，所以下一个比较位置也是下标 k
            }
            if(s[i] == s[j]){
                j++;
            }
            next[i] = j;
        }
    }
    int strStr(string haystack, string needle) {
        vector<int> next(needle.size(), 0);
        getNext(needle, next);
        int j = 0;
        for(int i = 0; i < haystack.size(); i++){
            while(j > 0 && haystack[i] != needle[j]){
                j = next[j - 1]; // 回溯到前一个匹配位置 
            }
            if(haystack[i] == needle[j]){
                j++;
            }
            if(j == needle.size()){
                return i - j + 1;
            }
        }
        return -1;
    }
    bool repeatedSubstringPattern(string s) {

        // 方法1:
        // 如果字符串长度为0或1，则不能由子串重复构成
        if(s.size() <= 1) return false;
        // 将原字符串与自身拼接，然后在拼接后的字符串中查找原字符串
        // 如果能找到，则说明原字符串可以由子串重复构成
        string ss = s + s;
        ss = ss.substr(1, ss.size() - 2); // 去掉首尾字符
        return strStr(ss, s) != -1;

        // 方法2:
        int n = s.size();
        vector<int> next(n, 0);
        getNext(s, next);
        int len = next[n - 1];
        return len > 0 && n % (n - len) == 0;
    }
};
//2. 重复的子字符串
// 给定一个非空的字符串，判断它是否可以由它的一个子串重复多次构成。
// 示例 1:
// 输入: "abab"
// 输出: True
// 解释: 可由子字符串 "ab" 重复两次构成。
// 示例 2:
// 输入: "aba"
// 输出: False
// 示例 3:
// 输入: "abcabcabcabc"
// 输出: True
// 解释: 可由子字符串 "abc" 重复四次构成。 (或者子字符串 "abcabc" 重复两次构成。
// };

int main(){
    Solution s;
    // string str = "ABABABCA";
    // vector<int> next(str.size(), 0);
    // s.getNext(str, next);
    // cout << "Next array: ";
    // for(int i = 0; i < next.size(); i++){
    //     cout << next[i] << " ";
    // }
    // cout << endl;
    
    string haystack = "aabaabaafa";
    string needle = "aabaaf";
    int index = s.strStr(haystack, needle);
    cout << "Index: " << index << endl;

    string str1 = "abc";
    bool result = s.repeatedSubstringPattern(str1);
    cout << "Repeated substring pattern: " << result << endl;
}