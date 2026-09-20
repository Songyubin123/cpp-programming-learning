# `static` 与 `const` 关键字

## 一、核心区别

可以先记住：

- `const` 主要控制“能不能修改”。
- `static` 主要控制“生命周期、可见范围和归属关系”。

它们不是互相替代的关键字，也可以组合使用。

## 二、`const`：只读

```cpp
const int value = 10;
// value = 20; // 错误
```

`const` 变量必须初始化，初始化后不能再次赋值。它不一定是编译期常量；需要编译期常量时可以使用 `constexpr`。

### 1. `const` 成员变量

```cpp
class Student {
public:
    const int id;

    Student(int value) : id(value) {}
};
```

`const` 成员变量必须使用构造函数初始化列表初始化，每个对象都有自己的一份。

### 2. `const` 成员函数

```cpp
class Student {
public:
    int getAge() const {
        return age;
    }

private:
    int age = 18;
};
```

函数末尾的 `const` 表示该成员函数不会修改当前对象，可以被 `const` 对象调用。

## 三、`static`：改变生命周期、可见性或归属

### 1. 函数内部的 `static`

```cpp
void countCalls() {
    static int count = 0;
    ++count;
    cout << count << endl;
}
```

局部 `static` 变量只初始化一次，函数结束后仍然存在，下次调用时会保留原来的值。它的作用域仍然只在函数内部，生命周期则持续到程序结束。

### 2. 文件作用域的 `static`

```cpp
static int fileValue = 10;
```

定义在函数外的 `static` 变量只能在当前 `.cpp` 文件中访问，常用于隐藏文件内部的实现细节。

### 3. 类中的 `static` 数据成员

```cpp
class Student {
public:
    static int total;
};

int Student::total = 0;
```

静态成员属于类本身，而不是某个对象。所有 `Student` 对象共享同一份 `total`。C++17 以后可以使用 `inline static` 直接在类内定义：

```cpp
class Student {
public:
    inline static int total = 0;
};
```

### 4. `static` 成员函数

```cpp
class Student {
public:
    static int getTotal() {
        return total;
    }

    inline static int total = 0;
};
```

静态成员函数没有 `this` 指针，因此可以直接访问静态成员，但不能直接访问普通成员变量，也不能在函数末尾加 `const`。

## 四、`static const`

```cpp
static const int maxSize = 100;
```

这表示对象既不能修改，又具备 `static` 的特性。具体含义取决于所在位置：

- 函数内部：只初始化一次，并且只读；
- 文件作用域：当前文件可见，并且只读；
- 类中：所有对象共享，并且只读。

## 五、指针中的 `const`

```cpp
const int* p;        // 不能通过 p 修改所指向的值
int* const p = &a;   // p 本身不能指向别处，但可以修改 *p
const int* const p = &a; // 值和指针本身都不能修改
```

判断方法：看 `const` 修饰的是数据，还是指针本身。

## 六、对比表

| 关键字 | 主要作用 | 典型场景 |
|---|---|---|
| `const` | 限制修改 | 只读变量、`const` 成员函数、只读指针 |
| `static` | 控制生命周期、可见性或归属 | 局部静态变量、文件私有变量、类共享成员 |
| `static const` | 同时具备两者特点 | 共享的只读配置值 |

一句话总结：`const` 关注“修改权限”，`static` 关注“生命周期、作用范围和归属关系”。
