#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// 变量
long long int data;
int crc;
long long int data_len;
int crc_len;
// 用于储存数据的数组
long long int *data_arr;
long long int *crc_arr;
// 用于储存结果的数组
int *result_arr;
// 用于储存余数的数组
long long int *remainder_arr;

// 用于计算数字长度
long long int get_num_len(long long int num)
{
    int length = 0;
    if (num == 0)
    {
        return 1; // 0的长度为1
    }
    if (num < 0)
    {
        num = -num; // 处理负数
        length++;   // 负号占一个长度
    }
    while (num != 0)
    {
        num /= 10;
        length++;
    }
    return length;
}

// CRC检验函数
void verify_CRC()
{

    // 输入数据
    printf("请输入要发送的数据(如：10011111)：");
    scanf("%lld", &data);
    printf("请输入CRC生成的多项式(如：10011)：");
    scanf("%lld", &crc);

    data_len = get_num_len(data);

    crc_len = get_num_len(crc);
    printf("数据长度为：%lld\n", data_len);
    printf("CRC长度为：%lld\n", crc_len);

    data_arr = (long long int *)malloc(data_len * sizeof(long long int));
    // 用于将需要发送的数据放到数组中
    for (long long int i = data_len - 1; i >= 0; i--)
    {

        data_arr[i] = data % 10;
        data = data / 10;
    }

    // 将crc转换为数组
    crc_arr = (long long int *)malloc(crc_len * sizeof(long long int));
    for (long long int i = crc_len - 1; i >= 0; i--)
    {
        crc_arr[i] = crc % 10;
        crc = crc / 10;
    }

    for (long long int i = 0; i < data_len; i++)
    {
        printf("%d", data_arr[i]);
    }

    // 给result_arr分配内存
    result_arr = (long long int *)malloc((data_len - crc_len + 1) * sizeof(long long int));

    // 给remainder_arr分配内存
    remainder_arr = (long long int *)malloc((crc_len) * sizeof(long long int));

    // 先给raminder_arr赋值为data_arr的前crc_len-1个数据
    for (long long int i = 0; i < crc_len; i++)
    {
        remainder_arr[i] = data_arr[i];
    }

    // 开始计算
    for (long long int i = crc_len - 1; i < data_len; i++)
    {
        if (remainder_arr[0] == 1)
        {
            // 对每一位data数据进行^运算
            for (int j = 0; j < crc_len; j++)
            {
                remainder_arr[j] = remainder_arr[j] ^ crc_arr[j];
            }
            result_arr[i - crc_len + 1] = 1;
        }
        else
        {
            for (int j = 0; j < crc_len; j++)
            {
                remainder_arr[j] = remainder_arr[j] ^ 0;
            }
            result_arr[i - crc_len + 1] = 0;
        }
        // 将余数左移一位
        for (int j = 0; j < crc_len - 1; j++)
        {
            remainder_arr[j] = remainder_arr[j + 1];
        }
        // 将data_arr的下一位赋值给余数的最后一位
        remainder_arr[crc_len - 1] = data_arr[i + 1];
    }

    // for (int i = 0; i < crc_len - 1; i++)
    // {
    //     printf("--%d--\n", remainder_arr[i]);
    //     // res += remainder_arr[i] * 10;
    // }

    // 判断余数是否为0
    long long res = 0;

    // printf("余数为：");
    for (int i = 0; i < crc_len - 1; i++)
    {
        res = remainder_arr[i] * 10;
        // printf("%d", remainder_arr[i]);
    }
    if (res == 0)
    {
        printf("数据完整\n");
    }
    else
    {
        printf("数据不完整\n");
    }
    printf("\n");
}
////

