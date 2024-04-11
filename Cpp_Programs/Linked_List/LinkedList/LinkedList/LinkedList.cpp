#include "Single_Linked_List.h"
#include "Doubly_Linked_List.h"

using namespace std;

int main()
{
	Doubly_Linked_List<char> d_ll;

	d_ll.addItem(Double_Link_Node<char>::create_node('t'));

	d_ll.addItem(Double_Link_Node<char>::create_node('e'), 1);

	d_ll.addItem(Double_Link_Node<char>::create_node('j'), -1);

	d_ll.addItem(Double_Link_Node<char>::create_node('a'), -1);

	d_ll.addItem(Double_Link_Node<char>::create_node('s'), -1);

	d_ll.addItem(Double_Link_Node<char>::create_node('M'), 5);

	d_ll.addItem(Double_Link_Node<char>::create_node('A'), 5);

	d_ll.Print_List(); cout << endl;

	/*d_ll.addItem(Double_Link_Node<char>::create_node('Z'), 4);

	d_ll.Print_List(); cout << endl;*/

	/*delete d_ll.removeItemByPosition();
	delete d_ll.removeItemByPosition(-1);
	delete d_ll.removeItemByPosition(3);
	delete d_ll.removeItemByPosition(-2);
	delete d_ll.removeItemByPosition(2);
	delete d_ll.removeItemByPosition(1);
	delete d_ll.removeItemByPosition(0);

	d_ll.Print_List(); cout << endl;*/

	char temp = 's';
	int pos = 0;
	Double_Link_Node<char>* ret_node = d_ll.searchByData(&temp, &pos);

	cout << "Found '" << temp << "' at " << pos << endl;

	return 0;
}

//char main()
//{
//	Single_Linked_List<char> s_ll;
//
//	s_ll.addItem(Single_Link_Node<char>::createNode('t'));
//
//	s_ll.addItem(Single_Link_Node<char>::createNode('e'), 1);
//
//	s_ll.addItem(Single_Link_Node<char>::createNode('j'), 2);
//
//	s_ll.addItem(Single_Link_Node<char>::createNode('a'), 3);
//
//	s_ll.addItem(Single_Link_Node<char>::createNode('s'), 4);
//
//	s_ll.addItem(Single_Link_Node<char>::createNode('Z'), 3);
//	
//	s_ll.Print_List(); cout << endl;
//
//	delete s_ll.removeItemByPosition(1);
//
//	s_ll.Print_List(); cout << endl;
//
//	s_ll.Reverse_List();
//
//	s_ll.Print_List(); cout << endl;
//
//	s_ll.Reverse_List();
//
//	s_ll.Print_List(); cout << endl;
//
//	delete s_ll.removeItemByData('a');
//	
//	s_ll.Print_List(); cout << endl;
//
//	delete s_ll.removeItemByData('t');
//
//	s_ll.Print_List(); cout << endl;
//
//	delete s_ll.removeItemByPosition(0);
//	delete s_ll.removeItemByPosition(-1);
//	delete s_ll.removeItemByPosition(0);
//
//	s_ll.Print_List(); cout << endl;
//
//	s_ll.addItem(Single_Link_Node<char>::createNode('t'));
//
//	s_ll.addItem(Single_Link_Node<char>::createNode('e'), 1);
//
//	s_ll.addItem(Single_Link_Node<char>::createNode('j'), 2);
//
//	s_ll.addItem(Single_Link_Node<char>::createNode('a'), 3);
//
//	s_ll.addItem(Single_Link_Node<char>::createNode('s'), 4);
//
//	s_ll.addItem(Single_Link_Node<char>::createNode('a'), -1);
//
//	s_ll.addItem(Single_Link_Node<char>::createNode('m'), -1);
//
//	s_ll.Print_List(); cout << endl;
//
//	return 0;
//}