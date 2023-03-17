#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// ����
long long int data;
int crc;
long long int data_len;
int crc_len;
// ���ڴ������ݵ�����
long long int *data_arr;
long long int *crc_arr;
// ���ڴ�����������
int *result_arr;
// ���ڴ�������������
long long int *remainder_arr;

// ���ڼ������ֳ���
long long int get_num_len(long long int num)
{
    int length = 0;
    if (num == 0)
    {
        return 1; // 0�ĳ���Ϊ1
    }
    if (num < 0)
    {
        num = -num; // ������
        length++;   // ����ռһ������
    }
    while (num != 0)
    {
        num /= 10;
        length++;
    }
    return length;
}

// CRC���麯��
void verify_CRC()
{

    // ��������
    printf("������Ҫ���͵�����(�磺10011111)��");
    scanf("%lld", &data);
    printf("������CRC���ɵĶ���ʽ(�磺10011)��");
    scanf("%lld", &crc);

    data_len = get_num_len(data);

    crc_len = get_num_len(crc);
    printf("���ݳ���Ϊ��%lld\n", data_len);
    printf("CRC����Ϊ��%lld\n", crc_len);

    data_arr = (long long int *)malloc(data_len * sizeof(long long int));
    // ���ڽ���Ҫ���͵����ݷŵ�������
    for (long long int i = data_len - 1; i >= 0; i--)
    {

        data_arr[i] = data % 10;
        data = data / 10;
    }

    // ��crcת��Ϊ����
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

    // ��result_arr�����ڴ�
    result_arr = (long long int *)malloc((data_len - crc_len + 1) * sizeof(long long int));

    // ��remainder_arr�����ڴ�
    remainder_arr = (long long int *)malloc((crc_len) * sizeof(long long int));

    // �ȸ�raminder_arr��ֵΪdata_arr��ǰcrc_len-1������
    for (long long int i = 0; i < crc_len; i++)
    {
        remainder_arr[i] = data_arr[i];
    }

    // ��ʼ����
    for (long long int i = crc_len - 1; i < data_len; i++)
    {
        if (remainder_arr[0] == 1)
        {
            // ��ÿһλdata���ݽ���^����
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
        // ����������һλ
        for (int j = 0; j < crc_len - 1; j++)
        {
            remainder_arr[j] = remainder_arr[j + 1];
        }
        // ��data_arr����һλ��ֵ�����������һλ
        remainder_arr[crc_len - 1] = data_arr[i + 1];
    }

    // for (int i = 0; i < crc_len - 1; i++)
    // {
    //     printf("--%d--\n", remainder_arr[i]);
    //     // res += remainder_arr[i] * 10;
    // }

    // �ж������Ƿ�Ϊ0
    long long res = 0;

    // printf("����Ϊ��");
    for (int i = 0; i < crc_len - 1; i++)
    {
        res = remainder_arr[i] * 10;
        // printf("%d", remainder_arr[i]);
    }
    if (res == 0)
    {
        printf("��������\n");
    }
    else
    {
        printf("���ݲ�����\n");
    }
    printf("\n");
}
////

void count_FCS()
{

    // ��������
    printf("������Ҫ���͵�����(�磺10011111)��");
    scanf("%lld", &data);
    printf("������CRC���ɵĶ���ʽ(�磺10011)��");
    scanf("%lld", &crc);

    data_len = get_num_len(data);

    crc_len = get_num_len(crc);
    printf("���ݳ���Ϊ��%d\n", data_len);
    printf("CRC����Ϊ��%d\n", crc_len);

    // ��data_len����crc-1������
    data_len = data_len + crc_len - 1;

    data_arr = (long long int *)malloc(data_len * sizeof(long long int));
    // ���ڽ���Ҫ���͵����ݷŵ�������,���ҽ����ݺ���crc_len-1��0
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

    // ��crcת��Ϊ����
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

    // ��result_arr�����ڴ�
    result_arr = (long long int *)malloc((data_len - crc_len + 1) * sizeof(long long int));

    // ��remainder_arr�����ڴ�
    remainder_arr = (long long int *)malloc((crc_len) * sizeof(long long int));

    // �ȸ�raminder_arr��ֵΪdata_arr��ǰcrc_len-1������
    for (long long int i = 0; i < crc_len; i++)
    {
        remainder_arr[i] = data_arr[i];
    }

    // ��ʼ����
    for (long long int i = crc_len - 1; i < data_len; i++)
    {
        if (remainder_arr[0] == 1)
        {
            // ��ÿһλdata���ݽ���^����
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
        // ����������һλ
        for (long long int j = 0; j < crc_len - 1; j++)
        {
            remainder_arr[j] = remainder_arr[j + 1];
        }
        // ��data_arr����һλ��ֵ�����������һλ
        remainder_arr[crc_len - 1] = data_arr[i + 1];
    }

    // for (long long int i = 0; i < crc_len - 1; i++)
    // {
    //     printf("--%d--\n", remainder_arr[i]);
    //     // res += remainder_arr[i] * 10;
    // }

    // �������
    printf("����Ϊ��");
    for (long long int i = 0; i < crc_len - 1; i++)
    {
        printf("%d", remainder_arr[i]);
    }
    printf("\n");
}

// CRC����
int main()
{

    while (true)
    {
        int key = 0;
        printf("----------��ӭ����CRC�������----------\n");
        printf("----------1������FCS--------------\n");
        printf("----------2��CRC����-------------\n");
        printf("������(1or2):");
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

    // // ��������
    // printf("������Ҫ���͵����ݣ�");
    // scanf("%d", &data);
    // printf("������CRC���ɵĶ���ʽ��");
    // scanf("%d", &crc);

    // data_len = get_num_len(data);

    // crc_len = get_num_len(crc);
    // printf("���ݳ���Ϊ��%d\n", data_len);
    // printf("CRC����Ϊ��%d\n", crc_len);

    // // ��data_len����crc-1������
    // data_len = data_len + crc_len - 1;

    // // ����
    // data_arr = (int *)malloc(data_len * sizeof(int));
    // // ���ڽ���Ҫ���͵����ݷŵ�������,���ҽ����ݺ���crc_len-1��0
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

    // // ��crcת��Ϊ����
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

    // // ��result_arr�����ڴ�
    // result_arr = (int *)malloc((data_len - crc_len + 1) * sizeof(int));

    // // ��remainder_arr�����ڴ�
    // remainder_arr = (int *)malloc((crc_len - 1) * sizeof(int));

    // // �ȸ�raminder_arr��ֵΪdata_arr��ǰcrc_len-1������
    // for (int i = 0; i < crc_len; i++)
    // {
    //     remainder_arr[i] = data_arr[i];
    // }

    // // ��ʼ����
    // for (int i = crc_len - 1; i < data_len; i++)
    // {
    //     if (remainder_arr[0] == 1)
    //     {
    //         // ��ÿһλdata���ݽ���^����
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
    //     // ����������һλ
    //     for (int j = 0; j < crc_len - 1; j++)
    //     {
    //         remainder_arr[j] = remainder_arr[j + 1];
    //     }
    //     // ��data_arr����һλ��ֵ�����������һλ
    //     remainder_arr[crc_len - 1] = data_arr[i + 1];
    // }

    // // �������
    // printf("����Ϊ��");
    // for (int i = 0; i < crc_len - 1; i++)
    // {
    //     printf("%d", remainder_arr[i]);
    // }
    return 0;
}
