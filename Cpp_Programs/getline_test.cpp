#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

vector<string> InputSplit(string inp)
{
	int fs = 0;
	int sp = inp.find(' ', fs + 1);

	cout << "fs = " << fs << " sp = " << sp << endl;

	cout << "First word = " << inp.substr(0, sp) << " len = " << inp.substr(0, sp).length() << endl;

	//fs = inp.find(' ', fs + 1);
	sp = inp.find(' ', fs + 1);

	cout << "fs = " << fs << " sp = " << sp << endl;

	cout << "Second word = " << inp.substr(fs+1, ((sp - fs) - 1)) << " len = " << inp.substr(fs+1, ((sp - fs) - 1)).length() << endl;

	fs = sp;
	sp = inp.find(' ', fs + 1);

	cout << "fs = " << fs << " sp = " << sp << endl;

	cout << "Second word = " << inp.substr(fs+1, ((sp - fs) - 1)) << " len = " << inp.substr(fs+1, ((sp - fs) - 1)).length() << endl;

	return {};
}

int main()
{
	vector<string> temp = InputSplit("poop piss pp l               tejas     ");

//	for (int i = 0; i < temp.size(); i++)
//	{
//		cout << temp[i] << endl;
//	}
}

/*vector<string> InputSplit(string inp)
{
	vector<string> result;
	string holder;
	for (int i = 0; i < inp.length(); i++)
	{
		if (inp[i] != ' ')
		{
		 holder.push_back(inp[i]);
		 }
	  else if ((inp[i] == ' ') && (holder != ""))
	  {
	    	result.push_back(holder);
			holder.clear();
	  }
	}
	if (holder != "")
	result.push_back(holder);

	return result;
}*/