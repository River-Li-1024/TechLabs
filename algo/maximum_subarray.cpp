#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define MAXIMUM_SUBARRAY

namespace MAXIMUM_SUBARRAY_NS
{
    struct SubArrayInfo
    {
        int low;
        int high;
        int sum;
    };

    //////////////////////////////////////////
    //�������������-�����ⷨ
    SubArrayInfo FindmaximumSubarray_Violence(std::vector<int>& vec, int low, int high)
    {
        if (low == high) {
            return{ low, high, vec[low] };
        }

        int sum_max = INT_MIN;
        int left_max = low;
        int right_max = low;

        // �����������п��ܵ��������
        int sum = 0;
        for (int i = low; i <= high; i++) {
            sum = 0;
            for (int j = i; j <= high; j++) {
                sum += vec[j];
                if (sum > sum_max) {
                    sum_max = sum;
                    left_max = i;
                    right_max = j;
                }
            }
        }

        return{ left_max, right_max, sum_max };
    }

    //////////////////////////////////////////
    //�������������-�ݹ�ⷨ
    SubArrayInfo FindMaximumCrossingSubarray(std::vector<int>& vec, int low, int mid, int high)
    {
        // �������ߣ���������
        int sum = 0;
        int leftSum = INT_MIN;
        int leftIdx = mid;
        for (int i = mid; i >= low; i--) {
            sum += vec[i];
            if (sum > leftSum) {
                leftSum = sum;
                leftIdx = i;
            }
        }

        // �����Ұ�ߣ���������
        sum = 0;
        int rightSum = INT_MIN;
        int rightIdx = mid;
        for (int i = mid + 1; i <= high; i++) {
            sum += vec[i];
            if (sum > rightSum) {
                rightSum = sum;
                rightIdx = i;
            }
        }

        return{ leftIdx, rightIdx, leftSum + rightSum };
    }

    SubArrayInfo FindmaximumSubarray(std::vector<int>& vec, int low, int high)
    {
        if (low == high) {
            return{ low, high, vec[low] };
        } else {
            int mid = (low + high) / 2;
            //��ֳ������֣��ݹ����
            SubArrayInfo leftInfo = FindmaximumSubarray(vec, low, mid);
            SubArrayInfo rightInfo = FindmaximumSubarray(vec, mid + 1, high);
            //������յ㲿��
            SubArrayInfo midInfo = FindMaximumCrossingSubarray(vec, low, mid, high);
            //ѡ����
            if (leftInfo.sum >= midInfo.sum && leftInfo.sum >= rightInfo.sum) {
                return leftInfo;
            } else if (rightInfo.sum > midInfo.sum && rightInfo.sum >= leftInfo.sum) {
                return rightInfo;
            } else {
                return midInfo;
            }
        }
    }

    //////////////////////////////////////////
    //�������������-���Խⷨ
    SubArrayInfo FindmaximumSubarray_Linear(std::vector<int>& vec, int low, int high)
    {
        int max_sum = INT_MIN;
        int left_idx = low;
        int right_idx = low;

        int sum = 0;
        int sum_idx = low;
        for (int i = low; i <= high; i++) {
            sum += vec[i];
            if (sum > max_sum) {
                max_sum = sum;
                left_idx = sum_idx;
                right_idx = i;
            }
            if (sum < 0) {
                sum = 0;
                sum_idx = i + 1;
            }
        }
        return{ left_idx, right_idx, max_sum };
    }
}

#ifdef MAXIMUM_SUBARRAY
/////////////////////////////////////////////////////////////////
// ���Դ���
using namespace MAXIMUM_SUBARRAY_NS;
int main(int argc, char **argv)
{
    //std::vector<int> vec = { 1, 2, -3, 2, -1, -3, -1, 4, -2, 5 };
    std::vector<int> vec = { -5, -2, -3, -2 };
    //std::vector<int> vec = { -1, 2 };
    //std::vector<int> vec = { -1 };
    // ���η�
    SubArrayInfo info = FindmaximumSubarray(vec, 0, vec.size() - 1);
    printf("low(%d) high(%d) sum(%d)\n", info.low, info.high, info.sum);

    // ������
    SubArrayInfo info2 = FindmaximumSubarray_Violence(vec, 0, vec.size() - 1);
    printf("low(%d) high(%d) sum(%d)\n", info2.low, info2.high, info2.sum);

    // ���Է�
    SubArrayInfo info3 = FindmaximumSubarray_Linear(vec, 0, vec.size() - 1);
    printf("low(%d) high(%d) sum(%d)\n", info3.low, info3.high, info3.sum);

    getchar();
    return 0;
}
#endif //EXCEPTION