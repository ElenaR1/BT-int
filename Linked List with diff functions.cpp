//!!!!!!!!!! http://comproguide.blogspot.bg/search?q=linked+list+c%2B%2B RESHENI ZADACHI za linked list
#include <iostream>
#include <string.h>
#include <assert.h>

using namespace std;

template<typename T>
struct node {
	T data;
	node<T> *next;// ?
	node() :next(NULL) {}
	node(const T& d, node<T>*nextt) :data(d), next(nextt) {}
	node& operator!=(const node<T>& other)
	{
		return this->data != other.data&&this->next != other.next;
	}
};

template<typename T>
class list {
private:
	node<T> *head;
	node<T> *curr;
	node<T> *temp;
	node<T> *last;
public:
	list()
	{
		head = NULL;
		curr = NULL;
		temp = NULL;
	}
	list(const list<T>& other)
	{
		cout << "copy const is called" << endl;
		node<T> *curr = other.head;
		if (other.head == NULL)
		{
			head = curr = NULL;
		}
		else
		{
			node<T> *n = new node<T>(curr->data, NULL);// v novata kutiika kopirame stoinostta ot 1viq element na other list-a
			head = n;
			last = head;//oboznachavame kude da ni e last-a
			curr = curr->next;//nashiq curr veche vurvi po drugiq list

			while (curr != NULL)
			{
				node<T>* newNode = new node<T>(curr->data, NULL);
				last->next = newNode;
				last = last->next;
				curr = curr->next;
			}
		}
	}

	list&operator=(const list<T>& other)
	{
		cout << "operator= is called" << endl;
		if (this != &other)
		{
			node<T> *curr = other.head;
			if (other.head == NULL)
			{
				head = curr = NULL;
			}
			else
			{
				node<T> *n = new node<T>(curr->data, NULL);// v novata kutiika kopirame stoinostta ot 1viq element na other list-a
				head = n;
				last = head;//oboznachavame kude da ni e last-a
				curr = curr->next;//nashiq curr veche vurvi po drugiq list

				while (curr != NULL)
				{
					node<T>* newNode = new node<T>(curr->data, NULL);
					last->next = newNode;
					last = last->next;
					curr = curr->next;
				}
			}
		}
		return *this;
	}

	node<T> *getHead()
	{
		return this->head;
	}
	void sortedInsert(const T& addData)
	{
		if (head == NULL)
		{
			head = new node<T>(addData, NULL);
		}
		node<T>* temp = head;
		node<T>* prev = NULL;
		if (addData < head->data)
		{
			addFront(addData);
		}

		while (temp != NULL&&addData > temp->data)
		{
			prev = temp;
			temp = temp->next;
		}

		assert(prev->data == 10);
		assert(temp->data == 20);
		node<T>*n = new node<T>(addData, NULL);
		n->next = temp;
		prev->next = n;
	}

	node<T>* sortedInsert2(node<T>*Head, node<T>* newNode)
	{
		if (Head == NULL || Head->data >= newNode->data)
		{
			newNode->next = Head;
			Head = newNode;
			return Head;
		}
		node<T>* ptr = Head;
		node<T>* prev = NULL;
		while (ptr != NULL && ptr->data < newNode->data)
		{
			prev = ptr;
			ptr = ptr->next;
		}
		newNode->next = ptr;
		prev->next = newNode;
		return Head;
	}

	void insertionSort()
	{
		cout << "Insertion sort: " << endl;
		head = insertionSortPr();
	}

	node<T>* insertionSortPr()
	{
		if (!head || !head->next)
			return head;
		node<T>* ptr = head->next;
		node<T>* res = head;
		res->next = NULL;///??? zashto tova ne znachi li che ptr e NULL
		while (ptr != NULL)
		{
			node<T>* temp = ptr;
			ptr = ptr->next;
			res = sortedInsert2(res, temp);
		}
		return res;//res node li e ili cql list
	}

