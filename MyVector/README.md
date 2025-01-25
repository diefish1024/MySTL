# MyVector

自定义动态数组实现，类似 `std::vector`

## 功能状态

| 功能/方法                     | 进度 |
|---------------------------------|-------|
| 类型别名 (`value_type`, `size_type`, 等) | √    |
| 默认构造函数 `MyVector()`      | √    |
| 带有大小的构造函数 `MyVector(size)`   | √    |
| 带有大小和初始值的构造函数 `MyVector(size, value)`| √    |
| 初始化列表构造函数 `MyVector(init_list)`     | √    |
| 拷贝构造函数 `MyVector(const MyVector&)`   | √    |
| 移动构造函数 `MyVector(MyVector&&)`   | √    |
| 析构函数 `~MyVector()`           | √    |
| 赋值运算符 `operator=`          | √    |
| 初始化列表赋值 `operator=(init_list)` | √    |
| `size()`                         | √    |
| `capacity()`                     | √    |
| `empty()`                        | √    |
| `reserve()`                      | √    |
| `shrink_to_fit()`                | √    |
| `operator[]` (非 `const`)          | √    |
| `operator[]` (`const`)          | √    |
| `at()` (非 `const`)            | √    |
| `at()` (`const`)              | √    |
| `front()` (非 `const`)           | √    |
| `front()` (`const`)            | √    |
| `back()` (非 `const`)            | √    |
| `back()` (`const`)             | √    |
| `data()` (非 `const`)            | √    |
| `data()` (`const`)              | √    |
| `push_back(const&)`             | √    |
| `push_back(T&&)`                 | √    |
| `pop_back()`                    | √    |
| `insert(pos, const&)`           | √    |
| `insert(pos, T&&)`                | √    |
| `insert(pos, cnt, const&)`      | √    |
| `insert(pos, first, last)`       | 还没解决通过 SFINAE 限制迭代器    |
| `emplace(pos, args...)`        | √    |
| `erase(pos)`                  | √    |
| `erase(first, last)`             | √    |
| `clear()`                       | √    |
| `resize(n)`                     | √    |
| `resize(n, value)`              | √    |
| `begin()` (非 `const`)          | √    |
| `begin()` (`const`)            | √    |
| `end()` (非 `const`)            | √    |
| `end()` (`const`)              | √    |
| `cbegin()`                       | √    |
| `cend()`                         | √    |
| `rbegin()` (非 `const`)         | √    |
| `rbegin()` (`const`)           | √    |
| `rend()` (非 `const`)           | √    |
| `rend()` (`const`)             | √    |
| `crbegin()`                     | √    |
| `crend()`                       | √    |
| `swap()`                        | √    |
| `operator==`                   | √    |
| `operator!=`                   | √    |

## 测试

直接编译 `test.cpp`