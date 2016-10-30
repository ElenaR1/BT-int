#include <iostream>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

void printVector(const vector<int> &a)//const cause we're not making a chanfe
{
	cout << "vector: ";
	for (size_t i = 0; i < a.size(); i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void fillVector(vector<int> &newVector)//pass by ref because the vecotr can be very large in memory and i don't want to make a copy
//si even if i don't make changes i pass it by reference
{
	cout << "type in a list of numbers (-1 to stop)";
	int input;
	cin >> input;
	while (input != -1)
	{
		newVector.push_back(input);
		cin >> input;
	}
	cout << endl;
}

void reverse(const vector<int>& a)
{
	cout << "reversed vector: ";
	for (size_t i = a.size(); i>0 ; i--)//trqbva da e a.size()-1 s golemina 5 no posledniq indeks e 4 but this way it doesn't get to the last element
		//zashtoto e vinagi do i >0
	{
		cout << a[i-1] << " ";
	}
	cout << endl;
}

void printEvens(const vector<int>& a)
{
	cout << "evens: ";
	for (size_t i = 0; i < a.size(); i++)
	{
		if (a[i] % 2 == 0)
		{
			cout << a[i] << " ";
		}
	}
	cout << endl;
}
void replace(vector<int> &a)//we change the vector
{
	int old, replace;
	cout << "type in a number to be replaced with another num: ";
	cin >> old >> replace;
	for (size_t i = 0; i < a.size(); i++)
	{
		if (a[i] == old)
		{
			a[i] = replace;
		}
	}
	cout << endl;
}

int main()
{   //v.begin() reads vector from the 1st element
	//v.insert()=(v.begin()+integer,newValue) adds elemet BEFORE specified index number
	//v.erase(v.begin()++int)=removes element AT specified index
	//v.clear()=removes all elements in vector
	//v.empty() returns boolean value if whether vector is empty

	vector<int> v(3);//po default elementite sa 0
	v[0] = 10;
	v[1] = 22;
	v[2] = 5;
	v.push_back(7);//adds an element to the end
	cout << v.front() << endl;//retrieves the value from  the 1ste element
	cout << v.back() << endl;//the value of the last element
	cout<<v.at(2) << endl;//na 2riq indeks

	printVector(v);//when we call the function we get a copy of the vecotor v being passed to vector a in the func
	cout << endl;
	
	v.insert(v.begin(), 2);
	printVector(v);
	cout << endl;
	v.insert(v.begin()+3, 55);
	printVector(v);

	v.erase(v.begin() + 1);//to delete 10
	cout << endl;
	printVector(v);
	cout << endl;

	cout<<"is it empty: " << v.empty();
	cout << endl;
	v.clear();
	cout<<"is it empty: " << v.empty();
	cout << endl;

	vector<int> otherv;
	fillVector(otherv);
	printVector(otherv);
	reverse(otherv);
	printEvens(otherv);
	replace(otherv);
	printVector(otherv);

	return 0;
}
