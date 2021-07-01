#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***** Begin *****/

/// 在串行关卡中分析已经知道, 问题的解为[1, 2, 4, 8, ...]等比数列
/// 该数列通项公式为2^i, 0 <= i < n
/// 创建多个线程, 每个线程负责计算一部分值, 不重叠无数据冲突
/// 所有线程计算完毕后打印

typedef struct {
    long *arr;
    int begin;
    int step;
    int size;
} accumulate_arg_t;

/// 固定设置4个线程
/// 0号线程计算arr[0], arr[4], arr[8]...(如果有的话)
/// 1号线程计算arr[1], arr[5], arr[9]...
/// 以此类推
const int NUM_THREADS = 4;

static void *accumulate(void *arg);

int main() {
    int n = 1;
    scanf("%d", &n);
    long arr[n];
    int step = (n + NUM_THREADS - 1) / NUM_THREADS;

    pthread_t threads[NUM_THREADS];
    accumulate_arg_t args[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        accumulate_arg_t temp = {
            .arr = arr, .begin = i, .step = NUM_THREADS, .size = n};
        args[i] = temp;
        int ret = pthread_create(
            &threads[i], NULL, accumulate,
            (void *)&args[i]);  // 注意此处传地址，不能使用临时变量
        if (ret != 0) {
            fprintf(stderr, "Error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    int i = 0;
    for (; i < n - 1; i++) {
        printf("%ld ", arr[i]);
    }
    printf("%ld\n", arr[i]);
    return 0;
}

static void *accumulate(void *args) {
    accumulate_arg_t *arg = (accumulate_arg_t *)args;
    int i = arg->begin;
    while (i < arg->size) {
        arg->arr[i] = (long)pow(2, i);
        i += arg->step;
    }
}

/***** End *****/
