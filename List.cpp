#include <iostream>
#include <vector>
#include <list>
using namespace std;

void print(list<int >lst)
{list<int>::iterator i;
	for (i = lst.begin(); i != lst.end(); i++)
	{
		cout << *i << " ";
	}
	cout << endl;
}
int main()
{	
	list<int> lst;//kato vektora trqbva da oboznachim kakuv tip e
	list<int> list2(lst);//list2 e kopie na list
	list<int>list3(10);//creates a list with 10 elements
	list<int> list4(3, 12);//a list with size 10 and we initialize it with 12 for each elem?
	lst.assign(2, 3);//2 copies of 3 are assigned to lst

	lst.push_front(1);
	lst.pop_front();
	lst.push_front(2);
	lst.push_front(4);
	lst.push_front(4);
	lst.push_front(-1);
	print(lst);
	lst.remove(3);//it removes the elements equal to 3
	print(lst);
	cout << lst.back() << endl;
	//lst.unique();//removes the duplicates
	print(lst);
	lst.sort();
	print(lst);
	lst.merge(list4);
	print(lst);
	lst.reverse();
	print(lst);
	return 0;
}
