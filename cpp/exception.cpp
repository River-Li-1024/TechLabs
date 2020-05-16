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

//#define EXCEPTION

namespace exception
{
    class TestExceptionBase
    {
    public:
        int cnt;
        TestExceptionBase(int c) : cnt(c) {}
    };

    class TestExceptionDerived : public TestExceptionBase
    {
    public:
        TestExceptionDerived(int c) : TestExceptionBase(c) {}
    };


    /////////////////////////////////////////////////////////////////
    // �����쳣
    class TestClass
    {
    private:
        int* iptr;
    public:
        //�쳣������ȷ����Դ����ȷ�ͷ�
        TestClass() try : iptr(nullptr)
        {
                iptr = new int(10);
                printf("TestClass::Constructor throw exception.\n");
                throw TestExceptionDerived(0);
        } catch (TestExceptionBase& e) {
            e.cnt++;//�쳣���������ò��񣬿��ڲ�����޸�
            if (iptr) {
                delete iptr;
                iptr = nullptr;
            }
            printf("TestClass::Constructor hit on Exception Base.\n");
            throw;// �����׳��������ǻ᷵��ָ��
        } catch (...) {
            printf("TestClass::Constructor hit ...\n");
            throw;// �����׳��������ǻ᷵��ָ��
        }

        ~TestClass()
        {
            printf("TestClass::Destructor hit.\n");
            if (iptr) {
                delete iptr;
                iptr = nullptr;
            }
        }
    };
}

#ifdef EXCEPTION
/////////////////////////////////////////////////////////////////
// ���Դ���
int main(int argc, char **argv)
{
    using namespace exception;
    TestClass* ptr = nullptr;
    try {
        ptr = new TestClass();
    } catch (exception::TestExceptionDerived& e) {
        e.cnt++;
        printf("TestClass catch exception:%d.\n", e.cnt);
    }
    printf("ptr=%p\n", ptr);

    getchar();
    return 0;
}
#endif //EXCEPTION