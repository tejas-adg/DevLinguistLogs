// treap_bst.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "treap_aaryan.h"

int main()
{
    Treap<int, int> t;
    bool temp = false;

    std::cout << "empty = " << t.empty() << std::endl;;

    for (int i = 1; i < 251; i++)
    {
        t.insert(i, 10 * i);
    }

    std::cout << "empty = (expecting false) = " << t.empty() << std::endl;;

    for (int i = 1; i < 251; i++)
    {
        temp = false;
        if (t.search(i, temp) != (i * 10))
        {
            std::cout << "searching for " << i << " did not result in " << 12 * i << std::endl;
        }
        if (!(temp))
        {
            std::cout << "search for " << i << " failed" << std::endl;
        }
    }

    for (int i = 1; i < 251; i++)
    {
        t.remove(i);
    }

    std::cout << "empty (expecting true) = " << t.empty() << std::endl;
    /*Treap<int, int> t;

    t.insert(10, 100);
    t.insert(20, 200);
    t.insert(30, 300);
    t.insert(60, 600);
    t.insert(50, 500);
    t.insert(40, 400);
    t.insert(70, 700);
    bool temp = false;
    int ret = t.search(40, temp);
    std::cout << "the height is = " << t.height() << std::endl;
    std::cout << "is empty = " << t.empty() << std::endl;
    std::cout << "ret = " << ret << " temp = " << temp << std::endl;

    temp = false;
    ret = t.search(10, temp);
    std::cout << "ret = " << ret << " temp = " << temp << std::endl;

    t.remove(10);
    t.remove(40);

    temp = false;
    ret = t.search(20, temp);
    std::cout << "ret = " << ret << " temp = " << temp << std::endl;

    temp = false;
    ret = t.search(30, temp);
    std::cout << "ret = " << ret << " temp = " << temp << std::endl;

    temp = false;
    ret = t.search(50, temp);
    std::cout << "ret = " << ret << " temp = " << temp << std::endl;

    t.remove(20);
    t.remove(30);
    t.remove(50);

    temp = false;
    ret = t.search(60, temp);
    std::cout << "ret = " << ret << " temp = " << temp << std::endl;

    temp = false;
    ret = t.search(70, temp);
    std::cout << "ret = " << ret << " temp = " << temp << std::endl;

    t.remove(60);
    t.remove(70);

    std::cout << "is empty = " << t.empty() << std::endl;*/

    /*t.remove(10);
    /*t.remove(20);
    t.remove(30);
    t.remove(40);
    t.remove(50);
    t.remove(60);
    temp = true;
    ret = t.search(70, temp);
    std::cout << "ret = " << ret << " temp = " << temp << std::endl;
    std::cout << "is empty = " << t.empty() << std::endl;
    t.remove(70);
    std::cout << "is empty = " << t.empty() << std::endl;

    t.insert(10, 220);

    temp = false;
    ret = t.search(10, temp);
    std::cout << "ret = " << ret << " temp = " << temp << std::endl;

    std::cout << "the height is = " << t.height() << std::endl;*/
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
