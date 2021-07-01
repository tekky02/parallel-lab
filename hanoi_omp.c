#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***** Begin *****/

/// 在串行关卡中分析已经知道, 问题的解为[1, 2, 4, 8, ...]等比数列
/// 该数列通项公式为2^i, 0 <= i < n
/// 可以使用OpenMP的parallel for分别求出各项再打印

int main() {
    int n = 1;
    scanf("%d", &n);
    long arr[n];

#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        arr[i] = (long)pow(2, i);
    }

    int j = 0;
    for (; j < n - 1; j++) {
        printf("%ld ", arr[j]);
    }
    printf("%ld\n", arr[j]);
    return 0;
}
/***** End *****/
