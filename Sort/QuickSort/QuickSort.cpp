#include <iostream>

using namespace std;

void quickSortOverride(int A[], int n);
void quickSortOverride(int A[], int lo, int hi);
void quickSortSwap(int A[], int n);
void quickSortSwap(int A[], int lo, int hi);

const int LEN = 10;

int main(int argc, const char * argv[]) {
    int A[LEN];
    printf("请输入%d个待排序的整数：\n", LEN);
    for (int i = 0; i < LEN; i++)
        cin >> A[i];
//    quickSortOverride(A, LEN);
    quickSortSwap(A, LEN);
    cout << "按升序进行排序后的序列为：" << endl;
    for (int i = 0; i < LEN; i++)
        cout << A[i] << ' ';
    cout << endl;
    return 0;
}

//override
void quickSortOverride(int A[], int n)
{
    //利用重载，简化程序的入口参数
    quickSortOverride(A, 0, n-1);
}

//基于挖坑填数的快速排序
void quickSortOverride(int A[], int lo, int hi)
{
    if (lo < hi)
    {
        int i = lo, j = hi, x = A[lo];
        while (i < j)
        {
            while (i < j && A[j] >= x)      //从后往前找小于基准值x的数
                j--;
            if (i < j)
                A[i++] = A[j];              //填入之前挖好的坑A[i]中，由于A[i]这个坑已经填好，i++
            
            while (i < j && A[i] < x)       //从前往后找大于或等于基准值x的数
                i++;
            if (i < j)
                A[j--] = A[i];              //填入坑A[j]中，由于A[j]这个坑已经填好，j--
        }
        //一次排序退出后，将基准值x填入最后挖的坑A[i]中
        A[i] = x;
        quickSortOverride(A, lo, i-1);
        quickSortOverride(A, j+1, hi);
    }
}

//override
void quickSortSwap(int A[], int n)
{
    //利用重载，简化程序入口参数
    quickSortSwap(A, 0, n-1);
}

void mySwap(int &x1, int &x2)
{
    int tmp = x1;
    x1 = x2;
    x2 = tmp;
}

//基于交换的快速排序
void quickSortSwap(int A[], int lo, int hi)
{
    if (lo < hi)
    {
        int i = lo, j = hi, x = A[lo];
        while (i < j)
        {
            while (i < j && A[j] >= x)          //从后往前查找小于基准值x的数，如果找到记录下对应的下标j
                j--;
            
            while (i < j && A[i] <= x)          //从前往后查找大于基准值x的数，如果找到记录下对应的下标i
                i++;
            if (i < j)
                mySwap(A[i], A[j]);             //交换之前记录下的两个数A[i]和A[j]
        }
        //一次排序退出后，交换基准值A[lo]和A[i]
        mySwap(A[lo], A[i]);
        quickSortSwap(A, lo, i-1);
        quickSortSwap(A, j+1, hi);
    }
}
