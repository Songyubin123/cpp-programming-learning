// 1. 滑动窗口最大值 
// 给定一个数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
// 返回滑动窗口中的最大值。

//2.前k个高频元素
//给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。

#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <queue>
using namespace std;
class Solution {
private:
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        deque<int> dq; 
        for(int i = 0; i < k; i++){
            while(!dq.empty() && nums[i] > dq.back()){
                dq.pop_back();
            }
            dq.push_back(nums[i]);
        }
        result.push_back(dq.front());
        for(int i = k; i < nums.size(); i++){
            if(nums[i - k] == dq.front()){
                dq.pop_front();
            }
            while(!dq.empty() && nums[i] > dq.back()){
                dq.pop_back();
            }
            dq.push_back(nums[i]);
            result.push_back(dq.front());
        }
        return result;
    }

    class mycomparison{
    public:
        bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs){
            return lhs.second > rhs.second;
        }
    };

    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> map;
        for(int i = 0; i < nums.size(); i++){
            map[nums[i]]++;
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparison> pri_que;
        for(auto iter = map.begin(); iter != map.end(); iter++){
            pri_que.push(*iter);
            if(pri_que.size() > k){
                pri_que.pop();
            }
        }
        //更简洁的写法
        // for(const auto& value : map){
        //     pri_que.push(value);
        //     if(pri_que.size() > k){
        //         pri_que.pop();
        //     }
        // }
        vector<int> result(k);
        for(int i = k - 1; i >= 0; i--){
            result[i] = pri_que.top().first;
            pri_que.pop();
        }
        return result;
    }
};

int main(){
    Solution s;
    vector<int> nums = {1,3,-1,-3,5,3,6,7};
    int k = 3;
    vector<int> result = s.maxSlidingWindow(nums, k);
    for(int i : result){
        cout << i << " ";
    }

    vector<int> nums2 = {1,1,1,2,2,3};
    int k2 = 2;
    vector<int> result2 = s.topKFrequent(nums2, k2);
    for(int i : result2){
        cout << i << " ";
    }
    return 0;
}