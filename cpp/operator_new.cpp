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

#define operator_new_standard

/////////////////////////////////////////////////////////////////
// 标准的operator new/delete
#ifdef operator_new_standard
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

// 测试代码
class StandardClass
{
};

void unittest()
{
    printf("standard operator new/delete\n");
    //using namespace operator_new_standard;
    int *iptr = new int(10);
    delete iptr;

    char *cptr = new char[100];
    delete[] cptr;
}
#endif //operator_new_standard

/////////////////////////////////////////////////////////////////
// 带越界检查的 operator new/delete
#ifdef operator_new_signature
static const int signature = 0xDEADBEEF;    // 边界符
typedef char Byte;

void* operator new(std::size_t sz) throw(std::bad_alloc)
{
    printf("signature new alloc %d bytes\n", sz);

    if (sz == 0) {
        sz = 0;
    }

    sz = sz + 2 * sizeof(int);
    void *ptr = malloc(sz);
    if (ptr) {
        // 添加越界检查
        *(static_cast<int*>(ptr)) = signature;
        *(reinterpret_cast<int*>(static_cast<Byte*>(ptr)+sz - sizeof(int))) = signature;
        // 返回真正的地址
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
    printf("signature delete %p\n", ptr);

    if (ptr)  {
        ptr = static_cast<Byte*>(ptr) - sizeof(int);
        free(ptr);
        ptr = nullptr;
    }
}

// 测试代码
void unittest()
{
    printf("signature operator new/delete\n");
    using namespace operator_new_signature;
    int *ptr = new int(10);
    delete ptr;
}
#endif //operator_new_signature

/////////////////////////////////////////////////////////////////
// 测试代码
int main(int argc, char **argv)
{
    unittest();

    getchar();
    return 0;
}