#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL){}
};

class Solution {
public:
    //1. 递归法
    // void traversal(TreeNode* root, vector<int>& res){
    //     if(root == NULL) return;
    //     traversal(root->left, res);
    //     res.push_back(root->val);
    //     traversal(root->right, res);
    // }
    // vector<int> inorderTraversal(TreeNode* root) {
    //     vector<int> res;
    //     traversal(root, res);
    //     return res;
    // }

    //2. 迭代法
    // vector<int> preorderTraversal(TreeNode* root){
    //     stack<TreeNode*> st;
    //     vector<int> res;
    //     if(root == NULL) return res;
    //     st.push(root);
    //     while(!st.empty()){
    //         TreeNode* node = st.top();
    //         st.pop();
    //         res.push_back(node->val);
    //         if(node->right) st.push(node->right);
    //         if(node->left) st.push(node->left);
    //     }
    //     return res;
    // }

    // vector<int> inorderTraversal(TreeNode* root){
    //     stack<TreeNode*> st;
    //     vector<int> res;
    //     TreeNode* node = root;
    //     while(node != NULL || !st.empty()){
    //         if(node != NULL){
    //             st.push(node);
    //             node = node->left;
    //         }
    //         else{
    //             node = st.top();
    //             st.pop();
    //             res.push_back(node->val);
    //             node = node->right;
    //         }
    //     }
    //     return res;
    // }

    // vector<int> postorderTraversal(TreeNode* root){
    //     stack<TreeNode*> st;
    //     vector<int> res;
    //     if(root == NULL) return res;
    //     st.push(root);
    //     while(!st.empty()){
    //         TreeNode* node = st.top();
    //         st.pop();
    //         res.push_back(node->val);
    //         if(node->left) st.push(node->left);
    //         if(node->right) st.push(node->right);
    //     }
    //     reverse(res.begin(), res.end());
    //     return res;
    // }
    //迭代统一法 （空指针标记法）
    // vector<int> inorderTraversal(TreeNode* root){
    //     vector<int> result;
    //     stack<TreeNode*> st;
    //     if(root != NULL) st.push(root);
    //     while(!st.empty()){
    //         TreeNode* node = st.top();
    //         if(node != NULL){
    //             st.pop();
    //             if(node->right) st.push(node->right);
    //             st.push(node);
    //             st.push(NULL);
    //             if(node->left) st.push(node->left);

    //         }
    //         else{
    //             st.pop();
    //             node = st.top(); 
    //             st.pop();
    //             result.push_back(node->val);           
    //         }
    //     }
    //     return result;
    // }

    //迭代统一法 boolean 标记法
    vector<int> inorderTraversal(TreeNode* root){
        vector<int> result;
        stack<pair<TreeNode*, bool>> st;
        if(root != nullptr) st.push(make_pair(root, false));

        while(!st.empty()){
            auto node = st.top().first;
            auto visited = st.top().second;
            st.pop();
            if(visited){
                result.push_back(node->val);
                continue;
            
            
            if(node->right) st.push(make_pair(node->right, false));

            st.push(make_pair(node, true));
            
            if(node->left) st.push(make_pair(node->left, false));
            }
        return result;
        }
    }
};

int main(){
    Solution s;
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);
    vector<int> res = s.inorderTraversal(root);
    for(int i = 0; i < res.size(); i++){
        cout << res[i] << " ";
    }
    return 0;
}