//
//  main.cpp
//  과제3
//
//  Created by Jeon Charn on 2021/03/23.
//

#include <iostream>
#include <string.h>
#include "String.hpp"
using namespace std;

int main()
{
    Str a("I'm a girl");
    cout<<a.contents();
    a="I'm a boy\n";
    cout<<a.contents();
    cout<<a.compare("I'm a a")<<endl;
   
    return 0;
}
