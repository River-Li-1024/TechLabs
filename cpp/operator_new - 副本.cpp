#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <ctime>
#include <stack>
#include <queue>
#include <memory>

/////////////////////////////////////////////////////////////////
// ��׼��operator new/delete
namespace operator_new_standard
{
    void* operator new(std::size_t sz) throw(std::bad_alloc)
    {
        printf("standard new alloc %d bytes\n", sz);
        if (sz == 0) {
            sz = 1;
        }

        while (true) {
            void* ptr = malloc(sz);
            if (ptr) {
                return ptr;
            }
            std::new_handler handler = std::get_new_handler();
            if (handler != nullptr) {
                handler();
            } else {
                throw std::bad_alloc();
            }
        }
    }

    void operator delete(void* ptr) throw()
    {
        printf("standard delete %p\n", ptr);
        if (ptr) {
            free(ptr);
            ptr = nullptr;
        }
    }

    // ���Դ���
    void unittest()
    {
        printf("��׼��operator new/delete\n");
        using namespace operator_new_standard;
        int *ptr = new int(10);
        delete ptr;
    }
}

/////////////////////////////////////////////////////////////////
// ��Խ����� operator new/delete
namespace operator_new_signature
{

    static const int signature = 0xDEADBEEF;    // �߽��
    typedef char Byte;

    void* operator new(std::size_t sz) throw(std::bad_alloc)
    {
        if (sz == 0) {
            sz = 0;
        }

        sz = sz + 2 * sizeof(int);
        void *ptr = malloc(sz);
        if (ptr) {
            // ���Խ����
            *(static_cast<int*>(ptr)) = signature;
            *(reinterpret_cast<int*>(static_cast<Byte*>(ptr)+sz - sizeof(int))) = signature;
            // ���������ĵ�ַ
            return static_cast<Byte*>(ptr)+sizeof(int);
        }

        while (true) {
            std::new_handler handler = std::get_new_handler();
            if (handler) {
                handler();
            } else {
                throw std::bad_alloc();
            }
        }
    }

    void operator delete(void* ptr)
    {
        if (ptr)  {
            ptr = static_cast<Byte*>(ptr) - sizeof(int);
            free(ptr);
            ptr = nullptr;
        }
    }

    // ���Դ���
    void unittest()
    {
        printf("��Խ����� operator new/delete\n");
        using namespace operator_new_standard;
        int *ptr = new int(10);
        delete ptr;
    }
}

/////////////////////////////////////////////////////////////////
// ���Դ���
int main(int argc, char **argv)
{
    operator_new_standard::unittest();
    operator_new_signature::unittest();

    getchar();
    return 0;
}