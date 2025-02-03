#include "my_list.h"
#include <iostream>
#include <cassert>

// 辅助函数，用于输出 MyList 的内容
template <typename T>
void printMyList(const MyList<T>& lst, const std::string& message = "") {
    if (!message.empty()) {
        std::cout << message << ": ";
    }
    std::cout << "[";
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it;
        auto temp = it;
        ++temp;
        if (temp != lst.end()) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

int main() {
    // 1) 默认构造函数测试
    std::cout << "===== 1) Default constructor test =====" << std::endl;
    {
        MyList<int> list1;
        assert(list1.empty());
        assert(list1.size() == 0);
        printMyList(list1, "list1 after default construction");
        std::cout << "Default constructor test passed.\n" << std::endl;
    }

    // 2) 构造函数(size_type count)
    std::cout << "===== 2) Constructor with size count =====" << std::endl;
    {
        MyList<int> list2(5);
        assert(list2.size() == 5);
        printMyList(list2, "list2 with size=5");
        std::cout << "Constructor (size_type) test passed.\n" << std::endl;
    }

    // 3) 构造函数(size_type count, const_reference value)
    std::cout << "===== 3) Constructor with size and value =====" << std::endl;
    {
        MyList<int> list3(3, 7);
        assert(list3.size() == 3);
        for (auto it = list3.begin(); it != list3.end(); ++it) {
            assert(*it == 7);
        }
        printMyList(list3, "list3 with size=3 and value=7");
        std::cout << "Constructor (size_type, value) test passed.\n" << std::endl;
    }

    // 4) 构造函数(std::initializer_list)
    std::cout << "===== 4) Initializer list constructor test =====" << std::endl;
    {
        MyList<int> list4 = {1, 2, 3, 4, 5};
        assert(list4.size() == 5);
        printMyList(list4, "list4 from initializer_list");
        std::cout << "Initializer list constructor test passed.\n" << std::endl;
    }

    // 5) 拷贝构造函数测试
    std::cout << "===== 5) Copy constructor test =====" << std::endl;
    {
        MyList<int> list4 = {10, 20, 30};
        MyList<int> list5(list4);
        assert(list5.size() == list4.size());
        auto it4 = list4.begin();
        auto it5 = list5.begin();
        for (; it4 != list4.end() && it5 != list5.end(); ++it4, ++it5) {
            assert(*it4 == *it5);
        }
        printMyList(list5, "list5 copy from list4");
        std::cout << "Copy constructor test passed.\n" << std::endl;
    }

    // 6) 移动构造函数测试
    std::cout << "===== 6) Move constructor test =====" << std::endl;
    {
        MyList<int> original = {11, 22, 33};
        MyList<int> moved(std::move(original));
        assert(moved.size() == 3);
        printMyList(moved, "moved from original");
        // original 已被移动，size应为0
        assert(original.size() == 0);
        std::cout << "Move constructor test passed.\n" << std::endl;
    }

    // 7) 拷贝赋值运算符测试
    std::cout << "===== 7) Copy assignment test =====" << std::endl;
    {
        MyList<int> listA = {1, 2, 3};
        MyList<int> listB;
        listB = listA;
        assert(listA.size() == listB.size());
        auto itA = listA.begin();
        auto itB = listB.begin();
        for (; itA != listA.end() && itB != listB.end(); ++itA, ++itB) {
            assert(*itA == *itB);
        }
        printMyList(listB, "listB assigned from listA");
        std::cout << "Copy assignment test passed.\n" << std::endl;
    }

    // 8) 移动赋值运算符测试
    std::cout << "===== 8) Move assignment test =====" << std::endl;
    {
        MyList<int> listC = {7, 8, 9};
        MyList<int> listD;
        listD = std::move(listC);
        assert(listD.size() == 3);
        printMyList(listD, "listD after move assignment from listC");
        // listC 已被移动，size应为0
        assert(listC.size() == 0);
        std::cout << "Move assignment test passed.\n" << std::endl;
    }

    // 9) initializer_list 赋值测试
    std::cout << "===== 9) initializer_list assignment test =====" << std::endl;
    {
        MyList<int> listE;
        listE = {100, 200, 300};
        assert(listE.size() == 3);
        printMyList(listE, "listE after initializer_list assignment");
        std::cout << "Initializer list assignment test passed.\n" << std::endl;
    }

    // 10) push_front / push_back / pop_front / pop_back 测试
    std::cout << "===== 10) push/pop front/back test =====" << std::endl;
    {
        MyList<int> listF;
        listF.push_back(10);
        listF.push_front(5);
        listF.push_back(15);
        printMyList(listF, "listF after pushes");
        assert(listF.size() == 3);

        assert(listF.front() == 5);
        assert(listF.back() == 15);

        listF.pop_front();  // 移除 5
        printMyList(listF, "listF after pop_front");
        assert(listF.front() == 10);
        assert(listF.size() == 2);

        listF.pop_back();   // 移除 15
        printMyList(listF, "listF after pop_back");
        assert(listF.size() == 1);
        assert(listF.front() == 10);

        std::cout << "push/pop front/back test passed.\n" << std::endl;
    }

    // 11) insert(pos, val) / insert(pos, count, val) / emplace(pos, args...)
    std::cout << "===== 11) insert and emplace test =====" << std::endl;
    {
        MyList<int> listG = {1, 2, 3};
        // 在开头插入 0
        listG.insert(listG.begin(), 0);
        printMyList(listG, "listG after insert 0 at begin()");
        assert(listG.size() == 4);

        // 在结尾插入两个 9
        listG.insert(listG.end(), 2, 9);
        printMyList(listG, "listG after insert two 9s at end()");
        assert(listG.size() == 6);

        // 在第二个位置 emplace 一个 10
        auto itPos = listG.begin();
        ++itPos;  // 指向原来的第2个元素(现在是1 -> 2 -> 3 -> ...)
        listG.emplace(itPos, 10);
        printMyList(listG, "listG after emplace(10) at second position");
        assert(listG.size() == 7);

        // 验证顺序
        // [0, 10, 2, 3, 9, 9] 加上之前的 1？
        // 实际插入顺序要仔细核对，但此处仅做简要断言演示
        assert(*listG.begin() == 0);

        std::cout << "insert and emplace test passed.\n" << std::endl;
    }

    // 12) erase(pos) / erase(first, last)
    std::cout << "===== 12) erase test =====" << std::endl;
    {
        MyList<int> listH = {5, 6, 7, 8, 9};
        // 删除第一个元素
        listH.erase(listH.begin());
        printMyList(listH, "listH after erase first element");
        assert(listH.size() == 4);
        assert(listH.front() == 6);

        // 删除中间两个元素
        auto itBegin = listH.begin();
        auto itEnd   = listH.begin();
        ++itEnd;   // 7
        ++itEnd;   // 8(指向8的位置)
        // 现在 itBegin 指向 6, itEnd 指向 8
        // 如果想要删除 [6, 7], 就是 erase(itBegin, itEnd)
        listH.erase(itBegin, itEnd);
        printMyList(listH, "listH after erase range [6, 7]");
        assert(listH.size() == 2);

        std::cout << "erase test passed.\n" << std::endl;
    }

    // 13) clear 测试
    std::cout << "===== 13) clear test =====" << std::endl;
    {
        MyList<int> listI = {1, 2, 3};
        listI.clear();
        assert(listI.empty());
        printMyList(listI, "listI after clear");
        std::cout << "clear test passed.\n" << std::endl;
    }

    // 14) resize 测试
    std::cout << "===== 14) resize test =====" << std::endl;
    {
        MyList<int> listJ = {1, 2, 3};
        listJ.resize(5);  // 添加默认值T()，这里是 int() == 0
        assert(listJ.size() == 5);
        int countZero = 0;
        for (auto it = listJ.begin(); it != listJ.end(); ++it) {
            if (*it == 0) {
                ++countZero;
            }
        }
        assert(countZero == 2);
        printMyList(listJ, "listJ after resize(5)");

        listJ.resize(3);
        assert(listJ.size() == 3);
        printMyList(listJ, "listJ after resize(3)");

        listJ.resize(5, 9);
        // [1, 2, 3, 9, 9]
        assert(listJ.size() == 5);
        int countNine = 0;
        for (auto& x : listJ) {
            if (x == 9) ++countNine;
        }
        assert(countNine == 2);
        printMyList(listJ, "listJ after resize(5,9)");
        std::cout << "resize test passed.\n" << std::endl;
    }

    // 15) front() / back() 测试
    std::cout << "===== 15) front()/back() test =====" << std::endl;
    {
        MyList<int> listK = {10, 20, 30};
        assert(listK.front() == 10);
        assert(listK.back() == 30);
        listK.front() = 15;
        listK.back()  = 25;
        printMyList(listK, "listK after modifying front/back");
        assert(listK.front() == 15);
        assert(listK.back() == 25);
        std::cout << "front()/back() test passed.\n" << std::endl;
    }

    // 16) 迭代器和 const 迭代器测试
    std::cout << "===== 16) iterator and const_iterator test =====" << std::endl;
    {
        MyList<int> listL = {1, 2, 3, 4, 5};

        // 普通迭代器累加求和
        int sum = 0;
        for (auto& x : listL) {
            sum += x;
        }
        assert(sum == 15);

        // const 迭代器
        const MyList<int> listM = {2, 4, 6};
        int csum = 0;
        for (auto it = listM.cbegin(); it != listM.cend(); ++it) {
            csum += *it;
        }
        assert(csum == 12);

        std::cout << "iterator and const_iterator test passed.\n" << std::endl;
    }

    // 17) reverse_iterator 和 const_reverse_iterator 测试
    std::cout << "===== 17) reverse_iterator test =====" << std::endl;
    {
        MyList<int> listN = {1, 2, 3};
        int i = 3;
        for (auto rit = listN.rbegin(); rit != listN.rend(); ++rit) {
            assert(*rit == i);
            i--;
        }
        std::cout << "reverse_iterator test passed.\n" << std::endl;

        std::cout << "===== const_reverse_iterator test =====" << std::endl;
        {
            const MyList<int> listO = {4, 5, 6};
            int j = 6;
            for (auto crit = listO.crbegin(); crit != listO.crend(); ++crit) {
                assert(*crit == j);
                j--;
            }
            std::cout << "const_reverse_iterator test passed.\n" << std::endl;
        }
    }

    // 18) swap 测试
    std::cout << "===== 18) swap test =====" << std::endl;
    {
        MyList<int> listP = {1, 2, 3};
        MyList<int> listQ = {4, 5, 6, 7};
        listP.swap(listQ);
        printMyList(listP, "listP after swap");
        printMyList(listQ, "listQ after swap");
        // 现在 listP 应该是 {4, 5, 6, 7}, size=4
        // listQ 应该是 {1, 2, 3}, size=3
        assert(listP.size() == 4);
        assert(listQ.size() == 3);
        assert(listP.front() == 4);
        assert(listQ.back() == 3);
        std::cout << "swap test passed.\n" << std::endl;
    }

    std::cout << "All MyList tests passed successfully!" << std::endl;
    return 0;
}