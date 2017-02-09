#include <iostream>
#include <string.h>
#include <assert.h>

using namespace std;
template <typename T>
struct node {
	T data;
	node<T>* next;
	node<T>* prev;
	node():next(nullptr),prev(nullptr){}
	node(const T& d,node<T>*n, node<T>*p):data(d),next(n),prev(p){}
};
template <typename T>
class doublyLinkedList
{
private:
	node < T>*head;
	node < T>*last;
	node<T>* curr;
	node<T>* temp;
	int size;
public:
	doublyLinkedList()
	{
		head = NULL;
		last = NULL;
		size = 0;
	}
	void addFront(const T&);
	void addEnd(const T&);
	~doublyLinkedList();
	void print();
	bool empty();
	T operator[](int index);
	void deleteFront();
	void deleteBack();
};
template <typename T>
void doublyLinkedList<T>::addFront(const T& d)
{
	node<T>*n = new node<T>(d, NULL, NULL);
	if (head == NULL)
	{
		head = n;
	}
	else
	{
		head->prev = n;
		n->next = head;
		head = n;
	}

	if (last == NULL)
	{
		last = n;
	}
	assert(head != NULL);
	size++;
}
template <typename T>
void doublyLinkedList<T>::addEnd(const T& d)
{
	node<T>*n = new node<T>(d, NULL, NULL);
	if (head == NULL)
	{
		addFront(d);
	}
	else
	{
		last->next = n;
		n->prev = last;
		last = last->next;
	}
	size++;
}
template <typename T>
doublyLinkedList<T>::~doublyLinkedList()
{
	cout << "destructor is called" << endl;
	curr = head;
	while (curr != NULL)
	{
		temp = curr->next;
		delete curr;
		curr = temp;
	}
	head = NULL;
}
template <typename T>
void doublyLinkedList<T>::print()
{
	curr = head;
	while (curr != NULL)
	{
		cout << curr->data << " ";
		curr = curr->next;
	}
	cout << endl;
}
template <typename T>
bool doublyLinkedList<T>::empty()
{
	if (size <= 0)
		return true;
	else
		return false;
}
template <typename T>
T doublyLinkedList<T>::operator[](int index)
{
	curr = head;
	while (curr != NULL&&index>0)//ili samo index-- vmesto index>0
	{
		curr = curr->next;
		index--;
	}
	if (curr == NULL)
	{
		cout << "the list does not have so many elements" << endl;
	}
	else {
		return curr->data;
	}
}
template <typename T>
void doublyLinkedList<T>::deleteFront()
{
	node<T>* delPtr = head;
	if (head == NULL)
	{
		cout << "the list is empty ";
	}
	head = head->next;
	//head->prev = NULL; i bez tozi red raboti
	delete delPtr;
	size--;
}
template <typename T>
void doublyLinkedList<T>::deleteBack()
{
	node<T>* delPtr = last;
	if (head == NULL)
	{
		cout << "the list is empty ";
	}
	last = last->prev;
	last->next = NULL;
	delete delPtr;
	size--;
}

int main()
{
	doublyLinkedList<int> l;
	l.addEnd(2);
	l.addEnd(3);
	l.addEnd(4);
	l.addFront(1);
	l.print();
	//cout << l[2]; ->3
	//l.deleteFront();
	l.deleteBack();
	l.print();

	return 0;
}


//circular
template <typename T>
void circularList<T>::addFront(const T& d)
{
	node<T>*n = new node<T>(d, NULL, NULL);
		head = n;
		head->next = NULL;
		if (last == NULL)
			last = n;
		else
			last->next = n;
	assert(head != NULL);
	size++;
}
template <typename T>
void circularList<T>::addEnd(const T& d)
{
	node<T>*n = new node<T>(d, NULL, NULL);
	if (head == NULL)
	{
		addFront(d);
	}
	curr = head;
	else
	{
		while (curr->next != head)
		{
			curr = curr -> next;
		}
		curr->next = n;
		last = n;
		n->next = head;
	}
	size++;
}
