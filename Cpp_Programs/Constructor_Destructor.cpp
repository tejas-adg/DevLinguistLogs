/*
constructors and destructors
The constructors are called in the same order they are in the code whereas the destructors are called in the opposite order they are called

Constructors - FILO (First In Last Out)
Destructor - LIFO (Last In First Out)

I wrote most of this code in ninth and tenth grade so please excuse the bad coding practices
*/
#include <iostream>
using namespace std;
class A
{
	public:
	A()
	{
		cout << "A is called";
		
	}
	~A()
	{
		cout << "Destructor A";
		
	}
};
class B
{
	public:
	B()
	{
		cout << "B is called";
		
	}
	~B()
	{
		cout << "Destructor B";
		
	}
	
};
class C
{
	public:
	C()
	{
		cout << "C is called";
		
	}
	~C()
	{
		cout << "Destructor C";
		
	}
};
int main()
{
	C obc;
	B obb;
	A oba;
}
