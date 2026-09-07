#include <iostream>
using namespace std;
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
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {};
};
// head = [1,2,6,3,4,5,6], val = 6
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        //常规方法 需要判断头节点是否为val
        // while( head != nullptr && head->val == val){
        //     ListNode* temp = head;
        //     head = head->next;
        //     delete temp;
        // }
        // ListNode* cur = head;
        // while(cur != nullptr && cur->next != nullptr){
        //     if (cur->next->val == val){
        //         ListNode* temp = cur->next;
        //         cur->next = cur->next->next;
        //         delete temp;
        //     }
        //     else{
        //         cur = cur->next;
        //     }
        // }
        // return head;

        //虚拟头节点
        // ListNode* dummy = new ListNode(-1);
        // dummy->next = head;
        // ListNode* cur = dummy;
        // while(cur->next != nullptr){
        //     if (cur->next->val == val){
        //         ListNode* temp = cur->next;
        //         cur->next = temp->next;
        //         delete temp;
        //     }
        //     else{
        //         cur = cur->next;
        //     }
        // }
        // head = dummy->next;
        // delete dummy;
        // return head;

        //递归:每次只处理当前的一个节点，剩下的链表交给同一个函数处理。
        if(head == nullptr){
            return nullptr;
        }
        if(head->val == val){
            ListNode* newhead = removeElements(head->next, val);
            delete head;
            return newhead;
        }else{
            head->next = removeElements(head->next, val);
            return head;
        }
    }
};


int main(){
    // ListNode* head = new ListNode();
    // head->val = 1;

    // ListNode* second = new ListNode();
    // second->val = 2;
    // head->next = second;
    // cout << head->val << endl;
    // cout << second->val << endl;
    // cout << head->next->val << endl;
    ListNode* head = new ListNode(6);
    head->next = new ListNode(2);
    head->next->next = new ListNode(6);
    head->next->next->next = new ListNode(3);
    head->next->next->next->next = new ListNode(4);
    head->next->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next->next = new ListNode(6);
    Solution s;
    head = s.removeElements(head, 6);
    ListNode* current = head;
    while (current != nullptr) {
        cout << current->val << " ";
        current = current->next;
    }
    return 0;
}
