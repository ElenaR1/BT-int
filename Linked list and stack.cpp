#include <iostream>
#include <string.h>

using namespace std;

struct node {
	int data;
	node*next;
};
class list {
private:
	typedef node* nodePtr;
	nodePtr head;
	node* temp;
	node* current;//=n
public:
	list()
	{
		head = NULL;
		current = NULL;
		temp = NULL;
	};
	node*getHead()
	{
		return head;
	}
	void addNodeEnd(int addData)
	{
		
		node*n = new node;//ili: node *n = new node(addData, NULL);
		n->data = addData;
		n->next = NULL;
		if (head != NULL)
		{
			current = head;//we make curr point to the same thing head is pointing to
			while (current->next != NULL)//we are gonna check to see if we're in the end of the list
			//so this case will happen at the very end of the list. We do this until we reach the end
			{
				current = current->next;
			}
			current->next = n;//current =new node
		}
		//if we don't have at lest 1 element in the list
		else {
			head = n;//t.e nqmame elementi v lista i n e 1viqt element i pointer-a head sochi kum nego
		}
	}
	void deleteNode(int delData)//we\re gonna search for a node that contains a value equal to delData
	{
		node* delPtr = NULL;//we are pointing it to nothing
		temp = head;
		current = head;
		while (current!= NULL&&current->data != delData)
		{
			temp = current;
			current = current->next;
		}
		if (current == NULL)//mai e sushtoto kato current->next da e null
		{
			cout << delData << " is not found " << endl;
			delete delPtr;//we delete it if we don't find the value
		}
		else
		{
			delPtr = current;
			current = current->next;
			temp->next = current;
			if(delPtr==head)
			{
				head = head->next;
				temp = NULL;//kato go mahna nishto ne se promenq zashto go pisha
			}
			delete delPtr;
			cout << "the value " << delData << " was deleted" << endl;
		}
	}
	void print()
	{
		current = head;
		while (current!= NULL)
		{
			cout << current->data << endl;
			current = current->next;
		}
	}

void addNodeFront(int newData)
	{
		node* n = new node;// (newData, head);
		n->data = newData;// Taka ako e bez konstruktor
		n->next = head;
		head = n;
	}
	int get(int index)
	{
		curr = head;
		while (index--&&curr!= NULL)
		{
			curr = curr->next;
		}
		if (curr == NULL)
		{
			cout << "the list does not have so many elements" << endl;
		}
		return curr->data;
	}
	int operator[](int index)
	{
		curr = head;
		while (index--&&curr != NULL)
		{
			curr = curr->next;
		}
		if (curr == NULL)
		{
			cout << "the list does not have so many elements" << endl;
		}
		return curr->data;
	}
	void reverse()
	{
		node *previous = NULL;
		curr = head;
		node*nextNode;
		while (curr != NULL)
		{
			nextNode = curr->next;
			curr->next = previous;
			previous = curr;
			curr = nextNode;
		}
		head = previous;
	}

	void append(list& other)
	{
		node* linkedlistPtr;
		if (this->getHead() == NULL)
		{
			linkedlistPtr = other.getHead();
		}
		//tozi if ne raboti
		if (other.getHead() == NULL)
		{
			linkedlistPtr = head;
		}
		curr = this->head;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}
		curr->next = other.getHead();
		linkedlistPtr = head;//bez tova sushto raboti
	}
	//i return a reference to the list of integers
	void clear()
	{
		curr = head;
		while (curr!= NULL)
		{	
			temp = curr->next;
			delete curr;
			curr = temp;
		}
	}
	~list()
	{
		clear();
	}
	//ne raboti operator=
	/*const list& operator=(const list& l)
	{
		if (this != &l)//we check if the addresses are the same -> this is the same object
		{
			//ako tozi list ne e prazen iskam da mu premahna elementite
			if (head != NULL)
			{
				clear();
			}
				
				node*originalPointer = l.head;
				while (originalPointer != NULL)
				{
					originalPointer = originalPointer->next;
					if (head == NULL)
					{
						node*n = new node;
						n->data = originalPointer->data;
						n->next = NULL;
						head = n;
						curr = head;
					}
					else {
						originalPointer = originalPointer->next;
						node*newNode = new node;
						newNode->data = originalPointer->data;
						curr->next = newNode;
						curr = curr->next;
					}
					originalPointer = originalPointer->next;
				}
			}		
		return*this;
	}*/
};
int main()
{
	list ob;
	ob.addEnd(1);
	ob.addEnd(2);
	ob.addEnd(3);
	ob.addEnd(4);
	//ob.print();
	//cout << endl;
	list ob2;
	ob2.addEnd(5);
	ob2.addEnd(6);
	ob2.addEnd(7);
	ob.append(ob2);
	ob.print();
	cout << endl;
	
	//list ob3;
	//ob3.append(ob2); ne raboti
	//ob.append(ob3);raboti
	
	
	/*ob.deleteNode(2);
	ob.print();
	ob.addFront(12);
	cout << endl;
	ob.print();
	cout << endl;
	cout<<ob.get(2);*/
	
	
	return 0;
}

