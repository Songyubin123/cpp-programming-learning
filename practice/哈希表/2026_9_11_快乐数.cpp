// 编写一个算法来判断一个数 n 是不是快乐数。

// 「快乐数」 定义为：

// 对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
// 然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。
// 如果这个过程 结果为 1，那么这个数就是快乐数。
// 如果 n 是 快乐数 就返回 true ；不是，则返回 false 。

 

// 示例 1：

// 输入：n = 19
// 输出：true
// 解释：
// 输入：19
// 输出：true
// 解释：
// 1^2 + 9^2 = 82
// 8^2 + 2^2 = 68
// 6^2 + 8^2 = 100
// 1^2 + 0^2 + 0^2 = 1


#include <iostream>
using namespace std;
#include <unordered_set>
//当我们遇到了要快速判断一个元素是否出现集合里的时候，就要考虑哈希法了!!!
class Solution {
public:

    int sum(int n){
        int total = 0;
        while(n > 0){
            total += (n % 10) * (n % 10);
            n = n / 10;
        }
        return total;
    }
    bool isHappy(int n) {
        unordered_set<int> res_set;
        while(1){
            n = sum(n);
            if(n == 1) return true;
            if(res_set.find(n) != res_set.end()) return false;
            res_set.insert(n);
        }
    }
};

int main(){
    Solution s;
    int n = 19;
    cout << s.isHappy(n) << endl;
}