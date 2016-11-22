#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <string.h>
#include <string>
#include <assert.h>

using namespace std;
/*	stack<w> s;
	w a;
	a.first = 1;
	a.second = 5;
	s.push(a);
	s.push(w(1,2));*/
template <class T>
using mapFn = T(*)(const T&);
template <class T>
struct node {
	T data;
	node<T> *left;
	node<T> *right;
	node() :left(NULL), right(NULL) {}
	node(const T d, node<T> *l, node<T> *r) :data(d), left(l), right(r) {}
};

#define OPER_PRINT 0
#define OPER_TRAV 1

template <class T>
using waiting = pair<int, node<T>*>;

template <class T>
class bt {
private:
	node<T> *root;
	void addNode(node<T>* &subTreeRoot, const T& x)
	{
		if (subTreeRoot == NULL)
		{
			subTreeRoot = new node<T>(x, NULL, NULL);
		}
		else
		{
			if (x < subTreeRoot->data)
			{
				addNode(subTreeRoot->left, x);
			}
			else if (x>subTreeRoot->data)
			{
				addNode(subTreeRoot->right, x);
			}
		}
	}
	node<T>* insertNode(node<T>* subTreeRoot, const T& x)
	{
		if (subTreeRoot == NULL)
		{
			return new node<T>(x, NULL, NULL);
		}
		else
		{
			if (x > subTreeRoot->data)
			{
				return new node<T>(subTreeRoot->data, copyTree(subTreeRoot->left), insertNode(subTreeRoot->right, x));
				//vikam copyTree za STR->left t.k iskam sushtoto i nishto ne dobavqm
				//a za str->right obrazuvam novo durvo
			}
			else if (x < subTreeRoot->data)
			{
				return new node<T>(subTreeRoot->data, insertNode(subTreeRoot->left, x), copyTree(subTreeRoot->right));

			}
		}
	}
	void printPrivate(node<T> * subTreeRoot)const
	{
		if (subTreeRoot == NULL)
		{
			return;// kakvo pravi??
		}
		if (subTreeRoot != NULL)
		{
			cout << subTreeRoot->data << " ";
			printPrivate(subTreeRoot->left);
			printPrivate(subTreeRoot->right);
		}
	}
	void prettyPrintPrivate(node<T>*subTreeRoot, int curLevel)
	{
		if (subTreeRoot == NULL)
		{
			return;// kakvo pravi??
		}
		else
		{
			if (subTreeRoot->right != NULL)
			{
				prettyPrintPrivate(subTreeRoot->right, curLevel + 4);
			}
			if (curLevel != 0) {
				cout << setw(curLevel) << ' ';
			}
			if (subTreeRoot->right != NULL)
			{
				cout << " /\n" << setw(curLevel) << ' ';
			}
			cout << subTreeRoot->data << "\n ";
			if (subTreeRoot->left != NULL)
			{
				cout << setw(curLevel) << ' ' << " \\\n";// kakvo e 
				prettyPrintPrivate(subTreeRoot->left, curLevel + 4);
			}
		}
	}
	node<T>* copyTree(node<T>* subTreeRoot)
	{
		if (subTreeRoot == NULL)
		{
			return	NULL;
		}
		else
			return new node<T>(subTreeRoot->data, copyTree(subTreeRoot->left), copyTree(subTreeRoot->right));
	}
	void deleteAll(node<T>* subTreeRoot)
	{
		if (subTreeRoot == NULL)
		{
			return;//The return statement stops execution and returns to the calling function. 
				   //When a return statement is executed, the function is terminated immediately at that point, regardless of whether 
				   //it's in the middle of a loop, etc.
		}
		else
		{
			deleteAll(subTreeRoot->left);
			deleteAll(subTreeRoot->right);
			cout << "deleting the node containing the data " << subTreeRoot->data << endl;
			delete subTreeRoot;
		}
	}
	T minElement(node<T>* subTreeRoot)
	{

		assert(subTreeRoot != NULL);
		if (subTreeRoot->left != NULL)
		{
			return minElement(subTreeRoot->left);
		}
		else
		{
			return subTreeRoot->data;
		}
	}
	void deleteElement(node<T>* &subTreeRoot, const T& x)
	{
		T rootData = subTreeRoot->data;
		if (subTreeRoot == NULL)
		{
			return;
		}
		if (subTreeRoot->data == x&& subTreeRoot->left == NULL&&subTreeRoot->right == NULL)
		{
			delete subTreeRoot;
			subTreeRoot = NULL;
			return;
		}
		if (x < subTreeRoot->data)
		{
			deleteElement(subTreeRoot->left, x);
			return;
		}
		if (x > subTreeRoot->data)
		{
			deleteElement(subTreeRoot->right, x);
			return;
		}
		//ot tuk natatuk znachi che str->data suvpada s x
		if (subTreeRoot->left == NULL)
		{
			node<T>* delPtr = subTreeRoot;
			subTreeRoot = subTreeRoot->right;
			delPtr->right = NULL;
			delete delPtr;
			return;
		}
		if (subTreeRoot->right == NULL)
		{
			node<T> *delPtr = subTreeRoot;
			subTreeRoot = subTreeRoot->left;
			delPtr->left = NULL;//because we want to copmpletely disconnect this node from the tree
			delete delPtr;
			return;

		}
		else
		{
			T smallestInRightSubtree = minElement(subTreeRoot->right);
			subTreeRoot->data = smallestInRightSubtree;
			deleteElement(subTreeRoot->right, smallestInRightSubtree);
			cout << "the root node with data " << rootData << " was deleted and the new root contains data: "
				<< subTreeRoot->data;
		}
	}
	bool isBinary(node<T>* subTreeRoot, int min, int max)
	{
		if (subTreeRoot == NULL)
		{
			return true;
		}
		if (subTreeRoot->data > min&&subTreeRoot->data < max
			&&isBinary(subTreeRoot->left, min, subTreeRoot->data)
			&& isBinary(subTreeRoot->right, subTreeRoot->data, max))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
public:

	bt(const bt<T>& other)
	{
		cout << "Copt constructor is called now " << endl;
		root = copyTree(other.root);//ne moje prosto root=other.root zashtoto taka shte sochi kum sushtata kutiika kum koqto 
									//sochi i drugiq root, a nie iskame da se obrazuvat novi sushtite kutiik
	}
	bt& operator=(const bt<T>& other)
	{
		cout << "operator is called " << endl;
		if (this == &other)//pointer-a this sudurja adresa na nashiq obekt 
		{
			return *this;
		}
		else
		{
			deleteAll(root);//ako ima neshto v druvotgo go triem
			root = copyTree(other.root);
		}
		return *this;//vrushtame go sus zvezda za da vurnem obekta,a ne adresa mu
	}

	bt()
	{
		root = NULL;
	}
	~bt()
	{
		cout << "destructor is called " << endl;
		deleteAll(root);
	}
	void addNode(const T& x)
	{
		addNode(root, x);
	}
	bt insertNode(const T& x)
	{
		bt<T> result;
		result.root = insertNode(root, x);
		return result;
	}
	void print()
	{
		printPrivate(root);
		cout << endl;
	}
	void prettyPrint()
	{
		prettyPrintPrivate(root, 1);
	}
	T minElement()
	{
		return minElement(root);
	}
	void deleteElement(const T& x)
	{
		deleteElement(root, x);
	}
	bool isBinary()
	{
		return isBinary(root, INT_MIN, INT_MAX);
	}
	void iterationPrint()
	{
		iterationPrint(root);
	}
	void iterationPrint(node<T> * subTreeRoot)
	{
		stack <waiting<T>> operations;
		operations.push(waiting<T>(OPER_TRAV, subTreeRoot));
		cout << "{";

		while (!operations.empty())
		{
			waiting<T> topOperation = operations.top();
			node<T>* topNode = topOperation.second;
			operations.pop();

			if (topOperation.first == OPER_PRINT)
			{
				cout << topNode->data << " ";
			}
			else if (topNode != nullptr) {
				/*vmesto da push-va topNode->righ po tozi nachin moje:
				waiting<T> a;
				a.first = OPER_TRAV;
				a.second = topNode->right;
				operations.push(a);*/
				operations.push(waiting<T>(OPER_TRAV, topNode->right));
				operations.push(waiting<T>(OPER_PRINT, topNode));
				operations.push(waiting<T>(OPER_TRAV, topNode->left));
			}
		}

		cout << "}\n";
	}
	class LeftRootRightIterator {
	private:
		stack<waiting<T>> operations;
	public:
		LeftRootRightIterator (node<T> *root)
		{
			if (root != nullptr)
			{
				operations.push(waiting<T>(OPER_TRAV, root));
				unwind();
			}
			//unwind осигурява, че на върха на стека
		//има операция за извличане или стекът е празен. Други
		//състояния на стека не са допустими.
		}
		void unwind()//trqbva da e v private 
		{
			//този метод извършва обхождането на чакащите за 
	//обхождане указатели към поддървета до момента, в който
	//на върха на стека попадне операция за извличане на елемент. Т.е.
	//обхождането се "развива" до достигане на следващя чакащ
	//за "отпечатване" връх
			if (operations.empty())
				return;

			waiting<T> topOperation = operations.top();
			node<T>* topNode = topOperation.second;

			while (!operations.empty() && topOperation.first != OPER_PRINT)
			{

				operations.pop();

				if (topNode->right != nullptr)
					/*{waiting<T> a;
				a.first = OPER_TRAV;
				a.second = topNode->right;
				operations.push(a);}
				vmesto dolniq red
				*/
				  operations.push(waiting<T>(OPER_TRAV, topNode->right));
				operations.push(waiting<T>(OPER_PRINT, topNode));
				if (topNode->left != nullptr)
					operations.push(waiting<T>(OPER_TRAV, topNode->left));

				topOperation = operations.top();
				topNode = topOperation.second;

			}

			//стекът е или празен или на върха му има операция PRINT
		}
		T operator * ()
		{
			//всички операции с итератора осигуряват, че на върха му
	//има операция за извличане или стекът е празен. Други
	//състояния на стека не са допустими.
	//Възелът на върха на стека е текущо посетения възел
	//при обхождането

			assert(!operations.empty());
			assert(operations.top().first == OPER_PRINT);
			assert(operations.top().second != nullptr);

			//сигурни сме, че на върха на стека
			//стои число "за печатане"

			return operations.top().second->data;

		}
		LeftRootRightIterator& operator ++ ()
		{

			assert(!operations.empty());
			//премахва се операцията за извличане, която е на върха на стека.
	//това довежда до продължаване на обхождането към следващите "части"
	//да дървото, или "активиране" на ичакващите под върха на стека операции
			operations.pop();
			//стекът се "доразвива" до достигане на следваща
	//операция за извличане
			unwind();
			return *this;
		}
		bool operator != (const LeftRootRightIterator &other)
		{

			if (operations.empty())
				return !other.operations.empty();

			if (other.operations.empty())
				return !operations.empty();

			//и двете са непразни

			return operations.top() != other.operations.top();
		}
	};
	LeftRootRightIterator end()
	{
		return LeftRootRightIterator(nullptr);
	}

	LeftRootRightIterator begin()
	{

		return LeftRootRightIterator(root);
	}
};
void testIterator()
{
	bt <int> t;

	t.addNode(59);
	t.addNode(23);
	t.addNode(68);
	t.addNode(190);
	t.addNode(41);
	t.addNode(67);

		bt<int>::LeftRootRightIterator it = t.begin();
		++it;
		++it;
		assert(*it == 59);;

		int count = 0;
		for (it = t.begin(); it != t.end(); ++it)
		{
			cout << "it=" << *it << "c=" << count << endl;
			count++;
		}


		assert(count == 6);
}
void testIterator2()
{
	bt <int> t;

	t.addNode(20);
	t.addNode(30);
	t.addNode(10);
	t.addNode(15);
	

	bt<int>::LeftRootRightIterator it = t.begin();
	++it;
	++it;
	assert(*it == 20);;

	int count = 0;
	for (it = t.begin(); it != t.end(); ++it)
	{
		cout << "it=" << *it << "c=" << count << endl;
		count++;
	}


	assert(count == 4);

}


int main()
{
	bt<int> t;
	t.addNode(20);
	t.addNode(10);
	t.addNode(30);
	t.addNode(15);
	t.prettyPrint();
	cout << endl;
	testIterator();
	testIterator2();
	t.iterationPrint();
	/*t.print();
	t.deleteElement(10);
	t.print();
	cout << t.isBinary();
	bt <int>t2;
	//t2 = t.insertNode(1000);//operator za prisvoqvane a ne copy construkotor
	//t2.print();
	*/
	return 0;
}
