//
//  String.cpp
//  과제3
//
//  Created by Jeon Charn on 2021/03/23.
//

#include <iostream>
#include <string.h>
#include "String.hpp"

Str::Str(char* neyong):string(neyong)
{
    str = neyong;
    len = (int)string::length();
}

Str::Str(int leng) // 어디에 사용하는 생성자인가?
{
    len = leng;
}

Str::~Str()
{
    
}

int Str::length()
{
    return len;
}

char* Str::contents()
{
    return str;
}

int Str::compare(class Str& a)
{
    return (strcmp(str, a.contents()));
}

int Str::compare(char* a)
{
    return (strcmp(str, a));
}

void Str::operator=(char *a)
{
    str = a;
    string cp = a;
    len = (int)(cp.length());
}

void Str::operator=(class Str& a)
{
    len = a.length();
    str = a.contents();
}
