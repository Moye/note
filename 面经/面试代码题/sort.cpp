#include <iostream>
#include <vector>

using namespace std;

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void insertSort(vector<int>& array)
{
    int len = array.size();
    if (len <= 1)
        return;
    cout << "len: " << len << endl;
    for (int i = 1; i < len; ++i) {
        int temp = array[i];
        int j;
        for (j = i - 1; j >= 0; --j) {
            if (array[j] > temp)
                array[j + 1] = array[j];
            else {
                break;
            }
        }
        array[j + 1] = temp;
    }
}

void bubbleSort(vector<int>& array)
{
    int len = array.size();
    if (len <= 1)
        return;

    for (int i = len - 1; i > 0; --i) {
        for (int j = 0; j < i; ++j) {
            if (array[j] > array[j + 1])
                swap(array[j], array[j + 1]);
        }
    }
}

void shellSort(vector<int>& array)
{
    int len = array.size();
    if (len <= 1)
        return;

    int i, j;
    // 取数组长度的一半初始化希尔增量
    for (int increment = len / 2; increment > 0; increment /= 2) {
        for (i = increment; i < len; ++i) {
            int temp = array[i];

            for (j = i - increment; j >= 0; j -= increment) {
                if (array[j] > temp)
                    array[j + increment] = array[j];
                else
                    break;
            }

            array[j + increment] = temp;
        }
    }
}

void merge(vector<int>& array, vector<int>& L, vector<int>& R)
{
    int i, j, k;

    i = 0;
    j = 0;
    k = 0;

    while (i < L.size() && j < R.size()) {
        if (L[i] < R[j])
            array[k++] = L[i++];
        else
            array[k++] = R[j++];
    }

    while (i < L.size())
        array[k++] = L[i++];

    while (j < R.size())
        array[k++] = R[j++];
}

void mergeSort(vector<int>& array)
{
    int mid, i;
    int len = array.size();
    vector<int> L, R;
    if (len < 2)
        return;
    mid = len / 2;
    for (i = 0; i < mid; ++i)
        L.push_back(array[i]);

    for (i = mid; i < len; ++i)
        R.push_back(array[i]);

    mergeSort(L);
    mergeSort(R);
    merge(array, L, R);
}

void partition(vector<int>& array, int begin, int end)
{
    if (begin >= end)
        return;

    // 取最左边、最右边和中间三个位置数的中位数
    // 作为基准值，并将基准值调到最右边。
    int center = (begin + end) / 2;
    if (array[begin] > array[center])
        swap(array[begin], array[center]);

    if (array[begin] > array[end])
        swap(array[begin], array[end]);

    if (array[center] < array[end])
        swap(array[center], array[end]);

    int left = begin;
    int right = end - 1;

    while (left < right) {
        while (array[left] < array[end])
            left++;
        while (array[right] > array[end])
            right--;

        if (left < right) {
            swap(array[left], array[right]);
        } else
            break;
    }

    // 将基准值放在排好序后它所处的位置
    if (array[left] >= array[end])
        swap(array[left], array[end]);
    else
        left++;

    partition(array, begin, left - 1);
    partition(array, left + 1, end);
}

void quickSort(vector<int>& array)
{
    int len = array.size();
    if (len < 2)
        return;

    int begin = 0;
    int end = len - 1;
    partition(array, begin, end);
}

/*
 * 建堆函数，传入参数：
 * @array: 数组
 * @root:  根节点位置
 * @len:   数组长度
 */
void heapBuild(vector<int>& array, int root, int len)
{
    int lchild = root * 2 + 1; // 根节点的左子结点下标
    if (lchild < len)          // 左子结点下标不能超出数组的长度
    {
        int flag = lchild; // flag保存左右结点中最大值的下标
        int rchild = lchild + 1;
        if (rchild < len) {
            if (array[rchild] > array[flag]) { // 求出左右结点的最大值
                flag = rchild;
            }
        }
        if (array[root] < array[flag]) { // 交换父结点和比父结点大的最大子结点
            swap(array[root], array[flag]);
            // 从此次最大子结点的那个位置开始递归建堆
            heapBuild(array, flag, len);
        }
    }
}

void heapSort(vector<int>& array)
{
    int len = array.size();
    for (int i = len / 2 - 1; i >= 0; --i) {
        // 从最后一个非叶子结点的父结点开始建堆
        heapBuild(array, i, len);
    }

    for (int j = len - 1; j > 0; --j) {
        swap(array[0], array[j]); // 交换首尾元素，将最大值交换到数组的最后位置保存
        heapBuild(array, 0, j);   // 去除最后位置的元素重新建堆，此处j表示数组的长度，最后一个位置下标变为len-2
    }
}

int main()
{
    vector<int> vec = { 3, 2, 9, 5, 7, 4, 1, 6, 0, 8 };
    // 1.插入排序（插入排序是希尔增量为1的特殊希尔排序）
    // insertSort(vec);
    // 2.冒泡排序
    // bubbleSort(vec);
    // 3.希尔排序
    // shellSort(vec);
    // 4.归并排序
    // mergeSort(vec);
    // 5.快速排序
    // quickSort(vec);
    // 6.堆排序
    heapSort(vec);

    for (int i = 0; i < vec.size(); ++i) {
        if (i != vec.size() - 1)
            cout << vec[i] << ' ';
        else
            cout << vec[i] << endl;
    }
    return 0;
}
