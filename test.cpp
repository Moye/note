#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct cmp2 {
    bool operator()(int a, int b) { return a > b; }
};

void designCmp()
{
    cout << "=========designCmp========" << endl;
    cout << "operator a<b" << endl;
    priority_queue<int, vector<int>, cmp2> q;
    priority_queue<int> small;

    for (int i = 0; i > -10; i--) {
        q.push(i);
        small.push(i);
    }

    while (!q.empty()) {
        cout << q.top() << " ";
        q.pop();
    }
    while (!small.empty()) {
        cout << small.top() << " ";
        small.pop();
    }
    cout << endl;
}

int main()
{
    designCmp();
    return 0;
}
