#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <string.h>
#include <string>
#include <assert.h>

using namespace std;
template <class T>
using mapFn = T(*)(const T&);
template <class T>
using predicat = bool(*)(const T&);
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
#define WAS_HERE 2

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
			//cout << "deleting the node containing the data " << subTreeRoot->data << endl;
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
	void preOrder(node<T>* subTreeRoot)
	{
		if (subTreeRoot == NULL)
		{
			return;
		}
		else
		{
			cout << subTreeRoot->data << " ";
			preOrder(subTreeRoot->left);
			preOrder(subTreeRoot->right);
		}
	}
	void inOrder(node<T>* subTreeRoot)
	{
		if (subTreeRoot == NULL)
		{
			return;
		}
		else
		{
			if (subTreeRoot->left != NULL)
			{
				inOrder(subTreeRoot->left);
			}
			cout << subTreeRoot->data << " ";
			if (subTreeRoot->right != NULL)
			{
				inOrder(subTreeRoot->right);
			}

		}
	}
	void postOrder(node<T>* subTreeRoot)
	{
		if (subTreeRoot == NULL)
		{
			return;
		}
		if (subTreeRoot->left != NULL)
		{
			postOrder(subTreeRoot->left);
		}

		if (subTreeRoot->right != NULL)
		{
			postOrder(subTreeRoot->right);
		}
		cout << subTreeRoot->data << " ";
	}
	void listTraverse(node<T>*subTreeRoot)
	{
		if (subTreeRoot == NULL)
		{
			return;
		}
		else if (subTreeRoot->left == NULL&&subTreeRoot->right == NULL)
		{
			cout << subTreeRoot->data << " ";
		}
		else
		{
			listTraverse(subTreeRoot->left);
			listTraverse(subTreeRoot->right);
		}
	}
	void boolPrint(node<T>* subTreeRoot, predicat<T> f)
	{
		if (subTreeRoot == NULL)
		{
			return;
		}
		else if (f(subTreeRoot->data))
		{
			cout << subTreeRoot->data << " ";
			boolPrint(subTreeRoot->left, f);
			boolPrint(subTreeRoot->right, f);
		}
		else
		{
			boolPrint(subTreeRoot->left, f);
			boolPrint(subTreeRoot->right, f);
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
		//cout << "destructor is called " << endl;
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
				operations.push(waiting<T>(OPER_TRAV, topNode->right));
				operations.push(waiting<T>(OPER_PRINT, topNode));
				operations.push(waiting<T>(OPER_TRAV, topNode->left));
			}
		}

		cout << "}\n";
	}
	void postOrderIterationPrint()//л-д-к
	{
		postOrderIterationPrint(root);
	}
	void postOrderIterationPrint(node<T> * subTreeRoot)
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
				operations.push(waiting<T>(OPER_PRINT, topNode));
				operations.push(waiting<T>(OPER_TRAV, topNode->right));
				operations.push(waiting<T>(OPER_TRAV, topNode->left));
			}
		}

		cout << "}\n";
	}
	void RootRightLeftIterationPrint()//к-д-л
	{
		RootRightLeftIterationPrint(root);
	}
	void RootRightLeftIterationPrint(node<T> * subTreeRoot)
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
				operations.push(waiting<T>(OPER_TRAV, topNode->left));
				operations.push(waiting<T>(OPER_TRAV, topNode->right));
				operations.push(waiting<T>(OPER_PRINT, topNode));
			}
		}

		cout << "}\n";
	}
	void listIterationPrint()
	{
		listIterationPrint(root);
	}
	void listIterationPrint(node<T>* subTreeRoot)
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
			else if (topNode != NULL)//tazi proverka si ni e zaduljitelna
			{
				if (topNode->right != nullptr)
				{
					operations.push(waiting<T>(OPER_TRAV, topNode->right));
				}
				if (topNode->left == NULL&&topNode->right == NULL)
				{
					operations.push(waiting<T>(OPER_PRINT, topNode));
				}
				if (topNode->left != nullptr)
				{
					operations.push(waiting<T>(OPER_TRAV, topNode->left));
				}
			}
		}
		cout << "}\n";
	}
	void boolIteration(predicat<T> f)
	{
		boolIteration(root, f);
	}

	void boolIteration(node<T>* subTreeRoot, predicat<T> f)
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
			else if (topNode != nullptr)
			{
				operations.push(waiting<T>(OPER_TRAV, topNode->right));

				if (f(topNode->data))
				{
					operations.push(waiting<T>(OPER_PRINT, topNode));
				}
				operations.push(waiting<T>(OPER_TRAV, topNode->left));
			}

		}
		cout << "}\n";
	}
	class RootRightLeftIterator {
	private:
		stack<waiting<T>> operations;
	public:
		RootRightLeftIterator(node<T> *root)
		{
			if (root != nullptr)
			{
				operations.push(waiting<T>(OPER_TRAV, root));
				unwind();
			}
			//a ako e NULL kakvo da pravib (NULL e naprimer kato izvikame end)
		}
		void unwind()
		{
			if (operations.empty())
				return;

			waiting<T> topOperation = operations.top();
			node<T>* topNode = topOperation.second;

			while (!operations.empty() && topOperation.first != OPER_PRINT)
			{

				operations.pop();
				if (topNode->left != nullptr)
					operations.push(waiting<T>(OPER_TRAV, topNode->left));
				if (topNode->right != nullptr)
					operations.push(waiting<T>(OPER_TRAV, topNode->right));
				operations.push(waiting<T>(OPER_PRINT, topNode));

				topOperation = operations.top();
				topNode = topOperation.second;

			}

			//стекът е или празен или на върха му има операция PRINT
		}
		T operator * ()
		{

			assert(!operations.empty());
			assert(operations.top().first == OPER_PRINT);
			assert(operations.top().second != nullptr);

			//сигурни сме, че на върха на стека
			//стои число "за печатане"

			return operations.top().second->data;

		}
		RootRightLeftIterator& operator ++ ()
		{

			assert(!operations.empty());
			operations.pop();
			unwind();
			return *this;
		}
		bool operator != (const RootRightLeftIterator &other)
		{

			if (operations.empty())
				return !other.operations.empty();

			if (other.operations.empty())
				return !operations.empty();

			//и двете са непразни

			return operations.top() != other.operations.top();
		}
	};

	RootRightLeftIterator beginRootRightLeftIterator()
	{
		return RootRightLeftIterator(root);
	}
	RootRightLeftIterator endRootRightLeftIterator()
	{
		return RootRightLeftIterator(nullptr);
	}


	class LeftRightRootIterator {//postorder
	private:
		stack <waiting<T>> operations;//ako beshe stack<int>
	public:
		LeftRightRootIterator(node<T>* root)
		{
			if (root != nullptr)
			{
				operations.push(waiting<T>(OPER_TRAV, root));//tuk shteshe da e op.push(int a)
															 //no tipa na elementite v stack-a e waiting, a (OPER_TRAV,root) e value-to kato v gorniq primer 'a'
				unwind();
			}
		}
		void unwind()
		{
			if (operations.empty())
			{
				return;
			}
			waiting<T> topOperation = operations.top();
			node<T>* topNode = topOperation.second;
			while (!operations.empty() && topOperation.first != OPER_PRINT)
			{
				operations.pop();
				operations.push(waiting<T>(OPER_PRINT, topNode));
				if (topNode->right != NULL)
				{
					operations.push(waiting<T>(OPER_TRAV, topNode->right));
				}
				if (topNode->left != NULL)
				{
					operations.push(waiting<T>(OPER_TRAV, topNode->left));
				}
				topOperation = operations.top();
				topNode = topOperation.second;
			}
		}
		T operator*()
		{
			assert(!operations.empty());
			assert(operations.top().first == OPER_PRINT);
			assert(operations.top().second != NULL);
			return operations.top().second->data;

		}
		LeftRightRootIterator& operator ++ ()
		{
			assert(!operations.empty());
			operations.pop();
			unwind();
			return *this;
		}
		bool operator != (const LeftRightRootIterator &other)
		{

			if (operations.empty())
				return !other.operations.empty();

			if (other.operations.empty())
				return !operations.empty();

			//и двете са непразни

			return operations.top() != other.operations.top();
		}

	};
	LeftRightRootIterator beginLeftRightRootIterator()
	{
		return LeftRightRootIterator(root);
	}
	LeftRightRootIterator endLeftRightRootIterator()
	{
		return LeftRightRootIterator(nullptr);
	}


	class LeftRootRightIterator {
	private:
		stack<waiting<T>> operations;
	public:
		LeftRootRightIterator(node<T> *root)
		{
			if (root != nullptr)
			{
				operations.push(waiting<T>(OPER_TRAV, root));
				unwind();
			}
			//a ako e NULL kakvo da pravib (NULL e naprimer kato izvikame end)
		}
		void unwind()
		{
			if (operations.empty())
				return;

			waiting<T> topOperation = operations.top();
			node<T>* topNode = topOperation.second;

			while (!operations.empty() && topOperation.first != OPER_PRINT)
			{

				operations.pop();

				if (topNode->right != nullptr)
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
			operations.pop();
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

	class listIterator {
	private:
		stack <waiting<T>> operations;
	public:
		listIterator(node<T>* root)
		{
			if (root != nullptr)
			{
				operations.push(waiting<T>(OPER_TRAV, root));
				unwind();
			}
		}
		void unwind()
		{
			if (operations.empty())
			{
				return;
			}
			waiting<T> topOperation = operations.top();
			node<T>* topNode = topOperation.second;
			while (!operations.empty() && topOperation.first != OPER_PRINT)
			{

				operations.pop();
				/*was here ne e nujno
				if (topOperation.first == WAS_HERE)
				{
				topOperation = operations.top();
				topNode = topOperation.second;
				operations.pop();
				}
				*/
				if (topNode->right != NULL)
				{
					operations.push(waiting<T>(OPER_TRAV, topNode->right));
				}
				if (topNode->left == NULL&&topNode->right == NULL)
				{
					operations.push(waiting<T>(OPER_PRINT, topNode));
				}
				if (topNode->left != NULL)
				{
					operations.push(waiting<T>(OPER_TRAV, topNode->left));
				}

				/*else
				{
				//cout << "was here " << topNode->data << endl;-nqkoi minavat po 2 puti ?
				operations.push(waiting<T>(WAS_HERE, topNode));
				}*/

				topOperation = operations.top();
				topNode = topOperation.second;
			}
		}
		T operator*()
		{
			assert(!operations.empty());
			assert(operations.top().first == OPER_PRINT);
			assert(operations.top().second != NULL);
			return operations.top().second->data;

		}
		listIterator& operator ++ ()
		{
			assert(!operations.empty());
			operations.pop();
			unwind();
			return *this;
		}
		bool operator != (const listIterator &other)
		{

			if (operations.empty())
				return !other.operations.empty();

			if (other.operations.empty())
				return !operations.empty();

			//и двете са непразни

			return operations.top() != other.operations.top();
		}

	};
	listIterator beginlistIterator()
	{
		return listIterator(root);
	}
	listIterator endlistIterator()
	{
		return listIterator(nullptr);
	}
	class boolIterator {
	private:
		stack <waiting<T>> operations;
		predicat<T> f;
	public:
		boolIterator(node<T> *root, predicat<T> pred)
		{
			f = pred;
			if (root != nullptr)
			{
				operations.push(waiting<T>(OPER_TRAV, root));
				unwind();
			}
			//a ako e NULL kakvo da pravim (NULL e naprimer kato izvikame end)
		}
		void unwind()
		{
			if (operations.empty())
			{
				return;
			}
			waiting<T> topOperation = operations.top();
			node<T>* topNode = topOperation.second;
			while (!operations.empty() && topOperation.first != OPER_PRINT)
			{
				operations.pop();
				/*if (topOperation.first == WAS_HERE)
				{
				waiting<T> topOperation = operations.top();
				node<T>* topNode = topOperation.second;
				operations.pop();
				}*/
				if (topNode->right != NULL)
				{
					operations.push(waiting<T>(OPER_TRAV, topNode->right));
				}
				if (f(topNode->data))
				{
					operations.push(waiting<T>(OPER_PRINT, topNode));
				}
				if (topNode->left != NULL)
				{
					operations.push(waiting<T>(OPER_TRAV, topNode->left));
				}
				topOperation = operations.top();
				topNode = topOperation.second;
				/*(else
				{
				operations.push(waiting<T>(WAS_HERE, topNode));
				}*/
			}
		}
		T operator*()
		{
			assert(!operations.empty());
			assert(operations.top().first == OPER_PRINT);
			assert(operations.top().second != NULL);
			return operations.top().second->data;
		}
		boolIterator& operator++()
		{
			assert(!operations.empty());
			operations.pop();
			unwind();
			return *this;
		}
		bool operator != (const boolIterator &other)
		{

			if (operations.empty())
				return !other.operations.empty();

			if (other.operations.empty())
				return !operations.empty();

			//и двете са непразни

			return operations.top() != other.operations.top();
		}
	};
	boolIterator beginboolIterator(predicat<T> pred)
	{
		return boolIterator(root, pred);
	}
	boolIterator endboolIterator(predicat<T> pred)
	{
		return boolIterator(nullptr, pred);
	}

	void postOrder()//л-д-к
	{
		postOrder(root);
	}
	void inOrder()//л-к-д
	{
		inOrder(root);
	}
	void preOrder()//к-л-д
	{
		preOrder(root);
	}
	void listTraverse()
	{
		listTraverse(root);
	}
	void boolPrint(predicat<T> f)
	{
		boolPrint(root, f);
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
	cout << endl;

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
	assert(*it == 20);

	int count = 0;
	for (it = t.begin(); it != t.end(); ++it)
	{
		cout << "it=" << *it << "c=" << count << endl;
		count++;
	}
	cout << endl;

	assert(count == 4);

}
void testLeftRightRootIterator()
{
	bt <int> t;

	t.addNode(20);
	t.addNode(30);
	t.addNode(10);
	t.addNode(15);
	bt<int>::LeftRightRootIterator it = t.beginLeftRightRootIterator();
	assert(*it == 15);
	++it;
	++it;
	assert(*it == 30);
	int count = 0;
	for (it = t.beginLeftRightRootIterator(); it != t.endLeftRightRootIterator(); ++it)
	{
		cout << "it= " << *it << "count= " << count << endl;
		count++;
	}
	cout << endl;
	assert(count == 4);

}

void testRootRightLeftIterator()
{
	bt <int> t;

	t.addNode(20);
	t.addNode(30);
	t.addNode(10);
	t.addNode(15);
	bt<int>::RootRightLeftIterator it = t.beginRootRightLeftIterator();
	assert(*it == 20);
	++it;
	++it;
	assert(*it == 10);
	int count = 0;
	for (it = t.beginRootRightLeftIterator(); it != t.endRootRightLeftIterator(); ++it)
	{
		cout << "it= " << *it << "count= " << count << endl;
		count++;
	}
	cout << endl;
	assert(count == 4);

}
void testlistIterator()
{
	bt <int> t;

	t.addNode(20);
	t.addNode(10);
	t.addNode(30);
	t.addNode(15);
	t.addNode(8);
	t.addNode(25);
	t.addNode(24);
	t.addNode(27);
	bt<int>::listIterator it = t.beginlistIterator();
	assert(*it == 8);
	++it;
	++it;
	assert(*it == 24);
	int count = 0;
	for (it = t.beginlistIterator(); it != t.endlistIterator(); ++it)
	{
		cout << "it= " << *it << "count= " << count << endl;
		count++;
	}
	cout << endl;
	assert(count == 4);

}
bool odd(const int& a)
{
	if (a % 2 != 0)
		return true;
	else
		return false;
}
void testboolItreator()
{
	cout << "test bool Iterator" << endl;
	bt <int> t;

	t.addNode(20);
	t.addNode(10);
	t.addNode(30);
	t.addNode(15);
	t.addNode(8);
	t.addNode(25);
	t.addNode(24);
	t.addNode(27);
	bt<int>::boolIterator it = t.beginboolIterator(odd);

	assert(*it == 15);
	++it;
	++it;
	assert(*it == 27);
	int count = 0;
	for (it = t.beginboolIterator(odd); it != t.endboolIterator(odd); ++it)
	{
		cout << "it= " << *it << "count= " << count << endl;
		count++;
	}
	cout << endl;
	assert(count == 3);
}

int main()
{
	bt<int> t;
	t.addNode(20);
	t.addNode(10);
	t.addNode(30);
	t.addNode(15);
	t.addNode(8);
	t.addNode(25);
	t.addNode(24);
	t.addNode(27);
	t.prettyPrint();
	cout << endl;
	testIterator();
	testIterator2();
	testLeftRightRootIterator();
	testRootRightLeftIterator();
	testlistIterator();
	testboolItreator();

	cout << "in order: ";
	t.inOrder();
	cout << endl;
	cout << "in order iteration: ";
	t.iterationPrint();
	cout << endl;
	cout << "pre order (root-left-right): ";
	t.preOrder();
	cout << endl;
	cout << "post order (left-right-root): ";
	t.postOrder();
	cout << endl;
	cout << "post order iteration: ";
	t.postOrderIterationPrint();
	cout << "root-right-left iteration: ";
	t.RootRightLeftIterationPrint();
	cout << "leaves: ";
	t.listTraverse();
	cout << endl;
	cout << "leaves iteration: ";
	t.listIterationPrint();
	cout << "nodes that fulfill the predicat: ";
	t.boolPrint(odd);
	cout << endl;
	cout << "nodes that fulfill the predicat Iteration: ";
	t.boolIteration(odd);
	t.boolIteration(NULL, odd);

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