S TEMPLATE
#include <iostream>
#include <string.h>
#include <assert.h>

using namespace std;

template<typename T>
struct node {
	T data;
	node<T> *next;// ?
	node(const T& d, node<T>*nextt) :data(d), next(nextt) {}
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
			curr = curr->next;
			temp->next = curr;
			if (head == curr)
			{
				head = head->next;
				temp = NULL;//t.k e pointer-a predi curr a tam nqma nishto
			}
			delete delPtr;
			cout << "the value " << delData << " was deleted" << endl;
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
};

int main()
{
	list<int> l1;
	l1.addEnd(1);
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

	//list<int> l2 = l1;//cpy cnstr
	//l2.print();
	//l1.deleteFirstNode();
	//l1.deleteNode(3);
	//list<int> l3;
	//l3 = l1;//operator=
	//l3.print();//cout << l2[1];

	return 0;
}




List with different functions:
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
};

int main()
{
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



STACK 
#include <iostream>
#include <string.h>
#include <string>

using namespace std;
template<class T>
struct node {
	node<T>* next;
	T data;
	node() :next(NULL) {}
	node(const T& d,node<T>* n):data(d),next(n){}
};

template<class T>
class stack
{
private:
node<T>* top;	
public:
	stack()
	{
		top = NULL;
	}
	void push(const T& newData)
	{
		node<T>* n = new node<T>(newData, top);
		//n->data = newData;
		//n->next = head;
		top = n;
	}
	void pop()
	{
		if (top == NULL)
		{
			cout << "the stack is empty" << endl;
		}
		else
		{
			node<T>* temp = top;
			top = top->next;
			cout << "Deleting the first node with value " << temp->data << endl;
			delete temp;
		}
	}
	void print()
	{
		node<T>*curr;
		curr = top;
		while (curr != NULL)
		{
			cout << curr->data << " ";
			curr = curr->next;
		}
	}
	 T& peek()
	{
		return top->data;
	}
	bool isEmpty()
	{
		if (top == NULL)
		{
			return true;
		}
		return false;
	}
	const T& getMax()
	{
		stack<int>stack2;
		int max = peek();
		while (!this->isEmpty())
		{
			if (this->peek() > max)
			{
				max = this->peek();
			}
			else
			{
				stack2.push(this->peek());
				this->pop();
			}
		}
		while (!stack2.isEmpty())
		{
			push(stack2.peek());
			stack2.pop();
		}
		return max;
	}

};
/*
bool arePair(char opening, char closing)
{
	if (opening == '(' && closing == ')') return true;
	else if (opening == '{' && closing == '}') return true;
	else if (opening == '[' && closing == ']') return true;
	return false;
}
bool bracket(string a)
{
	stack<char> s;
	for (size_t i = 0; i < a.size(); i++)
	{
		if (a[i] == '('||a[i]=='{' || a[i] == '[')
		{
			s.push(a[i]);
		}
		if (a[i] == ')'|| a[i] == '}' || a[i] == ']')
		{
			if (s.empty()||!arePair(s.top(),a[i]))
				return false;
			s.pop();
		}

	}
	if (s.empty())
		return true;
	else
		return false;
//string c = "({[]})";
	//string d = "({[)})";
	//cout << bracket(c) << endl;
	//cout << bracket(d) << endl;
}*/
bool bracket(string a)//ako a e string a = "((()))";
{
	stack<char> s;
	for (size_t i = 0; i < a.length(); i++)
	{
		if (a[i] == '(')
		{
			s.push(a[i]);//vseki put kato sreshtenm otvarqshta dobavqme
		}
		else if (a[i] == ')')//vseki put kato sreshtenm zatvarqshta mahame
		{
			if (s.isEmpty())
			{
				return false;
			}
			else
			{
				s.pop();
			}
		}
	}
	if (s.isEmpty())//ako e pravilen izrazut broqt na otvarqshtite i zatvarqshtitie skobi e raven-> shte se poluchi che 
		//stekut e prazen
	{
		return true;
	}
	else
	{
		return false;
	}
}


void reverse(char a[])// a="Hello/0"
{
	stack<char> s;
	int len = strlen(a);//ako e +1 ne stava
	for (size_t i = 0; i < len; i++)
	{
		s.push(a[i]);
	}
	//loop for pop
	for (size_t i = 0; i <len; i++)
	{
		a[i] = s.peek();//a[0]='/0' 1. a[1]='o' 2.a[2]='l' 3.a[3]='l' 4.a[4]='e' 5.a[5]='H' mai 1viqt element e 'o' a ne '/0'
		s.pop();//i sega mahame /0 1. sega mahame 'o' 2. sega mahame 'l'...
	}

}
bool isNumber(char&a)
{
	if (!isdigit(a))
	{
		return false;
	}
	else
		return true;
}


void evaluatePostfix(char*a)
{
	int n;
	int result;
	stack<int> newStack;
	int len = strlen(a);
	for (size_t i = 0; i < len; i++)// "63+2*"=18
	{
		if (isNumber(a[i]))
		{
			char c = a[i];
			n = c - '0';
			newStack.push(n);//6 vliza posle 3 vliza
			
		}
		if (a[i] == '+')
		{
			int x = newStack.peek();//x=3
			newStack.pop();
			int y = newStack.peek();//y=6
			newStack.pop();
			result = x + y;//8
			newStack.push(result);//vkarvame v steka 9
		}
		if (a[i] == '-')
		{
			int x = newStack.peek();
			newStack.pop();
			int y = newStack.peek();
			newStack.pop();
			result = y - x;//8
			newStack.push(result);
			
		}
		if (a[i] == '*')
		{
			int x = newStack.peek();
			newStack.pop();
			int y = newStack.peek();
			newStack.pop();
			result = x*y;//8
			newStack.push(result);
			
		}
		if (a[i] == '/')
		{
			int x = newStack.peek();
			newStack.pop();
			int y = newStack.peek();
			newStack.pop();
			result = y / x;//8
			newStack.push(result);
		}
	}
	cout << "result of expression is  " << newStack.peek();
}
void evaluatePrefix(char a[])
{
	//reverse(a);
	//evaluatePrefix(a);
	stack<int> s;
	int n;
	int result;
	int len = strlen(a);
	for (int i = len-1; i>=0; i--)
	{
		if (isNumber(a[i]))
		{
			char c = a[i];
			n = c - '0';
			s.push(n);
		}
		if (a[i] == '+')
		{
			int x = s.peek();
			s.pop();
			int y = s.peek();
			s.pop();
			result = x + y;
			s.push(result);
		}
		if (a[i] == '-')
		{
			int x = s.peek();
			s.pop();
			int y = s.peek();
			s.pop();
			result = x - y;
			s.push(result);
		}
		if (a[i] == '*')
		{
			int x = s.peek();
			s.pop();
			int y = s.peek();
			s.pop();
			result = y * x;
			s.push(result);
		}
		if (a[i] == '/')
		{
			int x = s.peek();
			s.pop();
			int y = s.peek();
			s.pop();
			result = x / y;
			s.push(result);
		}
	}
	cout << "result: " << s.peek() << endl;
}



int main()
{
    stack<int> s;
	s.push(5);
	s.push(4);
	s.push(9);
	s.push(13);
	s.push(7);
	s.push(10);
	s.print();
	cout << endl;
	s.pop();
	s.print();
	cout << endl;
	cout << s.peek();
	cout << endl;

	string a = "((()))";
	cout << bracket(a) << endl;

	
	char expression[] = "63+2*";
	evaluatePostfix(expression);
	char exp[] = "-*+4325";
	evaluatePrefix(exp);//9	

	char str[] = "Hello";
	reverse(str);
	cout << "after reversing the string: " << str << endl;//// ? zashto ne stava


	cout << endl;
	cout<<"the max data in the stack is: " << s.getMax();

	return 0;
}



#include <iostream>
#include <string.h>
#include <string>
#include <stack>

using namespace std;

bool IsOperand(char ch)
{
	if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
		return true;
	}
	return false;
}

