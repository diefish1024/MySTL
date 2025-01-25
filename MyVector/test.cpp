#include "my_vector.h"
#include <iostream>
#include <cassert>
#include <vector> // 用于比较的 std::vector

// 辅助函数，用于输出 MyVector 的内容
template <typename T>
void printMyVector(const MyVector<T>& vec, const std::string& message = "") {
  if (!message.empty()) {
    std::cout << message << ": ";
  }
  std::cout << "[";
  for (size_t i = 0; i < vec.size(); ++i) {
    std::cout << vec[i];
    if (i < vec.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "]" << std::endl;
}

template <typename T>
void printStdVector(const std::vector<T>& vec, const std::string& message = "") {
    if (!message.empty()) {
        std::cout << message << ": ";
    }
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}


int main() {
    // 默认构造函数测试
    MyVector<int> vec1;
    assert(vec1.empty());
    assert(vec1.size() == 0);
    assert(vec1.capacity() == 0);
    std::cout << "Default constructor test passed." << std::endl;

    // 带大小的构造函数测试
    MyVector<int> vec2(5);
    assert(vec2.size() == 5);
    assert(vec2.capacity() >= 5);
    printMyVector(vec2, "Vector2 with size 5");
    for (int x : vec2){
        assert(x == 0);
    }
    std::cout << "Size constructor test passed." << std::endl;


    // 带大小和值的构造函数测试
    MyVector<int> vec3(3, 10);
    assert(vec3.size() == 3);
    assert(vec3.capacity() >= 3);
    for (int x : vec3){
        assert(x == 10);
    }
    printMyVector(vec3, "Vector3 with size 3 and value 10");
    std::cout << "Size and value constructor test passed." << std::endl;

    // initializer_list构造函数测试
    MyVector<int> vec4 = {1, 2, 3, 4, 5};
    assert(vec4.size() == 5);
    assert(vec4[0] == 1);
    assert(vec4[4] == 5);
    printMyVector(vec4, "Vector4 with initializer_list");
    std::cout << "Initializer list constructor test passed." << std::endl;


    // 拷贝构造函数测试
    MyVector<int> vec5 = vec4;
    assert(vec5.size() == vec4.size());
    for (size_t i = 0; i < vec5.size(); ++i){
        assert(vec5[i] == vec4[i]);
    }
    printMyVector(vec5, "Vector5 copy from vector 4");
    std::cout << "Copy constructor test passed." << std::endl;

    // 移动构造函数测试
    MyVector<int> vec6 = std::move(vec5);
    assert(vec6.size() == 5);
    for (size_t i = 0; i < vec6.size(); ++i){
        assert(vec6[i] == vec4[i]);
    }
    printMyVector(vec6, "Vector6 move from vector 5");
    std::cout << "Move constructor test passed." << std::endl;

    // 拷贝赋值运算符测试
    MyVector<int> vec7;
    vec7 = vec6;
    assert(vec7.size() == vec6.size());
    for (size_t i = 0; i < vec7.size(); ++i){
        assert(vec7[i] == vec6[i]);
    }
    printMyVector(vec7, "Vector7 copy from vector 6");
    std::cout << "Copy assignment test passed." << std::endl;

    // 移动赋值运算符测试
    MyVector<int> vec8;
    vec8 = std::move(vec7);
    assert(vec8.size() == vec6.size());
    for (size_t i = 0; i < vec8.size(); ++i){
        assert(vec8[i] == vec6[i]);
    }
    printMyVector(vec8, "Vector8 move from vector 7");
    std::cout << "Move assignment test passed." << std::endl;

    // initializer list赋值测试
    MyVector<int> vec9;
    vec9 = {10, 20, 30};
    assert(vec9.size() == 3);
    assert(vec9[0] == 10);
    assert(vec9[2] == 30);
    printMyVector(vec9, "Vector9 assign from initializer list");
    std::cout << "Initializer list assignment test passed." << std::endl;

    // reserve 测试
    MyVector<int> vec10;
    vec10.reserve(10);
    assert(vec10.capacity() >= 10);
    std::cout << "Reserve test passed. Capacity after reserve: " << vec10.capacity() << std::endl;

    // shrink_to_fit 测试
    MyVector<int> vec11;
    vec11.reserve(10);
    vec11.push_back(1);
    vec11.push_back(2);
    vec11.shrink_to_fit();
    assert(vec11.capacity() == 2);
    printMyVector(vec11, "Vector11");
    std::cout << "Shrink to fit test passed. Capacity after shrink to fit: " << vec11.capacity() << std::endl;


    // push_back测试
    MyVector<int> vec12;
    vec12.push_back(100);
    vec12.push_back(200);
    assert(vec12.size() == 2);
    assert(vec12[0] == 100);
    assert(vec12[1] == 200);
    printMyVector(vec12, "Vector12");
    std::cout << "push_back test passed." << std::endl;


    // pop_back测试
    vec12.pop_back();
    assert(vec12.size() == 1);
    assert(vec12[0] == 100);
    printMyVector(vec12, "Vector12 after pop_back");
    std::cout << "pop_back test passed." << std::endl;

    // insert 测试
    vec12.insert(vec12.begin(), 50);
    assert(vec12.size() == 2);
    assert(vec12[0] == 50);
     assert(vec12[1] == 100);
     printMyVector(vec12, "Vector12 after insert");
    std::cout << "insert test passed." << std::endl;

    // insert 测试 cnt
    vec12.insert(vec12.end(), 3, 1000);
    assert(vec12.size() == 5);
    assert(vec12[2] == 1000);
    assert(vec12[3] == 1000);
    assert(vec12[4] == 1000);
    printMyVector(vec12, "Vector12 after insert cnt");
    std::cout << "insert cnt test passed." << std::endl;


    // insert 测试迭代器
    std::vector<int> tempVec = {1,2,3};
    vec12.insert(vec12.end(), tempVec.begin(), tempVec.end());
    assert(vec12.size() == 8);
    assert(vec12[5] == 1);
    assert(vec12[7] == 3);
    printMyVector(vec12, "Vector12 after insert iterator");
    std::cout << "insert iterator test passed." << std::endl;


    // emplace 测试
    vec12.emplace(vec12.begin() + 1, 55);
    assert(vec12.size() == 9);
    assert(vec12[1] == 55);
    printMyVector(vec12, "Vector12 after emplace");
    std::cout << "emplace test passed." << std::endl;


    // erase 测试
    vec12.erase(vec12.begin());
    assert(vec12.size() == 8);
    printMyVector(vec12, "Vector12 after erase");
    std::cout << "erase test passed." << std::endl;


   // erase 范围测试
    vec12.erase(vec12.begin(), vec12.begin() + 3);
     assert(vec12.size() == 5);
    printMyVector(vec12, "Vector12 after range erase");
    std::cout << "range erase test passed." << std::endl;

    // clear 测试
    vec12.clear();
    assert(vec12.empty());
    assert(vec12.size() == 0);
    printMyVector(vec12, "Vector12 after clear");
    std::cout << "clear test passed." << std::endl;


   // resize 测试
    vec12.resize(5, 1);
    assert(vec12.size() == 5);
    for (int x : vec12){
        assert(x == 1);
    }
    printMyVector(vec12, "Vector12 after resize with value");
    std::cout << "resize with value test passed." << std::endl;

    vec12.resize(3);
    assert(vec12.size() == 3);
    printMyVector(vec12, "Vector12 after resize without value");
    std::cout << "resize without value test passed." << std::endl;


    // at测试
    MyVector<int> vec13 = {10, 20, 30};
    assert(vec13.at(1) == 20);
    const MyVector<int> cvec13 = vec13;
    assert(cvec13.at(2) == 30);
    try{
        vec13.at(10);
    }catch(const std::out_of_range& e){
          std::cout << "at test out of range exception caught." << std::endl;
    }
    std::cout << "at test passed." << std::endl;



    // front/back测试
    MyVector<int> vec14 = {5, 6, 7};
     assert(vec14.front() == 5);
    assert(vec14.back() == 7);
    const MyVector<int> cvec14 = vec14;
    assert(cvec14.front() == 5);
    assert(cvec14.back() == 7);
    std::cout << "front/back test passed." << std::endl;


    // data 测试
    MyVector<int> vec15 = {100, 200, 300};
     int* dataPtr = vec15.data();
     assert(dataPtr[0] == 100);
    assert(dataPtr[2] == 300);
    const MyVector<int> cvec15 = vec15;
    const int* cdataPtr = cvec15.data();
     assert(cdataPtr[0] == 100);
    assert(cdataPtr[2] == 300);
     std::cout << "data test passed." << std::endl;



    // == and != 测试
    MyVector<int> vec16 = {1, 2, 3};
    MyVector<int> vec17 = {1, 2, 3};
    MyVector<int> vec18 = {3, 2, 1};
     assert(vec16 == vec17);
    assert(vec16 != vec18);
    std::cout << "== and != test passed." << std::endl;

    // 迭代器测试
    MyVector<int> vec19 = {10, 20, 30};
    int sum = 0;
    for (int x : vec19){
        sum += x;
    }
    assert(sum == 60);
     std::cout << "iterator test passed." << std::endl;



     // const 迭代器测试
    const MyVector<int> vec20 = {100, 200, 300};
    sum = 0;
    for(int x : vec20){
         sum += x;
    }
    assert(sum == 600);
    std::cout << "const iterator test passed." << std::endl;



    // reverse 迭代器测试
    MyVector<int> vec21 = {1, 2, 3};
    int i = 2;
    for (auto it = vec21.rbegin(); it != vec21.rend(); ++it){
        assert(*it == i);
        i--;
    }
    std::cout << "reverse iterator test passed." << std::endl;


    // const reverse 迭代器测试
    const MyVector<int> vec22 = {4, 5, 6};
    i = 6;
     for (auto it = vec22.crbegin(); it != vec22.crend(); ++it){
        assert(*it == i);
        i--;
    }
    std::cout << "const reverse iterator test passed." << std::endl;

     // swap 测试
    MyVector<int> vec23 = {1, 2, 3};
    MyVector<int> vec24 = {4, 5, 6};
    vec23.swap(vec24);
    assert(vec23[0] == 4);
    assert(vec24[2] == 3);
    printMyVector(vec23, "vec23 after swap");
    printMyVector(vec24, "vec24 after swap");
    std::cout << "swap test passed." << std::endl;


    std::cout << "\nAll tests passed!" << std::endl;

    return 0;
}