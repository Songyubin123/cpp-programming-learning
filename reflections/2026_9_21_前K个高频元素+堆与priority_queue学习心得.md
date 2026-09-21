# 前 K 个高频元素与堆学习心得

今天我学习了 LeetCode 347“前 K 个高频元素”，理解了“统计频率，再保留频率最高的 K 个元素”的思路。

## 今天掌握的重点

- 使用 `unordered_map<int, int>` 统计数字出现次数。它适合本题，因为不需要按 key 排序，查找和更新的平均复杂度是 `O(1)`。
- 理解 `pair<int, int>`：`first` 表示数字，`second` 表示出现次数。
- 理解小顶堆和 `priority_queue`：`top()` 是当前优先级最高的元素；本题用固定大小为 `k` 的小顶堆，堆超过 `k` 个元素时弹出频率最小的元素。
- 理解比较器 `operator()`：`return lhs.second > rhs.second` 按频率建立小顶堆。比较器返回 `bool`，只是定义元素之间的顺序，不能简单理解为返回 `true` 的元素优先级高。
- 理解 `lhs`、`rhs` 只是参数名，分别表示比较的两个元素；`struct` 成员默认是 `public`，而 `class` 成员默认是 `private`。
- 理解引用和指针的区别：`const T&` 是引用，访问成员使用 `.`；指针才使用 `->`。
- 理解迭代器和范围 `for`：`begin()` 指向第一个元素，`end()` 指向末尾之后；`for (const auto& value : map)` 与手写迭代器遍历本质相同，前者更简洁。

## 代码中需要注意

- 比较器放在 `class` 中时要写 `public:`，否则 `priority_queue` 无法调用 `operator()`。
- `pri_que.push(value);` 后面不能漏分号。
- `pri_que.top()` 返回的是 `pair`，取数字要写 `.first`，取频率要写 `.second`。
- `pair` 是对象或引用时使用 `.`，不能把 `lhs.second` 写成 `lhs->second`。

## 复杂度与后续复习

固定大小小顶堆方案的时间复杂度是 `O(n log k)`，空间复杂度是 `O(n)`。我还需要继续通过小例子练习比较器的排序规则，避免把“比较器返回 `true`”和“优先级更高”混为一谈。
