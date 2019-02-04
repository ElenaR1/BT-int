#include <iostream>
#include <iomanip>
#include <vector>
#include <string.h>
#include <string>
#include <assert.h>

using namespace std;
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

template <class T>
class bt {
private:
	node<T> *root;
	void addNode(node<T>* &subTreeRoot,const T& x)
	{
		if (subTreeRoot == NULL)
		{
			subTreeRoot=new node<T>(x, NULL, NULL);
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
				return new node<T>(subTreeRoot->data, copyTree(subTreeRoot->left), insertNode(subTreeRoot->right,x));
				//vikam copyTree za STR->left t.k iskam sushtoto i nishto ne dobavqm
				//a za str->right obrazuvam novo durvo
			}
			else if (x < subTreeRoot->data)
			{
				return new node<T>(subTreeRoot->data, insertNode(subTreeRoot->left,x), copyTree(subTreeRoot->right));

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
	void deleteElement(node<T>* &subTreeRoot,const T& x)
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
			return;// v tetradkata kudeto sum razpisvala kak tochno stav asum obqsnila zashto trqbva return
			//s trieneto durvoto se promenq i sled kato e mahnat edin element e.g 10
			//funkciqta shte produlji da se izpulnqva za sshtoto durvo no bez elementa 10
			//ako mahame 10,10 shte stane 15 i shte vleze v sluchaq kudeto STR nqma nito 1 naslednik
		}
		if (subTreeRoot->right == NULL)
		{
			node<T> *delPtr = subTreeRoot;
			subTreeRoot = subTreeRoot->left;
			delPtr->left = NULL;//because we want to copmpletely disconnect this node from the tree
			delete delPtr;
			return;
			
		}
		//str->data suvpada s x, no str-<left !=null && str->right!= null, t.e ima poddurvo pod str
		else
		{
			T smallestInRightSubtree = minElement(subTreeRoot->right);
			subTreeRoot->data = smallestInRightSubtree;
			deleteElement(subTreeRoot->right, smallestInRightSubtree);
			cout << "the root node with data " << rootData << " was deleted and the new root contains data: " 
				<< subTreeRoot->data;
		}
	}
	bool isBinary(node<T>* subTreeRoot,int min,int max)
	{
		if (subTreeRoot == NULL)
		{
			return true;
		}
		if (subTreeRoot->data > min&&subTreeRoot->data < max
			&&isBinary(subTreeRoot->left,min,subTreeRoot->data)
			&& isBinary(subTreeRoot->right,subTreeRoot->data,max))
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
		addNode(root,x);
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
		return isBinary(root,INT_MIN,INT_MAX);
	}
};



int main()
{
	bt<int> t;
	t.addNode(20);
	t.addNode(10);
	t.addNode(30);
	t.addNode(15);
	t.print();
	t.deleteElement(10);
	t.print();
	cout << t.isBinary();
	bt <int>t2;
	//t2 = t.insertNode(1000);//operator za prisvoqvane a ne copy construkotor
	//t2.print();

	return 0;
}