bool IsOperator(char C)
{
	if (C == '+' || C == '-' || C == '*' || C == '/' || C == '^') {
		return true;
	}
	return false;
}
bool IsLeftParenthesis(char ch)
{
	if (ch == '(') {
		return true;
	}
	return false;
}

bool IsRightParenthesis(char ch)
{
	if (ch == ')') {
		return true;
	}
	return false;
}

bool Flag(char ch)
{
	if (!IsOperand(ch) || !IsOperator(ch) || !IsLeftParenthesis(ch) || !IsRightParenthesis(ch)) {
		return false;
	}
	return true;
}

int IsRightAssociative(char op)
{
	if (op == '^') {
		return true;
	}
	return false;
}

int GetOperatorWeight(char op)
{
	int weight = -1;
	switch (op) {
	case '+':
	case '-':
		weight = 1;
		break;
	case '*':
	case '/':
		weight = 2;
		break;
	case '^':
		weight = 3;
		break;
	}
	return weight;
}

bool HasHigherPrecedence(char op1, char op2)
{
	int op1Weight = GetOperatorWeight(op1);
	int op2Weight = GetOperatorWeight(op2);

	// If operators have equal precedence, return true if they are left associative.
	// BUT REMEMBER...return false, if right associative.
	// if operator is left-associative, left one should be given priority.
	if (op1Weight == op2Weight) {
		if (IsRightAssociative(op1)) {
			return false;
		}
		else {
			return true;
		}
	}
	return op1Weight > op2Weight ? true : false;
}

