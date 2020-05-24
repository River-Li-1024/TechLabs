#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>

//#define SORT_SELECT

namespace NS_SORT_SELECT
{
    ////////////////////////////////////////
    // ѡ������
    void SelectSort(std::vector<int>& vec)
    {
        for (int i = 0; i < vec.size(); i++) {
            // �ҳ���С����
            int idx = i;
            for (int j = i + 1; j < vec.size(); j++) {
                if (vec[j] < vec[idx]) {
                    idx = j;
                }
            }
            using std::swap;
            swap(vec[idx], vec[i]);
        }
    }
}

#ifdef SORT_SELECT
/////////////////////////////////////////////////////////////////
// ���Դ���
using namespace NS_SORT_SELECT;
int main(int argc, char **argv)
{
    std::vector<int> vec = { 4, 3, 5, 1, 9, 2, 7, 6, 8 };

    std::for_each(vec.begin(), vec.end(), [](const int& val){printf("%d ", val); });
    std::printf("\n");

    SelectSort(vec);

    std::for_each(vec.begin(), vec.end(), [](const int& val){printf("%d ", val); });
    std::printf("\n");

    getchar();
    return 0;
}
#endif //EXCEPTION