#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string code_filename, line;
    char temp = 32;
    long line_count = 0;
    ifstream fin;

    cout << "Please specify the code file: ";
    cin >> code_filename;

    fin.open(code_filename, ios::in);

    while (!fin.eof())
    {
        temp = fin.get();
        if (temp == 10)
        {
            line_count++;
        } 
    }

    cout << "Total number of lines: " << line_count;

    fin.close();
}