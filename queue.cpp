#include <iostream>
#include <string.h>
#include <assert.h>

using namespace std;
template <typename T>
struct node {
	T data;
	node<T>* next;
	node():next(nullptr){}
	node(const T& d,node<T>*n):data(d),next(n){}
};
template <typename T>
class queue{
private:
	node<T>* head;
	node<T>* rear;
	node<T>* temp;
	node<T>* curr;
public:
	queue()
	{
		head = NULL;
		rear = NULL;
	}
	void enqueue(const T& addData)//push
	{
		node<T> *n = new node<T>(addData, NULL);
		if (head == NULL)//shte e NULL samo v nachalto kogato nqmame elementi v spisuka, inache vinagi sochi kum 1viq element
		{
			head = n;   
			if (rear == NULL)
				rear = head;
		}
		else
		{
			rear->next = n;
			rear = rear->next;
		}

	}
	void pop()
	{
		node<T> *n = head;
		if (n == rear)
		{
			head == NULL;
			rear == NULL;
		}
		else
		{
			head = head->next;
			delete n;
		}
	}
	void print()
	{
		curr = head;
		while (curr != NULL)
		{
			cout << curr->data << endl;
			curr = curr->next;
		}
	}
};
int main()
{
	queue<int> l;
	l.enqueue(2);
	l.enqueue(3);
	l.enqueue(4);
	l.pop();
	l.print();

	return 0;
}
