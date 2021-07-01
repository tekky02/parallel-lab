#include <stdio.h>

/***** Begin *****/

/// (1)将前n-1个盘子以C杆为中介移到B杆, 即A ~> C ~> B的解向量S(x)
/// (2)第n个盘子直接移动到C杆, 移动次数为1, 最底下的盘子只需移动一次
/// (3)将B杆上的n-1个盘子以A杆为中介移到C杆, 即B ~> A ~> C, 解向量
/// 同(1)为S(x)
/// (4)最终解[1, 2S(x)*]
/// (5)增加一个盘, 解为[1, 2[1, 2S(x)]*], 等比序列

int main() {
    int n = 1;
    scanf("%d", &n);
    int i = 1;
    long step = 1;
    while (i < n) {
        printf("%ld ", step);
        step *= 2;
        i++;
    }
    printf("%ld\n", step);
    return 0;
}
/***** End *****/