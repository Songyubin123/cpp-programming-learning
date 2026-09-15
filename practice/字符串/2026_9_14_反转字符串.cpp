// 1.反转字符串
// 编写一个函数，其作用是将输入的字符串反转过来。输入字符串以字符数组 char[] 的形式给出。

// 不要给另外的数组分配额外的空间，你必须原地修改输入数组、使用 O(1) 的额外空间解决这一问题。

// 你可以假设数组中的所有字符都是 ASCII 码表中的可打印字符。

// 示例 1：
// 输入：["h","e","l","l","o"]
// 输出：["o","l","l","e","h"]

// 示例 2：
// 输入：["H","a","n","n","a","h"]
// 输出：["h","a","n","n","a","H"]



//2.反转字符串2
// 给定一个字符串 s 和一个整数 k，从字符串开头算起, 每计数至 2k 个字符，就反转这 2k 个字符中的前 k 个字符。

// 如果剩余字符少于 k 个，则将剩余字符全部反转。

// 如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。

// 示例:

// 输入: s = "abcdefg", k = 2
// 输出: "bacdfeg"


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0;
        int right = s.size() - 1;
        while(left < right){
            swap(s[left], s[right]);
            left++;
            right--;
        }
    }
    string reverseStr(string s, int k) {
        for(int i = 0; i < s.size(); i += 2 * k){
            int left = i;
            int right = k + i - 1;
            if(right >= s.size()){
                right = s.size() - 1;
            }
            while(left < right){
                swap(s[left], s[right]);
                left++;
                right--;
            }
        }

        return s;
    }
};

int main(){
    Solution s;
    // vector<char> str = {'H','a','n','n','a','h'};
    // s.reverseString(str);
    // for(int i = 0; i < str.size(); i++){
    //     cout << str[i] << " ";
    // }

    string str = "abcdefg";
    cout << s.reverseStr(str, 2) << endl;
    return 0;
}