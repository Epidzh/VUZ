#include <iostream>
#include <string.h>
#include <string>

using namespace std;

class Hello
{
private:
    char *name;
public:
    Hello (const char *str)
    {
        //cout << "Hello, " << str << "!" << endl;
        name = new char[strlen(str)+1];
        strcpy(name, str);
        
    }
    
    ~Hello () 
    {
       delete name; 
    }
    
    template <typename T> 
    void greeting(T str)
    {
        cout << "Hello, " << str << "!" << endl;
    }
    
};

void operator<<(Hello obj, int a)
{
    obj.greeting(a);
    
}

int main(void)
{
    string name = "Denis";
    Hello obj("Yegor");
    obj << 1;
    obj.greeting<const char*>("Harry");
    obj.greeting(1);
    return 0;
}