string InfixToPostfix(string expression)
{
	stack <char> S;
	string postfix = "";
	for (int i = 0; i < expression.length();i++)//
	{
		if (Flag(expression[i])) {
			continue;
		}
		// If character is operator, pop two elements from stack, perform operation and push the result back.
		else if (IsOperator(expression[i]))
		{
			while (!S.empty() && S.top() != '(' && HasHigherPrecedence(S.top(), expression[i])) {
				postfix += S.top();
				S.pop();
			}
			S.push(expression[i]);
		}
		else if (IsOperand(expression[i])) {
			postfix += expression[i];
		}
		else if (expression[i] == '(') {
			S.push(expression[i]);
		}
		else if (expression[i] == ')') {
			while (!S.empty() && S.top() != '(') {
				postfix += S.top();
				S.pop();
			}
			S.pop();
		}
	}

	while (!S.empty()) {
		postfix += S.top();
		S.pop();
	}

	return postfix;
}
int main()
{
	
	string a = "A+B*C-D*E";
	cout << InfixToPostfix(a) << endl;
		string b = "((A+B)*C-D)*E";
		cout << InfixToPostfix(b) << endl;

	return 0;
}


//QUEUE
#include <iostream>
#include <assert.h>
#include <string.h>
#include <vector>
#include <fstream>


using namespace std;



template <class T>
struct node {
	T data;
	node<T> *next;
	node(T& d, node<T>*nextt) :data(d), next(nextt) {}//podavame go po referencia zashtoto moje da podavame obekt i ne iskame da ni se izvikva cpy constr
};

template<typename T>
class queue {
private:
	node<T>* head;
	node<T>* last;
public:
	queue()
	{
		head = NULL;
	}
	void push(T& newData)
	{
		node<T>* n = new node<T>(newData, null);
		if (head == NULL)
		{
			head = n;
		}
		last->next = n;//moje i s while cikul s current
		last = last->next;
	}
	void pop()
	{
		if (head == NULL)
		{
			cout << "the queue is empty ";
		}
		else
		{
			node<T>*temp = head;
			head = head->next;
			cout << "deleting the first node with value: " << temp->data;
			delete temp;
		}
	}
	bool isEmpty()
	{
		if (head == NULL)
		{
			return true;
		}
		return false;
	}
	 T& front()
	{
		if (head == NULL)
		{
			cout << "empty ";
		}
		else
		{
			return head->data;
		}
	}

};

class Heap {// Priority queue
private:
	vector<int> v;

public:
	int parent(int index)//parent of node with index 'index'
	{
		return v[index / 2];
	}
	int leftChild(int index)
	{
		return v[2 * index + 1];
	}
	int rightChild(int index)
	{
		return v[2 * index + 2];
	}
	void heapDown(int i)
	{
		int largest = i;
		int left = 2*i+1;
		int right = 2*i+2;

		if (i < v.size())
		{
			if (largest < left)
			{
				swap(largest, left);
			}
			if (largest < right)
			{
				swap(largest, right);
			}
		}
	}
	void swap(int &a, int &b)
	{
		int temp = a;
		a = b;
		b = temp;
	}
};

int main()
{
	queue<int> a;
	int b = 1;
	int c = 2;

	a.push(b);
	a.push(2);
	a.push(3);
	a.front() = 10;
	cout << a.front();

	return 0;
}
