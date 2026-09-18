# C++ 中 `struct` 与 `class` 的区别

## 一、核心结论

在 C++ 中，`struct` 和 `class` 本质上都是定义自定义类型的工具，二者都支持：

- 成员变量和成员函数
- 构造函数与析构函数
- 继承、多态和虚函数
- 模板、静态成员、友元和运算符重载
- `public`、`private`、`protected` 权限控制

它们最主要的区别只有两个默认规则：

1. `struct` 的成员默认是 `public`，`class` 的成员默认是 `private`。
2. `struct` 的继承默认是 `public`，`class` 的继承默认是 `private`。

除此之外，它们没有本质的性能差异。

---

## 二、成员默认访问权限

### `struct` 默认是 `public`

```cpp
struct Student {
    std::string name;
    int age;
};
```

上面的定义等价于：

```cpp
struct Student {
public:
    std::string name;
    int age;
};
```

因此可以直接访问成员：

```cpp
Student student;
student.name = "Tom";
student.age = 18;
```

### `class` 默认是 `private`

```cpp
class Student {
    std::string name;
    int age;
};
```

上面的定义等价于：

```cpp
class Student {
private:
    std::string name;
    int age;
};
```

外部不能直接访问：

```cpp
Student student;
// student.name = "Tom";  // 编译错误
```

如果希望公开访问，必须显式写出 `public`：

```cpp
class Student {
public:
    std::string name;
    int age;
};
```

注意：访问权限只影响从当前位置开始、直到下一个权限标签之前的成员。

```cpp
class Example {
    int a;       // private

public:
    int b;       // public

private:
    int c;       // private
};
```

---

## 三、继承时的默认权限

### `struct` 默认是 `public` 继承

```cpp
struct Base {
    int value;
};

struct Derived : Base {
};
```

等价于：

```cpp
struct Derived : public Base {
};
```

### `class` 默认是 `private` 继承

```cpp
class Base {
public:
    int value;
};

class Derived : Base {
};
```

等价于：

```cpp
class Derived : private Base {
};
```

这意味着外部代码不能直接通过 `Derived` 访问继承来的 `public` 成员，也不能自动把 `Derived*` 转换成 `Base*`。

如果使用 `class` 进行常见的公开继承，应明确写出：

```cpp
class Derived : public Base {
};
```

---

## 四、二者都不只是“存数据”

`struct` 也可以拥有私有成员、构造函数和成员函数：

```cpp
struct BankAccount {
private:
    double balance = 0;

public:
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    double getBalance() const {
        return balance;
    }
};
```

`class` 也可以拥有公开数据：

```cpp
class Point {
public:
    int x;
    int y;
};
```

所以不能简单理解为：

- `struct` 只能存数据
- `class` 只能写功能

这种说法是不准确的。

---

## 五、实际开发中的选择

### 通常使用 `struct` 的情况

适合表示简单的数据集合：

```cpp
struct Point {
    int x;
    int y;
};

struct Color {
    int red;
    int green;
    int blue;
};
```

常见特点：

- 数据主要公开
- 外部可以直接读写成员
- 内部没有复杂约束
- 更像一个“数据记录”

### 通常使用 `class` 的情况

适合表示需要封装的对象：

```cpp
class Person {
private:
    int age = 0;

public:
    void setAge(int value) {
        if (value >= 0 && value <= 150) {
            age = value;
        }
    }

    int getAge() const {
        return age;
    }
};
```

使用 `class` 可以防止外部直接制造非法状态，例如不能随意把年龄改成负数。

---

## 六、常见误解

### 1. `struct` 不能写成员函数

错误。`struct` 完全可以写成员函数、构造函数和析构函数。

```cpp
struct Rectangle {
    int width;
    int height;

    int area() const {
        return width * height;
    }
};
```

### 2. `class` 不能有公开变量

错误。只要写出 `public:`，`class` 就可以拥有公开成员。

### 3. `struct` 性能更好

错误。编译器不会因为使用 `struct` 而生成更快的代码。性能主要取决于数据布局、算法、编译器优化等因素。

### 4. `struct` 一定可以使用大括号初始化

不完全准确。是否可以使用聚合初始化取决于类型的具体定义，例如是否有构造函数、私有成员或虚函数等。`class` 在满足条件时也可以使用大括号初始化。

---

## 七、对比表

| 对比项 | `struct` | `class` |
|---|---|---|
| 成员默认访问权限 | `public` | `private` |
| 默认继承权限 | `public` | `private` |
| 是否支持成员函数 | 支持 | 支持 |
| 是否支持构造函数 | 支持 | 支持 |
| 是否支持继承和多态 | 支持 | 支持 |
| 性能 | 没有本质区别 | 没有本质区别 |
| 常见用途 | 简单数据结构 | 需要封装的对象 |

## 八、记忆方法

> `struct` 默认公开，`class` 默认私有。

实际选择时可以遵循这个风格：

```cpp
struct Point {
    int x;
    int y;
};
```

表示简单数据。

```cpp
class Account {
private:
    double balance;

public:
    void deposit(double money);
};
```

表示需要封装和维护规则的对象。

