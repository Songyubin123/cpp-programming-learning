
#include <iostream>
using namespace std;
//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int lenA = 0, lenB = 0;
        ListNode* curA = headA;
        ListNode* curB = headB;
        while(curA != nullptr){
            lenA++;
            curA = curA->next;
        }
        while(curB != nullptr){
            lenB++;
            curB = curB->next;
        }
        curA = headA;
        curB = headB;
        int diff = lenA - lenB;
        if(diff > 0){
            while(diff--){
                curA = curA->next;
            }
        }
        else{
            diff = abs(diff);
            while(diff--){
                curB = curB->next;
            }
        }
        while(curA != nullptr && curB != nullptr){
            if(curA == curB){
                return curA;
            }
            else{
                curA = curA->next;
                curB = curB->next;
            }
        }
        return nullptr;
    }
    ListNode* detectCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast != nullptr && fast->next != nullptr){
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast){
                ListNode* cur = head;
                while(cur != slow){
                    cur = cur->next;
                    slow = slow->next;
                }
                return cur;
            }
        }
        return nullptr;
    }
};

int main(){
    Solution s;
    // ListNode* headA = new ListNode(4);
    // ListNode* headB = new ListNode(5);
    // ListNode* nodeA1 = new ListNode(1);
    // ListNode* nodeB1 = new ListNode(0);
    // ListNode* nodeB2 = new ListNode(1);
    // ListNode* nodeC1 = new ListNode(8);
    // ListNode* nodeC2 = new ListNode(4);
    // ListNode* nodeC3 = new ListNode(5);
    // headA->next = nodeA1;
    // headB->next = nodeB1;
    // nodeB1->next = nodeB2;
    // nodeB2->next = nodeC1;
    // nodeA1->next = nodeC1;
    // nodeC1->next = nodeC2;
    // nodeC2->next = nodeC3;
    // ListNode* intersection = s.getIntersectionNode(headA, headB);
    // cout << intersection << "value:" << intersection->val << endl;
    ListNode* head = new ListNode(1);
    ListNode* node1 = new ListNode(2);
    ListNode* node2 = new ListNode(3);
    ListNode* node3 = new ListNode(4);
    ListNode* node4 = new ListNode(5);
    ListNode* node5 = new ListNode(6);
    ListNode* node6 = new ListNode(7);
    ListNode* node7 = new ListNode(8);
    head->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = node6;
    node6->next = node7;
    node7->next = node3; // Create a cycle here
    ListNode* cycleNode = s.detectCycle(head);
    cout << cycleNode << "value:" << cycleNode->val << endl;
    return 0;
}