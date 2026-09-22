# `volatile` 关键字与原子性

## 一、`volatile` 是什么

`volatile` 是一种类型限定符，用来告诉编译器：这个变量的值可能被当前代码之外的因素修改(硬件)，因此每次访问都需要真实执行去读内存，不能随意缓存、删除或合并访问。

```cpp
volatile bool flag = false;

while (!flag) {
    // 每次循环都重新读取 flag
}
```

普通变量如果在当前代码中没有被修改，编译器可能认为它的值不会变化；`volatile` 可以避免这种优化。

## 二、`volatile` 的常见使用场景

- 内存映射硬件寄存器：硬件可能随时改变寄存器的值。
- 中断处理函数修改的变量：主程序需要重新读取变量。
- 某些信号处理场景：信号处理函数可能修改变量。

```cpp
volatile unsigned int* status =
    reinterpret_cast<volatile unsigned int*>(0x40000000);

unsigned int value = *status;
```

## 三、`volatile` 不能解决的问题

`volatile` 只影响编译器优化，不保证：

- 操作的原子性；
- 多线程安全；
- 线程之间的同步和内存可见性；
- 多个操作之间的执行顺序。

下面的操作仍然可能出错：

```cpp
volatile int counter = 0;
counter++; // 读取、加一、写回，不是一个不可分割的操作
```

多线程场景应该使用 `std::atomic` 或互斥锁，而不是用 `volatile` 代替它们。

## 四、什么是原子性

原子性表示：

> 一个操作要么完整执行，要么完全没有执行，中间状态不会被其他线程看到，也不会被其他线程插入修改。

例如，`counter++` 实际上包含三个步骤：

```text
1. 读取 counter
2. 加 1
3. 写回 counter
```

两个线程同时执行时可能都读取到相同的旧值，导致更新丢失。

## 五、使用 `std::atomic` 保证原子操作

```cpp
#include <atomic>

std::atomic<int> counter = 0;

counter++;
// 或者：
counter.fetch_add(1);
```

`std::atomic` 适合多个线程共享的简单变量，可以保证读写和自增等操作的原子性，并提供线程同步相关的内存语义。

## 六、原子性与互斥锁

当多个变量需要作为一个整体修改时，通常使用互斥锁：

```cpp
#include <mutex>

std::mutex mtx;
int account_a = 1000;
int account_b = 0;

void transfer() {
    std::lock_guard<std::mutex> lock(mtx);
    account_a -= 100;
    account_b += 100;
}
```

`std::atomic` 适合简单的单变量原子操作；互斥锁适合保护一组需要一起完成的操作。

## 七、对比与记忆

| 内容 | `volatile` | `std::atomic` |
|---|---|---|
| 主要目的 | 防止编译器忽略真实访问 | 保证并发操作的原子性 |
| 保证原子性 | 不保证 | 保证相应的原子操作 |
| 适合硬件寄存器 | 适合 | 通常不用于替代 |
| 适合多线程共享变量 | 不适合单独使用 | 适合 |
| 能否替代互斥锁 | 不能 | 不能保护复杂的多变量操作 |

记忆方法：

> 面对硬件或外部变化，用 `volatile`；面对线程并发，用 `std::atomic`；需要保护多个相关操作，用互斥锁。
