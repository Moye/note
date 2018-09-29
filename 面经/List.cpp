#include "listNode.h" //引入列表节点类

template <typename T> class List { //列表模板类

private:
    int _size;               // 规模
    ListNodePosi(T) header;  //头哨兵
    ListNodePosi(T) trailer; //尾哨兵

protected:
    void init();                                                        //列表创建时的初始化
    int clear();                                                        //清除所有节点
    void copyNodes(ListNodePosi(T), int);                               //复制列表中自位置p起的n项
    void merge(ListNodePosi(T) &, int, List<T>&, ListNodePosi(T), int); //有序列表区间归并
    void mergeSort(ListNodePosi(T) &, int);                             // 从p开始继续的n个节点归并排序
    void selectionSort(ListNodePosi(T), int);                           // 从p开始继续的nge节点选择排序
    void insertionSort(ListNodePosi(T), int);                           // 对从p开始连续的n个节点插入排序

public:
    // 构造函数
    List() { init(); }                     // 默认
    List(List<T> const& L);                //整体复制列表L
    List(List<T> const& L, Rank r, int n); //复制列表L中自第r项起的n顷
    List(ListNodePosi(T) p, int n);        //复制列表中自位置p起的n顷
    // 析构函数
    ~List(); //释放（包含头、尾哨兵在内的）所有节点
    // 只读访问接口
    Rank size() const { return _size; };                    //规模
    bool empty() const { return _size <= 0; };              // 判空
    T& operator[](int r) const;                             //重载[]运算，支持询秩访问(效率低）
    ListNodePosi(T) first() const { return header->succ; }; //首节点位置
    ListNodePosi(T) last() const { return trailer->pred; }; // 末节点位置
};

template <typename T> void List<T>::init()
{                              //列表初始化，在创建列表对象时统一调用
    header = new ListNode<T>;  //创建头哨兵节点
    trailer = new ListNode<T>; //创建尾哨兵节点
    header->succ = trailer;
    header->pred = nullptr;
    trailer->pred = header;
    trailer->succ = nullptr;
    _size() = 0; //记录规模
}

template <typename T> T& List<T>::operator[](int r) const
{
    ListNodePosi(T) p = first();
    while (0 < r--)
        p = p->succ;
    return p->data;
}
