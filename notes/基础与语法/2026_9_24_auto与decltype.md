# C++11 中的 `auto` 与 `decltype`

## 一、核心区别

- `auto` 根据变量的初始化表达式推导变量类型，常按值推导，因此通常忽略顶层 `const` 和引用。
- `decltype(expr)` 查询表达式的类型，适合需要准确保留类型信息的声明和泛型代码。

```cpp
int x = 10;
const int cx = 20;
int& ref = x;

auto a = cx;         // int：顶层 const 被忽略
auto b = ref;        // int：引用被忽略
decltype(cx) c = 1;  // const int
decltype(ref) d = x; // int&
```

## 二、`auto` 推导

`auto` 必须有初始化表达式。推导时类似按值传递：忽略顶层 `const` 和引用；若要保留引用或只读属性，应显式加上 `&`、`const`。

```cpp
int value = 10;
const int& readOnly = value;

auto copy = readOnly;             // int，复制出独立变量
const auto& view = readOnly;      // const int&，不复制且只读
```

指针要区分顶层 `const` 与所指对象的 `const`：

```cpp
const int* p = &value;
auto p1 = p; // const int*，所指对象仍为 const

int* const p2 = &value;
auto p3 = p2; // int*，指针本身的顶层 const 被忽略
```

常见用法是简化迭代器和避免范围循环中的复制：

```cpp
for (const auto& item : items) {
    // 只读访问，不复制元素
}
```

## 三、`decltype` 推导

对未加括号的变量名，`decltype` 得到该变量声明时的类型，包括引用和 `const`：

```cpp
int value = 10;
int& ref = value;
const int readOnly = 20;

decltype(value) a = 1;     // int
decltype(ref) b = value;   // int&
decltype(readOnly) c = 2;  // const int
```

对其他表达式，结果依表达式的值类别决定：左值得到 `T&`，将亡值得到 `T&&`，纯右值得到 `T`。

```cpp
decltype((value)) ref2 = value; // int&，括号表达式是左值
decltype(value + 1) n = 2;       // int，结果是纯右值
```

特别注意：`decltype(value)` 和 `decltype((value))` 不同。前者识别未加括号的变量名，结果是声明类型；后者按左值表达式处理，结果是引用。

## 四、C++11 泛型代码中的用途

当函数返回类型依赖参数表达式时，可以用尾置返回类型：

```cpp
template <typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}
```

`decltype(a + b)` 会根据加法表达式推导返回类型。

## 五、初始化形式提醒

花括号初始化会影响 `auto` 推导：

```cpp
auto one{1};       // int
auto list = {1, 2}; // std::initializer_list<int>
```

普通变量初始化时优先使用清晰的 `auto name = value;` 写法。

## 六、快速判断

| 写法 | 主要规则 |
|---|---|
| `auto x = expr` | 根据初始化值推导，通常忽略顶层 `const` 和引用 |
| `auto& x = expr` | 推导类型并保留左值引用；`const` 按初始化对象传播 |
| `decltype(name)` | 未加括号的变量名，得到其声明类型 |
| `decltype(expr)` | 根据表达式值类别决定是 `T`、`T&` 还是 `T&&` |

实际开发中，`auto` 常用于迭代器、复杂类型和范围循环；`decltype` 常用于模板、尾置返回类型，以及需要精确获取表达式类型的场景。
