/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
#include <iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x): val(x),next(nullptr){}
};

class Solution {
public:

    ListNode* reverse(ListNode* pre, ListNode* cur) {
        if(cur == nullptr) return pre;
        ListNode* temp = cur->next;
        cur->next = pre;
        return reverse(cur, temp);
    }

    ListNode* reverseList(ListNode* head) {
        // ListNode* pre = nullptr;
        // ListNode* cur = head;
        // ListNode* temp ;
        // while( cur != nullptr ) {
        //     temp = cur->next;
        //     cur->next =pre;
        //     pre = cur;
        //     cur = temp;
        // }   
        // return pre;

        //递归
        return reverse(nullptr, head);
    }

    //删除倒数第n个节点
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* fast = dummy;
        ListNode* slow = dummy;
        for(int i = 0; i < n; i++){
            fast = fast->next;
        }
        while(fast->next != nullptr){
            fast = fast->next;
            slow = slow->next;
        }
        ListNode* remove  = slow->next;
        slow->next = remove->next;
        delete remove;
        remove = nullptr;
        return dummy->next;
    }
};

int main(){
    Solution s;
    ListNode* head = new ListNode(1);
    ListNode* second = new ListNode(2);
    ListNode* third = new ListNode(3);
    head->next = second;
    second->next = third;
    ListNode* fourth = new ListNode(4);
    third->next = fourth;
    ListNode* fifth = new ListNode(5);
    fourth->next = fifth;
    ListNode* newHead = s.reverseList(head);
    newHead = s.removeNthFromEnd(newHead, 5); // 删除倒数第3个节点
    cout << newHead->val << endl; // 输出 5
    cout << newHead->next->val << endl; // 输出 4
    cout << newHead->next->next->val << endl; // 输出 3
    cout << newHead->next->next->next->val << endl; // 输出 2
    cout << newHead->next->next->next->next->val << endl; // 输出 1
    
}