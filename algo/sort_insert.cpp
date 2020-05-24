#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <vector>
#include <ctime>
#include <stack>
#include <queue>
#include <memory>

#define INSERT_SORT

namespace INSERT_SORT_NS
{
    ////////////////////////////////////////////////////////
    // ��������
    void InsertSort(std::vector<int>& arr)
    {
        using std::swap;
        int len = arr.size();
        if (len <= 1) {
            return;
        }

        int i = 0;
        int key = 0;
        for (int j = 1; j < len; j++) {
            key = arr[j];
            i = j - 1;

            while (i >= 0 && arr[i] > key) {    // �ƶ��м������
                arr[i + 1] = arr[i];
                i--;
            }
            arr[i + 1] = key;
        }
    }

    // ��������-�Ľ��������Ϊ���ֲ��ң�ʱ�临�Ӷȱ�ΪNlgN
    void InsertSort(std::vector<int>& arr)
    {
        using std::swap;
        int len = arr.size();
        if (len <= 1) {
            return;
        }

        int i = 0;
        int key = 0;
        for (int j = 1; j < len; j++) {
            key = arr[j];
            i = j - 1;

            //ʹ�ö��ֲ���
            int min = 0;
            int max = j - 1;
            for (int i = 0; i < std::log2(j); i++) {
                if (arr[i] == key) {

                }


            }
            while (i >= 0 && arr[i] > key) {    // �ƶ��м������
                arr[i + 1] = arr[i];
                i--;
            }
            arr[i + 1] = key;
        }
    }
}

#ifdef INSERT_SORT
/////////////////////////////////////////////////////////////////
// ���Դ���
using namespace INSERT_SORT_NS;
int main(int argc, char **argv)
{
    std::vector<int> arr = { 2, 8, 7, 1, 3, 5, 6, 4 };
    printf("arr:\n");
    for (std::vector<int>::iterator iter = std::begin(arr); iter != std::end(arr); iter++) {
        printf("%d ", *iter);
    }
    printf("\n");

    InsertSort(arr);

    printf("sorted arr:\n");
    for (std::vector<int>::iterator iter = std::begin(arr); iter != std::end(arr); iter++) {
        printf("%d ", *iter);
    }
    printf("\n");

    getchar();
    return 0;
}
#endif //EXCEPTION