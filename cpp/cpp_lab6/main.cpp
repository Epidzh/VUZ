#include <iostream>
using namespace std;

class myString
{
private:
    const char* str;
    int len;
public:
    
    myString(char *s)
    {
        str = s;
        while (strcmp(s++, "\0"))
            len++;
    }
    
    const char* begin() { return str; }
    
    const char* end() { return str+len; }
};

int main() {
    myString str("Some Interesting String");
    for(auto i : str){
        cout<<i;
    }
    cout<<endl;
    return 0;
}
