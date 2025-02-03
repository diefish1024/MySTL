# MyList

自定义双向链表实现，类似于 `std::list`，支持动态内存管理、双向迭代器等功能。

---

## 功能状态

| 组件                              | 进度 |
|-----------------------------------|------|
| 类型别名                          | √    |
| `MyList()`                        | √    |
| `MyList(size)`                    | √    |
| `MyList(size, value)`             | √    |
| `MyList(init_list)`               | √    |
| `MyList(const MyList&)`           | √    |
| `MyList(MyList&&)`                | √    |
| `~MyList()`                       | √    |
| `operator=`                       | √    |
| `operator=(init_list)`            | √    |
| `size()`                          | √    |
| `empty()`                         | √    |
| `front()` (非 `const`)            | √    |
| `front()` (`const`)               | √    |
| `back()` (非 `const`)             | √    |
| `back()` (`const`)                | √    |
| `push_front(const&)`              | √    |
| `push_front(T&&)`                 | √    |
| `pop_front()`                     | √    |
| `push_back(const&)`               | √    |
| `push_back(T&&)`                  | √    |
| `pop_back()`                      | √    |
| `insert(pos, const&)`             | √    |
| `insert(pos, T&&)`                | √    |
| `insert(pos, cnt, const&)`        | √    |
| `insert(pos, first, last)`        | √    |
| `insert(pos, init_list)`          | √    |
| `emplace(pos, args...)`           | √    |
| `erase(pos)`                      | √    |
| `erase(first, last)`              | √    |
| `clear()`                         | √    |
| `resize(n)`                       | √    |
| `resize(n, value)`                | √    |
| `begin()` (非 `const`)            | √    |
| `begin()` (`const`)               | √    |
| `end()` (非 `const`)              | √    |
| `end()` (`const`)                 | √    |
| `cbegin()`                        | √    |
| `cend()`                          | √    |
| `rbegin()` (非 `const`)           | √    |
| `rbegin()` (`const`)              | √    |
| `rend()` (非 `const`)             | √    |
| `rend()` (`const`)                | √    |
| `crbegin()`                       | √    |
| `crend()`                         | √    |
| `swap()`                          | √    |
| `operator==`                      | √    |
| `operator!=`                      | √    |
| 迭代器递增 (`++`)                 | √    |
| 迭代器递减 (`--`)                 | √    |
| 解引用 (`*`)                      | √    |
| 成员访问 (`->`)                   | √    |
| 迭代器相等比较 (`==`)             | √    |
| 迭代器不等比较 (`!=`)             | √    |

---

## 测试

编译运行 `test.cpp`

```
g++ -std=c++17 -o test test.cpp
./test
```