void count_FCS()
{

    // 输入数据
    printf("请输入要发送的数据(如：10011111)：");
    scanf("%lld", &data);
    printf("请输入CRC生成的多项式(如：10011)：");
    scanf("%lld", &crc);

    data_len = get_num_len(data);

    crc_len = get_num_len(crc);
    printf("数据长度为：%d\n", data_len);
    printf("CRC长度为：%d\n", crc_len);

    // 将data_len加上crc-1个长度
    data_len = data_len + crc_len - 1;

    data_arr = (long long int *)malloc(data_len * sizeof(long long int));
    // 用于将需要发送的数据放到数组中,并且将数据后补上crc_len-1个0
    for (long long int i = data_len - 1; i >= 0; i--)
    {
        if (i >= data_len - crc_len + 1)
        {
            data_arr[i] = 0;
        }
        else
        {
            data_arr[i] = data % 10;
            data = data / 10;
        }
    }

    // 将crc转换为数组
    crc_arr = (long long int *)malloc(crc_len * sizeof(long long int));
    for (int i = crc_len - 1; i >= 0; i--)
    {
        crc_arr[i] = crc % 10;
        crc = crc / 10;
    }

    for (long long int i = 0; i < data_len; i++)
    {
        printf("%d", data_arr[i]);
    }

    // 给result_arr分配内存
    result_arr = (long long int *)malloc((data_len - crc_len + 1) * sizeof(long long int));

    // 给remainder_arr分配内存
    remainder_arr = (long long int *)malloc((crc_len) * sizeof(long long int));

    // 先给raminder_arr赋值为data_arr的前crc_len-1个数据
    for (long long int i = 0; i < crc_len; i++)
    {
        remainder_arr[i] = data_arr[i];
    }

    // 开始计算
    for (long long int i = crc_len - 1; i < data_len; i++)
    {
        if (remainder_arr[0] == 1)
        {
            // 对每一位data数据进行^运算
            for (int j = 0; j < crc_len; j++)
            {
                remainder_arr[j] = remainder_arr[j] ^ crc_arr[j];
            }
            result_arr[i - crc_len + 1] = 1;
        }
        else
        {
            for (int j = 0; j < crc_len; j++)
            {
                remainder_arr[j] = remainder_arr[j] ^ 0;
            }
            result_arr[i - crc_len + 1] = 0;
        }
        // 将余数左移一位
        for (long long int j = 0; j < crc_len - 1; j++)
        {
            remainder_arr[j] = remainder_arr[j + 1];
        }
        // 将data_arr的下一位赋值给余数的最后一位
        remainder_arr[crc_len - 1] = data_arr[i + 1];
    }

    // for (long long int i = 0; i < crc_len - 1; i++)
    // {
    //     printf("--%d--\n", remainder_arr[i]);
    //     // res += remainder_arr[i] * 10;
    // }

    // 输出余数
    printf("余数为：");
    for (long long int i = 0; i < crc_len - 1; i++)
    {
        printf("%d", remainder_arr[i]);
    }
    printf("\n");
}

// CRC计算
int main()
{

    while (true)
    {
        int key = 0;
        printf("----------欢迎来到CRC检验程序----------\n");
        printf("----------1、计算FCS--------------\n");
        printf("----------2、CRC检验-------------\n");
        printf("请输入(1or2):");
        scanf("%d", &key);
        switch (key)
        {
        case 1:
            count_FCS();
            break;
        case 2:
            verify_CRC();
            break;
        }
    }

    // // 输入数据
    // printf("请输入要发送的数据：");
    // scanf("%d", &data);
    // printf("请输入CRC生成的多项式：");
    // scanf("%d", &crc);

    // data_len = get_num_len(data);

    // crc_len = get_num_len(crc);
    // printf("数据长度为：%d\n", data_len);
    // printf("CRC长度为：%d\n", crc_len);

    // // 将data_len加上crc-1个长度
    // data_len = data_len + crc_len - 1;

    // // 计算
    // data_arr = (int *)malloc(data_len * sizeof(int));
    // // 用于将需要发送的数据放到数组中,并且将数据后补上crc_len-1个0
    // for (int i = data_len - 1; i >= 0; i--)
    // {
    //     if (i >= data_len - crc_len + 1)
    //     {
    //         data_arr[i] = 0;
    //     }
    //     else
    //     {
    //         data_arr[i] = data % 10;
    //         data = data / 10;
    //     }
    // }

    // // 将crc转换为数组
    // crc_arr = (int *)malloc(crc_len * sizeof(int));
    // for (int i = crc_len - 1; i >= 0; i--)
    // {
    //     crc_arr[i] = crc % 10;
    //     crc = crc / 10;
    // }

    // for (int i = 0; i < data_len; i++)
    // {
    //     printf("%d", data_arr[i]);
    // }

    // // 给result_arr分配内存
    // result_arr = (int *)malloc((data_len - crc_len + 1) * sizeof(int));

    // // 给remainder_arr分配内存
    // remainder_arr = (int *)malloc((crc_len - 1) * sizeof(int));

    // // 先给raminder_arr赋值为data_arr的前crc_len-1个数据
    // for (int i = 0; i < crc_len; i++)
    // {
    //     remainder_arr[i] = data_arr[i];
    // }

    // // 开始计算
    // for (int i = crc_len - 1; i < data_len; i++)
    // {
    //     if (remainder_arr[0] == 1)
    //     {
    //         // 对每一位data数据进行^运算
    //         for (int j = 0; j < crc_len; j++)
    //         {
    //             remainder_arr[j] = remainder_arr[j] ^ crc_arr[j];
    //         }
    //         result_arr[i - crc_len + 1] = 1;
    //     }
    //     else
    //     {
    //         for (int j = 0; j < crc_len; j++)
    //         {
    //             remainder_arr[j] = remainder_arr[j] ^ 0;
    //         }
    //         result_arr[i - crc_len + 1] = 0;
    //     }
    //     // 将余数左移一位
    //     for (int j = 0; j < crc_len - 1; j++)
    //     {
    //         remainder_arr[j] = remainder_arr[j + 1];
    //     }
    //     // 将data_arr的下一位赋值给余数的最后一位
    //     remainder_arr[crc_len - 1] = data_arr[i + 1];
    // }

    // // 输出余数
    // printf("余数为：");
    // for (int i = 0; i < crc_len - 1; i++)
    // {
    //     printf("%d", remainder_arr[i]);
    // }
    return 0;
}
