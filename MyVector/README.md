# MyVector

自定义动态数组实现，类似 `std::vector`

## 功能状态

| 组件                             | 进度 |
|----------------------------------|------|
| 类型别名                          | √    |
| `MyVector()`                     | √    |
| `MyVector(size)`                 | √    |
| `MyVector(size, value)`          | √    |
| `MyVector(init_list)`            | √    |
| `MyVector(const MyVector&)`      | √    |
| `MyVector(MyVector&&)`           | √    |
| `~MyVector()`                    | √    |
| `operator=`                      | √    |
| `operator=(init_list)`           | √    |
| `size()`                         | √    |
| `capacity()`                     | √    |
| `empty()`                        | √    |
| `reserve()`                      | √    |
| `shrink_to_fit()`                | √    |
| `operator[]` (非 `const`)        | √    |
| `operator[]` (`const`)           | √    |
| `at()` (非 `const`)              | √    |
| `at()` (`const`)                 | √    |
| `front()` (非 `const`)           | √    |
| `front()` (`const`)              | √    |
| `back()` (非 `const`)            | √    |
| `back()` (`const`)               | √    |
| `data()` (非 `const`)            | √    |
| `data()` (`const`)               | √    |
| `push_back(const&)`              | √    |
| `push_back(T&&)`                 | √    |
| `pop_back()`                     | √    |
| `insert(pos, const&)`            | √    |
| `insert(pos, T&&)`               | √    |
| `insert(pos, cnt, const&)`       | √    |
| `insert(pos, first, last)`       | √    |
| `emplace(pos, args...)`          | √    |
| `erase(pos)`                     | √    |
| `erase(first, last)`             | √    |
| `clear()`                        | √    |
| `resize(n)`                      | √    |
| `resize(n, value)`               | √    |
| `begin()` (非 `const`)           | √    |
| `begin()` (`const`)              | √    |
| `end()` (非 `const`)             | √    |
| `end()` (`const`)                | √    |
| `cbegin()`                       | √    |
| `cend()`                         | √    |
| `rbegin()` (非 `const`)          | √    |
| `rbegin()` (`const`)             | √    |
| `rend()` (非 `const`)            | √    |
| `rend()` (`const`)               | √    |
| `crbegin()`                      | √    |
| `crend()`                        | √    |
| `swap()`                         | √    |
| `operator==`                     | √    |
| `operator!=`                     | √    |

## 测试

编译运行 `test.cpp`
```
g++ -std=c++17 -o test test.cpp
./test
```