	void addFront(const T& addData)
	{
		node<T> *n = new node<T>(addData, head);//sega head sochi kum novieq 1vi element-n
		head = n;   //head->data = addData;
		if (last == NULL)
			last = head;
		assert(head != NULL);
	}
	void addEnd(const T& addData)
	{
		node<T> *n = new node<T>(addData, NULL);//n sochi kum kutiika s data-addData i pointer sochesht kum NULL
												//n->data = addData;
												//n->next = NULL;
		if (head == NULL)//shte e NULL samo v nachalto kogato nqmame elementi v spisuka, inache vinagi sochi kum 1viq element
		{
			addFront(addData);
		}
		else {
			last->next = n;
			last = last->next;
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
	T operator[](int index)
	{
		curr = head;
		while (curr != NULL && index--)
		{
			curr = curr->next;
		}
		if (curr == NULL)
		{
			cout << "the list does not have so many elements" << endl;
		}
		else {
			return curr->data;
		}
	}
	bool empty()
	{
		return head == NULL;
	}
	~list()
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
	void deleteFirstNode()
	{
		if (head == NULL)
		{
			cout << "the queue is empty ";
		}
		else
		{
			cout << "deleting the first node with value: " << head->data << endl;
			curr = head;//ako prosto iztriq head nqma da imam head veche a ne moje taka
			head = head->next;

			delete curr;
		}
	}
	void deleteNode(const T& delData)
	{
		node<T>* delPtr = head;
		curr = head;
		temp = head;
		while (curr != NULL&&curr->data != delData)
		{
			temp = curr;
			curr = curr->next;
		}
		if (curr == NULL)//mai e sushtoto kato current->next da e null
		{
			cout << delData << " is not found " << endl;
			delete delPtr;//we delete it if we don't find the value
		}
		else
		{
			delPtr = curr;
			if (head == curr)
			{
				deleteFirstNode();
			}
			else
			{
				curr = curr->next;
				temp->next = curr;

				delete delPtr;
				cout << "the value " << delData << " was deleted" << endl;
			}
		}
	}
	void swap(int &a, int&b)
	{
		int temp = a;
		a = b;
		b = temp;
	}
	void sort()
	{
		curr = head;
		int count = 0;
		while (curr != NULL)
		{
			count++;
			curr = curr->next;
		}
		for (size_t i = count; i > 1; i--)
		{
			node<T>* swap1 = head;
			for (int j = 0; j < count - 1; j++)
			{
				if (swap1->data > swap1->next->data)
				{
					node<T>* swap2 = swap1->next;
					swap1->next = swap2->next;
					swap2->next = swap1;
					if (swap1 == head)
					{
						head = swap2;
						swap1 = swap2;
					}
					else
					{
						swap1 = swap2;
						temp->next = swap2;
					}
				}
				temp = swap1;
				swap1 = swap1->next;
			}
		}
	}

	void swapSort()
	{
		cout << "swapping sort: " << endl;
		node<T>* current = head;
		node<T>* insertionPointer = head;

		current = current->next;

		while (current != NULL)
		{

			insertionPointer = head;//it always starts pointing at the head

			while (insertionPointer->next != current)//when the next is current it reset its entire position and
													 //goes back pointing to the head
			{
				if (insertionPointer->data > current->data)
				{
					swap(insertionPointer->data, current->data);
					//T temp = current->data;
					//current->data = insertionPointer->data;
					//insertionPointer->data = temp;

				}
				else
				{

					insertionPointer = insertionPointer->next;

				}

			}

			current = current->next;

		}
	}

	void doBubbleSort()
	{
		cout << "bubble sort: " << endl;
		node<T>* curr;
		node<T>* nextNode;
		node<T>* prev;
		node<T>* swapNode;
		node<T>* nodeForFindingTheEndOfTheList;

		nodeForFindingTheEndOfTheList = nullptr;
		while (nodeForFindingTheEndOfTheList != head->next)
		{
			prev = head;
			curr = head;
			nextNode = curr->next;
			while (curr != nodeForFindingTheEndOfTheList)
			{
				if (curr->data > nextNode->data)
				{
					if (curr == head)
					{
						swapNode = nextNode->next;
						nextNode->next = curr;
						curr->next = swapNode;

						head = nextNode;
						prev = nextNode;
					}

					else
					{
						swapNode = nextNode->next;
						nextNode->next = curr;
						curr->next = swapNode;

						prev->next = nextNode;
						prev = nextNode;
					}
				}
				else
				{
					prev = curr;
					curr = curr->next;
				}
				nextNode = curr->next;
				if (nextNode == nodeForFindingTheEndOfTheList)
				{
					nodeForFindingTheEndOfTheList = curr;
				}
			}
		}
	}


	class iterator {
	private:
		node<T>* current;
	public:
		iterator(node<T>* n)
		{
			current = n;
		}
		iterator& operator++()
		{
			current = current->next;
			return *this;
		}
		bool operator!=(const iterator& other)
		{
			return current != other.current;
		}
		T& operator*()
		{
			return current->data;
		}
	};
	iterator begin()//it returns an iterator
	{
		return iterator(head);
	}
	iterator end()//it returns an iterator
	{
		return iterator(last->next);
	}

	list mergeList(list<int>& other)
	{
		cout << "mergeList: " << endl;
		list<int> newList;
		newList.head = NULL;
		newList.last = NULL;

		if (head == NULL)
			return other;
		if (other.head == NULL)
			return *this;
		node<T>* temp1 = head;
		node<T>* temp2 = other.head;
		while (temp1 != NULL&&temp2 != NULL)
		{
			if (temp1->data<temp2->data)
			{
				T dat = temp1->data;
				newList.addEnd(dat);
				temp1 = temp1->next;
			}
			else
			{
				T dat = temp2->data;
				newList.addEnd(dat);
				temp2 = temp2->next;
			}
		}
		assert(newList.head->data == 1);
		assert(temp2 == NULL);

		if (temp1 == NULL)
		{
			while (temp2 != NULL)
			{
				T dat = temp1->data;
				newList.addEnd(dat);
				temp2 = temp2->next;
			}
		}
		if (temp2 == NULL)
		{
			while (temp1 != NULL)
			{
				T dat = temp1->data;
				newList.addEnd(dat);
				temp1 = temp1->next;
			}
		}
		return newList;
	}


	list InterleaveLists(list<int> l2)
	{
		cout << "InterleaveLists: " << endl;
		list<int> newList;
		newList.head = NULL;
		newList.last = NULL;

		if (this->empty())
			return l2;
		if (l2.empty())
			return *this;
		node<T>* temp1 = head;
		node<T>* temp2 = l2.head;

		while (temp1 != NULL&&temp2 != NULL)
		{
			T dat = temp1->data;
			T dat2 = temp2->data;
			newList.addEnd(dat);
			newList.addEnd(dat2);
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		if (temp1 == NULL)
		{
			while (temp2 != NULL)
			{
				T dat = temp1->data;
				newList.addEnd(dat);
				temp2 = temp2->next;
			}
		}
		if (temp2 == NULL)
		{
			while (temp1 != NULL)
			{
				T dat = temp1->data;
				newList.addEnd(dat);
				temp1 = temp1->next;
			}
		}
		return newList;
	}
	void printReverse(node<T>* ptr)
	{
		if (ptr != NULL)
		{
			printReverse(ptr->next);
			cout << ptr->data;
		}
	}
	void printReverse()
	{
		printReverse(head);
	}
	void reverse()
	{
		curr = head;
		node<T>* prev = new node<T>();
		node<T>* next;
		while (curr != NULL)
		{
			next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		head = prev;
	}
};

int main()
{
	list<int> ll;
	ll.addEnd(1);
	ll.addEnd(2);
	ll.addEnd(3);
	ll.addEnd(4);
	ll.print();
	ll.printReverse();
	cout << endl;
	ll.reverse();
	ll.print();
	cout << endl;
	cout << "..........." << endl;

	list<int> l1;
	l1.addEnd(5);
	l1.addEnd(2);
	l1.addEnd(3);
	l1.addFront(12);
	l1.addEnd(4);
	l1.print();
	list<int>::iterator it = l1.begin();
	for (it = l1.begin(); it != l1.end(); ++it)
	{
		cout << "it=" << *it << " ";
	}
	cout << endl;
	//l1.sort();
	//l1.swapSort();
	//l1.print();
	//l1.doBubbleSort();
	l1.insertionSort();
	l1.print();

	list<int> l2;
	l2.addEnd(2);
	l2.addEnd(7);
	l2.addEnd(10);
	l2.addEnd(20);
	cout << "/n..........." << endl;
	l2.print();
	l2.sortedInsert(15);
	cout << "/n..........." << endl;
	l2.print();
	list<int> l3;
	l3.addEnd(1);
	l3.addEnd(3);
	l3.addEnd(17);
	cout << "..........\n";
	cout << "merged lists: ";
	l2.mergeList(l3).print();
	cout << "..........\n";
	l2.InterleaveLists(l3).print();

	//list<int> l2 = l1;//cpy cnstr
	//l2.print();
	//l1.deleteFirstNode();
	//l1.print();
	//l1.deleteNode(3);
	//l1.print();
	//list<int> l3;
	//l3 = l1;//operator=
	//l3.print();//cout << l2[1];

	return 0;
}
