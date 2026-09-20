// 1.有效的括号
// 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
// 有效字符串需满足：
// 左括号必须用相同类型的右括号闭合。
// 左括号必须以正确的顺序闭合。
// 注意空字符串可被认为是有效字符串。


//2. 删除字符串中的所有相邻重复项

// 给出由小写字母组成的字符串 s，重复项删除操作 会选择两个相邻且相同的字母，并删除它们。
// 在 s 上反复执行重复项删除操作，直到无法继续删除。
// 在完成所有重复项删除操作后返回最终的字符串。答案保证唯一。
// 输入："abbaca"
// 输出："ca"

//3. 逆波兰表达式求值
// 给你一个字符串数组 tokens ，表示一个根据 逆波兰表示法 表示的算术表达式。
// 请你计算该表达式。返回一个表示表达式值的整数
// 输入：tokens = ["4","13","5","/","+"]
// 输出：6
// 解释：该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6

#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (char c : s){
            if( c == '('){
                st.push(')');
            }
            else if( c == '{'){
                st.push('}');
            }
            else if( c == '['){
                st.push(']');
            }
            else{
                if(st.empty() || st.top() != c){
                    return false;
                }
                st.pop();
            }
        }
        return st.empty();
    }

        
    string removeDuplicates(string s) {
        stack<char> st;
        for(char c : s){
            if(!st.empty() && st.top() == c){
                st.pop();
            }
            else{
                st.push(c);
            }
        }
        string result;
        while(!st.empty()){
            result += st.top();
            st.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }

    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for(const string& token : tokens){
            if(token == "+" || token == "-" || token == "*" || token == "/"){
                int b = st.top(); st.pop();
                int a = st.top(); st.pop();
                if(token == "+") st.push(a + b);
                else if(token == "-") st.push(a - b);
                else if(token == "*") st.push(a * b);
                else if(token == "/") st.push(a / b);
            }
            else{
                st.push(stoi(token));
            }
        }
        return st.top();
    }
};

int main() {
    Solution solution;
    string s = "({[]}";
    bool result = solution.isValid(s);
    cout << "Is valid: " << (result ? "true" : "false") << endl;

    string s2 = "abbaca";
    string result2 = solution.removeDuplicates(s2);
    cout << "After removing duplicates: " << result2 << endl;

    vector<string> tokens = {"4", "13", "5", "/", "+"};
    int result3 = solution.evalRPN(tokens);
    cout << "Result of RPN evaluation: " << result3 << endl;
    return 0;


}