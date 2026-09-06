// 给定一个正整数 n，生成一个包含 1 到 n^2 所有元素，且元素按顺时针顺序螺旋排列的正方形矩阵。

// 示例:

// 输入: 3 输出: [ [ 1, 2, 3 ], [ 8, 9, 4 ], [ 7, 6, 5 ] ]

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        int val = 1;
        vector<vector<int>> res(n,vector<int>(n,0));
        int left = 0,top = 0;;
        int right = n - 1, bottom = n - 1;
        while(left < right && top < bottom){
            for(int col = left; col < right; col++){
                res[top][col] = val++;
            }
            for(int row = top; row < bottom; row++){
                res[row][right] = val++;
            }
            for(int col = right; col > left; col--){
                res[bottom][col] = val++;
            }
            for(int row = bottom; row > top; row--){
                res[row][left] = val++;
            }
            left++;
            bottom--;
            right--;
            top++;
        }
        //奇数阶的中心元素
        if(left == right && top == bottom){
            res[top][left] = val;
        }
        return res;
    }
};

int main(){
    Solution solution;
    int n = 4;
    vector<vector<int>> res = solution.generateMatrix(n);
    for(int i = 0; i < res.size(); i++){
        for(int j = 0; j < res[i].size(); j++){
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}