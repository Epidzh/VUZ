//
//  main.cpp
//  cpp_lab6
//
//  Created by Сергей Петров on 14/12/2018.
//  Copyright © 2018 SergioPetrovx. All rights reserved.
//

#include <iostream>
#include <string.h>

using namespace std;

int main(int argc, const char * argv[])
{
    
    char buf1[] = "123123", buf2[] = "123123aszzzz";
    int buf3[] = {1, 2, 3, 4};
    setZero(buf1, buf2, buf3);
    return 0;
}
