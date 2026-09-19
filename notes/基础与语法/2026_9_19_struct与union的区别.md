# struct 与 union 的区别

## 一、核心区别

`struct` 和 `union` 都可以把多个不同类型的数据组合在一起，但内存使用方式不同：

> `struct` 的所有成员同时存在；`union` 的所有成员共享同一块内存，同一时刻通常只能使用其中一个成员。

| 对比项 | `struct` 结构体 | `union` 联合体 |
|---|---|---|
| 内存分配 | 每个成员都有独立空间 | 所有成员共享同一空间 |
| 能否同时保存成员值 | 可以 | 通常只能有一个成员有效 |
| 占用空间 | 成员大小之和，再加对齐填充 | 最大成员大小，再加对齐填充 |
| 修改一个成员 | 通常不影响其他成员 | 可能覆盖其他成员 |
| 常见用途 | 表示一个完整对象 | 节省内存、表示多种可能类型 |

---

## 二、struct 的特点

```cpp
struct Student {
    int age;
    double score;
    char level;
};

Student student;
student.age = 20;
student.score = 95.5;
student.level = 'A';
```

结构体中的每个成员都有自己的存储空间，因此三个值可以同时存在：

```text
+---------+---------+---------+
| age     | score   | level   |
+---------+---------+---------+
```

结构体大小通常满足：

```text
sizeof(struct) >= 所有成员大小之和
```

实际大小可能大于成员大小之和，因为编译器会进行内存对齐和填充。例如，`char`、`int`、`double` 的排列顺序不同，结构体最终大小也可能不同。

结构体适合表达“同时拥有多个属性”的对象：

```cpp
struct Point {
    double x;
    double y;
};

struct Date {
    int year;
    int month;
    int day;
};
```

---

## 三、union 的特点

```cpp
union Data {
    int i;
    float f;
    char bytes[4];
};
```

联合体的成员共用同一块内存：

```text
+----------------+
|   i / f / bytes |
+----------------+
```

例如：

```cpp
Data data;

data.i = 100;       // 当前把内存当作 int 使用
data.f = 3.14f;     // 改为当作 float 使用，覆盖原来的内容
```

联合体的大小通常近似等于最大成员的大小，但仍会受到对齐要求影响：

```text
sizeof(union) >= 最大成员的大小
```

联合体适合表达“多个类型中只能选择一种”的对象，例如一个数据可能是整数，也可能是浮点数，但不是同时保存两个独立值。

---

## 四、内存布局对比

### struct

```cpp
struct S {
    int a;
    int b;
};
```

内存大致如下：

```text
+-------+-------+
|   a   |   b   |
+-------+-------+
```

`a` 和 `b` 的地址通常不同，两个值可以同时保存。

### union

```cpp
union U {
    int a;
    float b;
};
```

内存大致如下：

```text
+-------+
| a / b |
+-------+
```

`a` 和 `b` 通常位于同一地址。给一个成员赋值后，另一个成员看到的是同一块内存按另一种类型解释后的结果。

---

## 五、union 通常需要配合类型标记

单独使用 `union` 时，程序可能不知道当前哪个成员有效。可以使用枚举记录当前类型：

```cpp
enum class ValueType {
    Integer,
    Floating
};

struct Value {
    ValueType type;

    union {
        int integer;
        double floating;
    };
};
```

使用时：

```cpp
Value value;

value.type = ValueType::Integer;
value.integer = 42;

if (value.type == ValueType::Integer) {
    std::cout << value.integer;
} else {
    std::cout << value.floating;
}
```

这种“类型标记 + 联合体”的形式称为 Tagged Union（带标签的联合体）。

---

## 六、不要随意读取非当前成员

下面的代码存在可移植性和未定义行为风险：

```cpp
union Number {
    int i;
    float f;
};

Number number;
number.i = 10;
std::cout << number.f;  // 不应依赖这种读取结果
```

原因是：

- 联合体成员共享同一块内存；
- 写入一个成员后，另一个成员的内容可能已被覆盖；
- 在 C++ 中，读取当前未激活的成员通常属于未定义行为；
- 结果还可能受到平台字节序、数据类型表示和编译器规则影响。

不要把 `union` 当作通用类型转换工具。若要查看对象的二进制表示，C++20 推荐使用 `std::bit_cast`：

```cpp
#include <bit>
#include <cstdint>

float value = 1.0f;
std::uint32_t bits = std::bit_cast<std::uint32_t>(value);
```

---

## 七、C++ 中的 struct 与 class

C++ 中，`struct` 和 `class` 的功能基本相同，都可以包含：

- 成员变量
- 成员函数
- 构造函数和析构函数
- 静态成员
- 模板
- 继承关系

主要区别是默认访问权限：

```cpp
struct A {
    int x;  // 默认 public
};

class B {
    int x;  // 默认 private
};
```

默认继承权限也不同：`struct` 默认 public 继承，`class` 默认 private 继承。

这与 `struct` 和 `union` 的根本区别不同；后者的根本区别是内存布局和成员是否共享存储空间。

---

## 八、复杂类型与现代 C++ 写法

如果 `union` 包含 `std::string` 等有构造、析构过程的复杂类型，就需要手动管理对象生命周期，容易出错。

现代 C++ 中更推荐使用 `std::variant`：

```cpp
#include <variant>
#include <string>

std::variant<int, double, std::string> value;

value = 42;
value = 3.14;
value = "hello";
```

`std::variant` 会记录当前存储的类型，使用时也可以进行安全访问，比手写联合体更可靠。

---

## 九、实际选择建议

### 使用 struct 的情况

当对象需要同时保存所有成员时使用：

```cpp
struct Person {
    char name[32];
    int age;
    double height;
};
```

它表达的是：

```text
Person 有 name，并且有 age，并且有 height
```

### 使用 union 的情况

当对象在多个类型中只需要选择一种，并且确实需要共享内存时使用：

```cpp
union Number {
    int integer;
    double floating;
};
```

它表达的是：

```text
Number 是 integer 或 floating
```

常见场景包括：

- 嵌入式系统和硬件寄存器映射
- 网络协议数据
- 内存非常紧张的场景
- C 风格的带标签数据结构

如果只是想在现代 C++ 中安全地保存多种类型，优先考虑 `std::variant`。

---

## 十、速记总结

```text
struct：所有成员各占一份空间，可以同时有效
union ：所有成员共用一份空间，通常只有一个成员有效
```

也可以记成：

```text
struct = 并且（AND）
union  = 或者（OR）
```

| 需求 | 推荐工具 |
|---|---|
| 一个对象同时拥有多个属性 | `struct` |
| 多种类型共用一块内存 | `union` |
| 安全地保存多种可能类型 | `std::variant` |
| 仅进行二进制位级转换 | `std::bit_cast` |

