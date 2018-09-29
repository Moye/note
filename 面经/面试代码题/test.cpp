#include <iostream>
#include <string>

using namespace std;

class A {
};
class B {
    virtual int get() = 0;
};

int main()
{
    string s = "hello";

    cout << sizeof(A) << ' ' << sizeof(B) << endl;

    cout << sizeof(s) << ' ' << sizeof(s[0]) << ' ' << s.size() << endl;

    for (int i = 0; i < 20; ++i) {
        s.push_back('a');
    }
    cout << sizeof(s) << ' ' << sizeof(s[0]) << ' ' << s.size() << endl;

    return 0;
}
