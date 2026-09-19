// 1.用栈实现队列
// 请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：
// 实现 MyQueue 类：
// void push(int x) 将元素 x 推到队列的末尾
// int pop() 从队列的开头移除并返回元素
// int peek() 返回队列开头的元素
// boolean empty() 如果队列为空，返回 true ；否则，返回 false
// 说明：
// 你 只能 使用标准的栈操作 —— 也就是只有 push to top, peek/pop from top, size, 和 is empty 操作是合法的。
// 你所使用的语言也许不支持栈。你可以使用 list 或者 deque（双端队列）来模拟一个栈，只要是标准的栈操作即可。

// 2. 用队列实现栈
// 使用队列实现栈的下列操作：

// push(x) -- 元素 x 入栈
// pop() -- 移除栈顶元素
// top() -- 获取栈顶元素
// empty() -- 返回栈是否为空

#include <stack>
#include <iostream>
#include <queue>
using namespace std;

class MyQueue {
public:
    stack<int> inputStack;  // 输入栈
    stack<int> outputStack; // 输出栈
    MyQueue() {

    }
    
    void push(int x) {
        inputStack.push(x);
    }
    
    int pop() {
        if(outputStack.empty()){
            while(!inputStack.empty()){
                outputStack.push(inputStack.top());
                inputStack.pop();
            }
        }
        int topElement = outputStack.top();
        outputStack.pop();
        return topElement;
    }
    
    int peek() {
        if(outputStack.empty()){
            while(!inputStack.empty()){
                outputStack.push(inputStack.top());
                inputStack.pop();
            }
        }
        return outputStack.top();
    }
    
    bool empty() {
        return inputStack.empty() && outputStack.empty();
    }
};
class MyStack {
public:
    queue<int> q1;
    queue<int> q2;
    MyStack() {
        
    }
    
    void push(int x) {
        q1.push(x);
    }
    
    int pop() {
        while(q1.size() > 1){
            q2.push(q1.front());
            q1.pop();
        }
        int topElement = q1.front();
        q1.pop();
        swap(q1, q2);
        return topElement;
    }
    
    int top() {
        int topElement = this -> pop();
        q1.push(topElement);
        return topElement;
    }
    
    bool empty() {
        return q1.empty() && q2.empty();
    }
};
class MyStack {
public:
    queue<int> que;

    MyStack() {

    }

    void push(int x) {
        que.push(x);
    }

    int pop() {
        int size = que.size();
        size--;
        while (size--) { // 将队列头部的元素（除了最后一个元素外） 重新添加到队列尾部
            que.push(que.front());
            que.pop();
        }
        int result = que.front(); // 此时弹出的元素顺序就是栈的顺序了
        que.pop();
        return result;
    }

    int top(){
        int size = que.size();
        size--;
        while (size--){
            // 将队列头部的元素（除了最后一个元素外） 重新添加到队列尾部
            que.push(que.front());
            que.pop();
        }
        int result = que.front(); // 此时获得的元素就是栈顶的元素了
        que.push(que.front());    // 将获取完的元素也重新添加到队列尾部，保证数据结构没有变化
        que.pop();
        return result;
    }

    bool empty() {
        return que.empty();
    }
};

int main(){
    MyQueue myQueue;
    myQueue.push(1);
    myQueue.push(2);
    cout << myQueue.peek() << endl; // 返回 1
    myQueue.pop(); // 返回 1
    cout << myQueue.empty() << endl; // 返回 false
    myQueue.pop(); // 返回 2
    cout << myQueue.empty() << endl; // 返回 true

    MyStack myStack;
    myStack.push(1);
    myStack.push(2);
    cout << myStack.top() << endl; // 返回 2
    cout << myStack.pop() << endl; // 返回 2
    cout << myStack.empty() << endl; // 返回 false
    cout << myStack.top() << endl; // 返回 1
    return 0;
}