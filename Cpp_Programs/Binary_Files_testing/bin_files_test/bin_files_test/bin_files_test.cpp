// bin_files_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct collection
{
	int p;
	string desc;
	bool done;
};

int main()
{
	vector<collection> tasks;

	tasks.push_back(collection{ 1, "my task", false });
	tasks.push_back(collection{ 2, "my task 2", true });
	tasks.push_back(collection{ 3, "my task 3", false });

	/*ofstream fout("sample.txt", ios::out | ios::binary);
	fout.write((char*)&tasks, sizeof(tasks));
	fout.close();

	cout << "writing done\n";*/

	ifstream fin("sample.txt", ios::in | ios::binary);
	fin.read((char*)&tasks, sizeof(tasks));
	fin.close();

	cout << "reading done, size = " << tasks.size() << endl;

	for (unsigned int i = 0; i < tasks.size(); i++)
		cout << tasks.at(i).p << ", " << tasks.at(i).desc << ", " << tasks.at(i).done << endl;
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
