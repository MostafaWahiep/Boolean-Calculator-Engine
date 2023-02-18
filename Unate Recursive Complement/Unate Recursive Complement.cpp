// Unate Recursive Complement.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CubeList.h"

int main()
{
    CubeList::Cube c(3);
    for (int i = 0; i < 3; i++) {
        cout << c.getValue(i + 1) << ' ';
    }
    cout << endl;
    c.setValue_at(-2);
    c.setValue_at(1);
    for (int i = 0; i < 3; i++) {
        cout << c.getValue(i + 1) << ' ';
    }
    cout << endl;


}

