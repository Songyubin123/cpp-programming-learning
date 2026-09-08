// 题意：

// 在链表类中实现这些功能：

// get(index)：获取链表中第 index 个节点的值。如果索引无效，则返回-1。
// addAtHead(val)：在链表的第一个元素之前添加一个值为 val 的节点。插入后，新节点将成为链表的第一个节点。
// addAtTail(val)：将值为 val 的节点追加到链表的最后一个元素。
// addAtIndex(index,val)：在链表中的第 index 个节点之前添加值为 val  的节点。如果 index 等于链表的长度，则该节点将附加到链表的末尾。如果 index 大于链表长度，则不会插入节点。如果index小于0，则在头部插入节点。
// deleteAtIndex(index)：如果索引 index 有效，则删除链表中的第 index 个节点。

#include <iostream>
using namespace std;

//可以定义链表的长度_size并且记录,方便判断
//成员变量用_开头表示私有成员变量
class MyLinkedList {
public:
    struct ListNode {
        int val;
        ListNode* next;
        ListNode(int x): val(x),next(nullptr){}
    };

    MyLinkedList() {
        _DummyNode = new ListNode(-1);
        _size = 0;
    }
    
    int get(int index) {
        if(index > (_size-1) || index < 0) return -1;
        ListNode* cur = _DummyNode;
        while(index--){
            cur = cur->next;
        }
        return cur->next->val;
    }
    
    void addAtHead(int val) {
        ListNode* NewNode = new ListNode(val);
        NewNode->next = _DummyNode->next;
        _DummyNode->next = NewNode;
        _size++;
    }
    
    void addAtTail(int val) {
        int index = _size;
        ListNode* cur = _DummyNode;
        ListNode* NewNode = new ListNode(val);
        while(index--){
            cur = cur->next;
        }
        cur->next = NewNode;
        _size++;
    }
    
    void addAtIndex(int index, int val) {
        ListNode* NewNode = new ListNode(val);
        if (index < 0) index = 0;
        if (index > _size) return;
        ListNode* cur = _DummyNode;
        while(index--){
            cur = cur->next;
        }
        NewNode->next = cur->next;
        cur->next = NewNode;
        _size++;
    }
    
    void deleteAtIndex(int index) {
        if (index >= _size || index < 0) return;
        ListNode* cur = _DummyNode;
        while(index--){
            cur = cur->next;
        }
        ListNode* RemovedNode = cur->next;
        cur->next = RemovedNode->next;
        delete RemovedNode;
        RemovedNode = nullptr;
        _size--;
    }

private:
    ListNode* _DummyNode;
    int _size;
};


// class MyLinkedList {

// public:
//     //定义链表节点结构体
//     struct ListNode {
//         int val;
//         ListNode *next;
//         ListNode(int x) : val(x), next(nullptr) {}
//     };

//     MyLinkedList() {
//         _dummyHead = new ListNode(-1); //虚拟头节点
//     }
    
//     int get(int index) {
//         ListNode* cur = _dummyHead->next;
//         int count = 0;
//         while(cur != nullptr){
//             if(count == index){
//                 return cur->val;
//             }
//             cur = cur->next;
//             count++;
//         }
//         return -1;
//     }
    
//     void addAtHead(int val) {
//         ListNode* newNode = new ListNode(val);
//         newNode->next = _dummyHead->next;
//         _dummyHead->next = newNode;
//     }
    
//     void addAtTail(int val) {
//         ListNode* newNode = new ListNode(val);
//         ListNode* cur = _dummyHead;
//         while(cur->next != nullptr){
//             cur = cur->next;
//         }
//         cur->next = newNode;
//     }
    
//     void addAtIndex(int index, int val) {
//         int count = 0;
//         ListNode* cur = _dummyHead;
//         if(index < 0){
//             index = 0;
//         }
//         while(cur != nullptr){
//             if(count != index){
//                 cur = cur->next;
//                 count++;
//             }
//             else{
//                 ListNode* newNode = new ListNode(val);
//                 newNode->next= cur->next;
//                 cur->next = newNode;
//                 return;
//             }
//         }
//     }
    
//     void deleteAtIndex(int index) {
//         int count = 0;
//         ListNode* cur = _dummyHead;
//         while(cur != nullptr){
//             if(count != index){
//                 cur = cur->next;
//                 count++;
//             }
//             else{
//                 if(cur->next == nullptr){
//                     return;
//                 }
//                 ListNode* temp = cur->next;
//                 cur->next = temp->next;
//                 delete temp;
//                 return;
//             }
//         }
//     }
// private:
//     ListNode* _dummyHead;
// };



int main(){
    MyLinkedList linkedList;
    linkedList.addAtHead(1);
    linkedList.addAtTail(3);
    linkedList.addAtIndex(1,2);   //链表变为1->2->3
    cout << linkedList.get(1) << endl;            //返回2
    linkedList.deleteAtIndex(1);  //现在链表是1->3
    cout << linkedList.get(1) << endl;            //返回3
    return 0;
}
/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */