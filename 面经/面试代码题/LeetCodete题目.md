## 1.链表

[TOC]



###[148.单链表排序(Sort List)](https://leetcode.com/problems/sort-list/description/)

解法1：归并排序。时间复杂度O(nlong(n))

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) 
            return head;
        
        /* 将链表平分为两个链表 */
        ListNode *slow = head, *fast = head, *pre = head;
        while (fast && fast->next) {
            pre = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        pre->next = NULL;
        
        /* 对两个子链表分别调用归并排序 */
        ListNode *partOne = sortList(head);
        ListNode *partTwo = sortList(slow);
        
        /* 对子链进行归并 */
        return merge(partOne, partTwo);
    }
    
private:
    ListNode* merge(ListNode* partOne, ListNode* partTwo) {
        ListNode *first = new ListNode(-1);
        ListNode *cur = first;
        while (partOne && partTwo) {
            if (partOne->val < partTwo->val) {
                cur->next = partOne;
                partOne = partOne->next;
            } else {
                cur->next = partTwo;
                partTwo = partTwo->next;
            }
            cur = cur->next;
        }
        if (partOne) cur->next = partOne;
        if (partTwo) cur->next = partTwo;
        return first->next;
    }

};
```

###[21.合并有序链表](https://leetcode.com/problems/merge-two-sorted-lists/description/)

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* first = new ListNode(-1);
        ListNode* cur = first;
        while(l1 && l2){
            if(l1->val < l2->val){
                cur->next = l1;
                l1 = l1->next;
            }else{
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        
        if(l1) cur->next = l1;
        if(l2) cur->next = l2;
        return first->next;
    }
};
```

###[23.K个有序链表合并](https://leetcode.com/problems/merge-k-sorted-lists/description/)

使用堆排序，可以使用优先级队列来实现一个小顶堆。

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

struct cmp
{
    bool operator () (ListNode *a, ListNode *b)
    {
        return a->val > b->val;
    }
};


class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // 使用优先级队列实现一个小顶堆。
        // 注：优先级队列一般是大顶堆，需要重载一下cmp的()的运算符
        // 每次top()，可以取到最小的元素，放入归并后的链表即可，然后再讲top()节点的下一个结点放入优先级队列中
        // 优先级队列的插入复杂度为O(logn)。取出的复杂度为O(1)
        
        priority_queue<ListNode*, vector<ListNode*>, cmp> que;
        for(int i = 0; i < lists.size(); ++i){
            if(lists[i])
                que.push(lists[i]);
        }
        
        ListNode *head = NULL;
        ListNode *pre = NULL;
        ListNode *temp = NULL;
        
        while(!que.empty())
        {
            temp = que.top();
            que.pop();
            if(!pre) 
                head = temp;
            else 
                pre->next = temp; // 将top()元素插入归并链表中
            pre = temp; // 保存链表的末节点位置
            if(temp->next) 
                que.push(temp->next); // 将top()元素的下一个结点放入优先级队列中
        }
        return head;
    }
};
```

###92.反转链表II

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode dummy(-1); // 定义一个假的的节点
        dummy.next = head; // dummy成为新的头结点，故head节点也可以有前驱指针，所以和其他节点一样了。
        
        ListNode* prev = &dummy;
        // prev指针指向第m个节点的前驱节点
        for(int i = 0; i < m-1; ++i){
            prev = prev->next;
        }
        
        // head2新的头节点指针指向这个前驱节点，作为头节点，利用头插法建立链表
        ListNode* const head2 = prev;
        // prev指向第m个节点
        prev = head2->next;
        // cur指向prev的下一个节点
        ListNode* curr = prev->next;
        
        for(int i = m+1; i <= n; ++i){
            // 将第i个节点(m<i<=n)依次使用头插法插入到head2为头节点的链表中
            prev->next = curr->next; // 记住第i+1个节点(作为prev的后继)
            curr->next = head2->next; // 1.curr指向的节点头插到head2节点之后的节点前面
            head2->next = curr; // 2.head2的后继更改为cur
            curr = prev->next; // curr指向下一个结点
        }
        
        return dummy.next;
    }
};
```



##2.动态规划

###[264.丑数II](https://leetcode-cn.com/problems/ugly-number-ii/description/)

丑数是因子只有2，3，5组合的数。1是特殊的丑数。

观察规律，发现**一个较大丑数都等于一个较小的丑数*2(或3或5)**得到的。

故用idx数组保存较小丑数的下标，用uglys数组保存当前找到的丑数。

例如uglys[idx[2]]*2如果是当前最小的丑数时候，则下标idx[2]自增。保存当前丑数。

```c++
#include <algorithm> 
class Solution {
public:
    int nthUglyNumber(int n) {
        int idx[3] = {0, 0, 0};
        int uglys[n];
        uglys[0] = 1;
        for(int i = 1; i < n; ++i){
            int a = uglys[idx[0]] * 2;
            int b = uglys[idx[1]] * 3;
            int c = uglys[idx[2]] * 5;
            int min = std::min(a, std::min(b, c));
            if(min == a) idx[0]++;
            if(min == b) idx[1]++;
            if(min == c) idx[2]++;
            uglys[i] = min;
        }
        return uglys[n-1];
    }
};
```

###[32.最长有效括号](https://leetcode.com/problems/longest-valid-parentheses/description/)

```c++
class Solution {
public:
    int longestValidParentheses(string s) {
        int length = s.size();
        stack<int> st;
        vector<int> lens(length);
        
        // 遍历一遍字符串，求得以第i个字符为止的最长有效括号字符串长度
        // 保存在数组lens中
        for(int i = 0; i < length; ++i){
            if(s[i] == '('){
                st.push(i);
                lens[i] = 0;
            }else if(s[i] == ')'){
                if(st.empty()){
                    lens[i] = 0;
                }else{
                    if(st.top() - 1 >= 0){
                        lens[i] = 2 + lens[i-1] + lens[st.top()-1];
                    }else{
                        lens[i] = 2 + lens[i-1];
                    }
                    st.pop();
                }
            }
        }
        
        // 遍历一遍lens数组，求得含有最长有效括号的子串长度
        int maxLen = 0;
        for(int i = 0; i < length; ++i){
           maxLen = std::max(maxLen, lens[i]);
        }
        return maxLen;
    }
};
```

###206.链表反转(Reverse Linked List)

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head == nullptr)
            return nullptr;
        ListNode dummy(-1);
        dummy.next = head;
        
        ListNode* head2 = &dummy;
        ListNode* prev = head2->next;
        
        ListNode* curr = prev->next;
        
        while(curr != nullptr){
            prev->next = curr->next;
            curr->next = head2->next;
            head2->next = curr;
            curr = prev->next;
        }
        
        return dummy.next;
    }
};
```



###63.不同路径II

```c++
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        // MxN grid
        int M = obstacleGrid.size();
        int N = obstacleGrid[0].size();
        vector<vector<int>> uniquePaths(M, vector<int>(N,0));
        for(int i = 0; i < M; ++i){
            if(obstacleGrid[i][0] == 0)
                uniquePaths[i][0] = 1;
            else
                break;
        }
        // 计算到达第一行的其他格子的不同路径个数
        for(int j = 0; j < N; ++j){
            if(obstacleGrid[0][j] == 0)
                uniquePaths[0][j] = 1;
            else
                break;
        }
        
        // 计算到达第一列的其他格子的不同路径个数
        
        for(int i = 1; i < M; ++i){
            for(int j = 1; j < N; ++j){
                if(obstacleGrid[i][j] == 0)
                    uniquePaths[i][j] = uniquePaths[i-1][j] + uniquePaths[i][j-1];
                else
                    uniquePaths[i][j] = 0;
            }
        }
        return uniquePaths[M-1][N-1];
    }
};
```

###[234.回文链表](https://leetcode.com/problems/palindrome-linked-list/description/)

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    
    ListNode* reverse(ListNode* head){
        ListNode* prev = nullptr;
        while(head){
            ListNode* curr = head->next;
            head->next = prev;
            prev = head;
            head = curr;
        }
        return prev;
    }
    
    bool isPalindrome(ListNode* head) {
        if(!head || !head->next)
            return true;
        // 找到链表的中间节点，然后反转后半部分链表，与前半部分比较即可
        ListNode* fast = head;
        ListNode* slow = head;
        
        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // 如果链表有奇数个节点
        if(fast){
            slow = slow->next;
        }
        
        slow = reverse(slow);
        
        while(slow){
            if(head->val != slow->val)
                return false;
            head = head->next;
            slow = slow->next;
        }
        return true;
    }
};
```



解法一：动态规划

用一个MxN的二维数组，来存储**机器人到达对应棋盘上的格子的不同路径条数**。

```c++
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        // MxN grid
        int M = obstacleGrid.size();
        int N = obstacleGrid[0].size();
        vector<vector<int>> uniquePaths(M, vector<int>(N,0));
        for(int i = 0; i < M; ++i){
            if(obstacleGrid[i][0] == 0)
                uniquePaths[i][0] = 1;
            else
                break;
        }
        // 计算到达第一行的其他格子的不同路径个数
        for(int j = 0; j < N; ++j){
            if(obstacleGrid[0][j] == 0)
                uniquePaths[0][j] = 1;
            else
                break;
        }
        
        // 计算到达第一列的其他格子的不同路径个数
        
        for(int i = 1; i < M; ++i){
            for(int j = 1; j < N; ++j){
                if(obstacleGrid[i][j] == 0)
                    uniquePaths[i][j] = uniquePaths[i-1][j] + uniquePaths[i][j-1];
                else
                    uniquePaths[i][j] = 0;
            }
        }
        return uniquePaths[M-1][N-1];
    }
};
```

解法二：递归

当棋盘过大时候，递归深度太大就会出现超时。

```c++
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        // MxN grid
        int M = obstacleGrid.size();
        int N = obstacleGrid[0].size();
        //std::cout << "M: " << M << "\n" << "N: " << N << endl;
        return getUniquePaths(obstacleGrid, M-1, N-1);
    }
    
    int getUniquePaths(vector<vector<int>>& obstacleGrid, int row, int column){
        
        //std::cout << "row: " << row << "\n" << "column: " << column << endl;
        if(row >= 0 && column >= 0 &&obstacleGrid[row][column] == 1)
            return 0;

        if(row == 0 && column == 0 && obstacleGrid[row][column] == 0)
            return 1;
        else if(row < 0 || column < 0){
            return 0;
        }
        
        
        return getUniquePaths(obstacleGrid, row-1, column) + getUniquePaths(obstacleGrid, row, column-1);
    }
    
};
```

###[72.编辑距离](https://leetcode.com/problems/edit-distance/description/)

[参考链接](https://blog.csdn.net/feliciafay/article/details/17502919)

```c++
class Solution {
public:
    int minDistance(string word1, string word2) {
        // 利用线性规划，用二维数组dp[i][j]保存，长度为i的word1子串要变成长度为j的word2子串需要的编辑操作。
        // 动态规划初始化 dp[i][0] = i; dp[0][j] = j
        // 动态转义方程：
        // dp[i][j] = min (
        //   删除操作+1           dp[i][j-1] + 1,
        //   插入操作+1           dp[i-1][j] + 1,
        //   替换操作+1           dp[i-1][i-1](if(word1[i] == word[2])) or dp[i-1][j-1]+2(if(word1[i] != word1[j]))
        //                  )
        vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
        // 初始化左边界
        for(int i = 1; i <= word1.size(); ++i)
            dp[i][0] = i;
        
        // 初始化下边界
        for(int i = 1; i <= word2.size(); ++i)
            dp[0][i] = i;
        
        for(int i = 1; i <= word1.size(); ++i)
        {
            for(int j = 1; j <= word2.size(); ++j){
                if(word1[i-1] == word2[j-1]){
                    dp[i][j] = std::min(dp[i-1][j] + 1, std::min(dp[i][j-1] + 1, dp[i-1][j-1]));
                }else{
                    dp[i][j] = std::min(dp[i-1][j] + 1, std::min(dp[i][j-1] + 1, dp[i-1][j-1] + 1));
                }
            }
        }
        return dp[word1.size()][word2.size()];
    }
};
```

###87.Scramble String（扰乱字符串）

```c++
class Solution {
public:
    bool isScramble(string s1, string s2) {
        
        if(s1.size() != s2.size())
            return false;
        
        if(s1 == s2)
            return true;
        int n = s1.size();
        
        // 用动态规划算法，用dp[i][j][len]来保存状态
        // i是s1的起始字符，j是s2的起始字符，而n是当前
        // 的字符串长度，res[i][j][len]表示的是以i和j
        // 分别为s1和s2起点的长度为len的字符串是不是互
        // 为scramble
        // 计算res[i][j][len]的值分两种情况
        // |---k---|--len-k------|
        // |_|_|_|_|_|_|_|_|_|_|_|
        // i
        // j
        // 只要一下两者情况之一为真，则res[i][j][len]为真：
        // 1: dp[i][j][k] && dp[i+k][j+k][len-k]
        // 2: dp[i][j+len-k][k] && dp[i+k][j][len-k]
        vector<vector<vector<bool> >> dp(n, vector<vector<bool>>(n, vector<bool>(n + 1, false)));
        
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                dp[i][j][1] = s1[i] == s2[j];
        
        for(int len = 2; len <= n; ++len){
            for(int i = 0; i <= n - len; ++i){
                for(int j = 0; j <= n - len; ++j){
                    for(int k = 1; k < len; ++k){
                        if((dp[i][j][k] && dp[i+k][j+k][len-k]) || (dp[i][j+len-k][k] && dp[i+k][j][len-k]) )
                            dp[i][j][len] = true;
                    }
                }
            }
        }
        return dp[0][0][n];
    }
};
```

[参考链接](http://www.cnblogs.com/grandyang/p/4318500.html)

