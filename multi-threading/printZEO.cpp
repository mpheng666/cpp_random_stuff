// Suppose you are given the following code:
// class ZeroEvenOdd {
// public
//     ZeroEvenOdd(int n) { ... }  // constructor
// public
//     void Zero(printNumber) { ... }  // only output 0's
// public
//     void even(printNumber) { ... }  // only output even numbers
// public
//     void odd(printNumber) { ... }  // only output odd numbers

// The same instance of ZeroEvenOdd will be passed to three different threads
// Thread A will call zero() which should only output 0's.
// Thread B will call even() which should only output even numbers
// Thread C will call odd() which should only output odd numbers

// Each of the threads is given a printNumber method to output an integer.
// Modify the given program to output the series 010203040506... where the
// length of the series must be 2n. Example 1
//     : Input : n = 2 Output : "0102" Explanation
//     : There are three threads being fired asynchronously.
//      One of them calls zero(),
//       the other calls even(),
//       and the last one calls odd().
//         “0102 " is the correct output.
//
// Example 2 : Input : n = 5 Output : "0102030405"
//  Example 3 : Input : n = 0 Output : "0"

#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
//#include <chrono>

using namespace std;

// implement solution in this class
class ZeroEvenOdd {
private:
    int m_N;
    int m_temp{0};
    bool m_print_zero_flag{false};
    std::mutex m_mtx;

public:
    ZeroEvenOdd(int n) { m_N = n; }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        while (m_temp <= m_N) {
        m_mtx.lock();
            if (m_temp == 0 || m_print_zero_flag) {
                printNumber(m_temp);
                if(!m_print_zero_flag)
                    ++m_temp;
        m_mtx.unlock();
                m_print_zero_flag = false;
            }
        }
    }

    void even(function<void(int)> printNumber) {
        while (m_temp <= m_N) {
        m_mtx.lock();
            if (m_temp != 0 && m_temp % 2 == 0) {
                printNumber(m_temp);
                ++m_temp;
                m_print_zero_flag = true;
            }
        m_mtx.unlock();
        }
    }

    void odd(function<void(int)> printNumber) {
        while (m_temp <= m_N) {
        m_mtx.lock();
            if (m_temp % 2 == 1) {
                printNumber(m_temp);
                ++m_temp;
                m_print_zero_flag = true;
            }
        m_mtx.unlock();
        }
    }
};

/* !!! Note, do NOT modify/add anything below this line !!! */
class Tester {
public:
    Tester() {}

    void test(int n) {
        cout << endl << "n = " << n << " => ";
        ZeroEvenOdd zeo(n);
        try {
            std::thread threadA(_threadFun, 'A', std::ref(zeo));
            std::thread threadB(_threadFun, 'B', std::ref(zeo));
            std::thread threadC(_threadFun, 'C', std::ref(zeo));
            threadA.join();
            threadB.join();
            threadC.join();
        } catch (const std::exception& ex) {
            cout << endl << "!!!! " << ex.what() << endl;
        }
    }

private:
    // printNumber(x) outputs "x", where x is an integer.
    static void _printNmber(int no) { cout << no; }

    static void _threadFun(char id, ZeroEvenOdd& zeo) {
        if (id == 'A')
            zeo.zero(_printNmber);
        else if (id == 'B')
            zeo.even(_printNmber);
        else if (id == 'C')
            zeo.odd(_printNmber);
        else
            return;
    }
};

int main(void) {
    Tester tester;

    // for (int i = 0; i < 10; i++) tester.test(i);
    tester.test(1);
    std::cout << '\n';

    return 0;
}