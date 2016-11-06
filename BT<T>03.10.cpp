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
	bool addPrivate(const T& newData, const char* trace, node<T>* &subTreeRoot)//? &
	{
		if (subTreeRoot == NULL)
		{
			if (strlen(trace) == 0)//The assert computer statement is analogous to the statement make sure
			{
				subTreeRoot = new node<T>(newData, NULL, NULL);//zashto T go postavqme tam ???
				return true;//subTreeRoot sochi kum tozi new node

							/*node<T>*n = new node;
							subTreeRoot = n;
							n->data = newData;
							n->left = NULL;
							n->right = NULL;*/
			}
		}
		if (strlen(trace) > 0)
		{
			if (trace[0] == 'L')
			{
				return addPrivate(newData, trace + 1, subTreeRoot->left);
			}
			if (trace[0] == 'R')
			{
				return addPrivate(newData, trace + 1, subTreeRoot->right);
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
	};
	bool memberPrivate(const T& searchedData, node<T>*subTreeRoot)const
	{
		if (subTreeRoot == NULL)
		{
			return false;//ako stigne do kraq i nqma takuv node shte sochi kum null -> nqma takuv node
						 //ili v sluchai che durvoto e prazno
		}
		else {
			if (subTreeRoot->data == searchedData)
			{
				return true;
			}
			else
			{
				return memberPrivate(searchedData, subTreeRoot->left) || memberPrivate(searchedData, subTreeRoot->right);
				// ako sa memberPrivate(searchedData, subTreeRoot->left);
				//memberPrivate(searchedData, subTreeRoot->right);ne stava

			}
			/*return subTreeRoot->data == searchedData || memberPrivate(searchedData, subTreeRoot->left) ||
			memberPrivate(searchedData, subTreeRoot->right);*/
		}
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
	void mapPrivate(mapFn<T> f, node<T>*subTreeRoot)
	{
		if (subTreeRoot == NULL)
		{
			return;
		}
		else
		{
			subTreeRoot->data = f(subTreeRoot->data);
			mapPrivate(f, subTreeRoot->left);
			mapPrivate(f, subTreeRoot->right);
		}
	}
	int countPrivate(node<T>* subTreeRoot)
	{

		/*int count = 0;
		if (subTreeRoot != NULL)
		{

		count=count+ countPrivate(subTreeRoot->left);
		count=count+ countPrivate(subTreeRoot->right);//ne raboti zashtoto vseki put count-a stava raven na 0
		}
		return count;*/
		if (subTreeRoot == NULL)
		{
			return 0;
		}
		else {
			if (subTreeRoot->left == NULL&& subTreeRoot->right == NULL)
			{
				return 1;
			}
			else
			{
				return (1 + (countPrivate(subTreeRoot->left) + countPrivate(subTreeRoot->right)));
			}
		}
	}
	int countEvensPrivate(node<T>* subTreeRoot)
	{
		if (subTreeRoot == NULL)
		{
			return 0;
		}
		else
		{
			if (subTreeRoot->left == NULL&&subTreeRoot->right == NULL && (subTreeRoot->data % 2 == 0))
			{
				return 1;
			}
			else
			{
				if (subTreeRoot->data % 2 == 0)
				{
					return (1 + (countEvensPrivate(subTreeRoot->left) + countEvensPrivate(subTreeRoot->right)));
				}
				else
				{
					return  (countEvensPrivate(subTreeRoot->left) + countEvensPrivate(subTreeRoot->right));
				}
			}
		}
	}
	int countOdds(bool(*pred)(const T&), node<T>*subTreeRoot)
	{
		if (subTreeRoot == NULL)
		{
			return 0;
		}
		else
		{
			if (subTreeRoot->left == NULL&&subTreeRoot->right == NULL&& pred(subTreeRoot->data))
			{
				return 1;
			}
			else
			{
				if (pred(subTreeRoot->data))
				{
					return (1 + (countOdds(pred, subTreeRoot->left) + countOdds(pred, subTreeRoot->right)));
				}
				else
				{
					return (countOdds(pred, subTreeRoot->left) + countOdds(pred, subTreeRoot->right));
				}
			}
		}
	}
	int max(int a, int b)
	{
		if (a > b)
		{
			return a;
		}
		else
		{
			return b;
		}
	}
	int min(int a, int b)
	{
		if (a < b)
		{
			return a;
		}
		else
		{
			return b;
		}
	}
	int findHeightPrivate(node<T>*subTreeRoot)//height=max depth
	{
		if (subTreeRoot == NULL)
		{
			return 0;
		}
		else
		{
			return max(findHeightPrivate(subTreeRoot->left), findHeightPrivate(subTreeRoot->right)) + 1;
		}
	}
	int findShortestHeightPrivate(node<T>*subTreeRoot)//height=max depth
	{
		if (subTreeRoot == NULL)
		{
			return 0;
		}
		else
		{
			return min(findShortestHeightPrivate(subTreeRoot->left), findShortestHeightPrivate(subTreeRoot->right)) + 1;
		}
	}

	int findLevelPrivate(T searchedData, node<T>* subTreeRoot, int level)
	{
		if (subTreeRoot == NULL)
		{
			return 0;
		}
		else
		{
			if (subTreeRoot->data == searchedData)
			{
				return level;
			}
			else
			{
				int downLevel = findLevelPrivate(searchedData, subTreeRoot->left, level + 1);
				if (downLevel != 0)
				{
					return downLevel;
				}
				else
				{
					downLevel = findLevelPrivate(searchedData, subTreeRoot->right, level + 1);
				}
				return downLevel;
			}
		}
	}

	int countLeavesPrivate(node<T>*subTreeRoot)
	{
		if (subTreeRoot == NULL)
		{
			return 0;
		}
		else
		{
			if (subTreeRoot->left == NULL&&subTreeRoot->right == NULL)
			{
				return 1;
			}
			else
			{
				return (countLeavesPrivate(subTreeRoot->left) + countLeavesPrivate(subTreeRoot->right));
			}
		}
	}
	int maxLeafPrivate(node<T>*subTreeRoot)
	{
		if (subTreeRoot == NULL)
		{
			return -10;//tova ako vleze v max vinagi shte e po-malko ot drugoto s koeto go sravnqvame i nqma da vliqe
					   //shte e po-malko t.k durvoto ni ima polojitelni stoinosti
		}
		else
		{
			if (subTreeRoot->left == NULL&&subTreeRoot->right == NULL)
			{
				return subTreeRoot->data;
			}
			else
			{
				return max(maxLeafPrivate(subTreeRoot->left), maxLeafPrivate(subTreeRoot->right));
			}
		}
	}
	T& getElementPrivate(const char*trace, node<T>* subTreeRoot)
	{
		if (strlen(trace) == 0)
		{
			return subTreeRoot->data;
		}
		else if (strlen(trace)>0)
		{
			if (trace[0] == 'L')
			{
				return getElementPrivate(trace + 1, subTreeRoot->left);
			}
			if (trace[0] == 'R')
			{
				return getElementPrivate(trace + 1, subTreeRoot->right);
			}
		}
		else//NE RABOTI
		{
			cout << "there is no node at that position" << endl;
		}
	}

	string findTracePrivate(node<T>* subTreeRoot, const T x, string trace)
	{
		if (subTreeRoot == NULL)
		{
			return "?";
		}
		else
		{
			if (subTreeRoot->data == x)
			{
				return trace;
			}
			else
			{
				string a = findTracePrivate(subTreeRoot->left, x, trace + "L");
				if (a != "?")
				{
					return a;
				}
				else
				{
					a = findTracePrivate(subTreeRoot->right, x, trace + "R");
				}
				return a;
			}
		}
	}
	/*void copy(node<T>* otherNode, node<T>* ourNode)
	{
		if (otherNode == NULL)
		{
			ourNode == NULL;
		}
		else
		{
			ourNode = new node<T>(otherNode->data, NULL, NULL);
			copy(otherNode->left, ourNode->left);
			copy(otherNode->right, ourNode->right);
		}
	}*/
	static node<T>* copyTree(const node<T>* subTreeRoot)//static t.k ne se polzva ot chlen dannite na klasa i ne promenq nishto v
		//durvoto. Print sushto moje da e static po sushtata logika. Vsichko koeto vzima node moje da e static		
	{
		if (subTreeRoot == NULL)
		{
			return NULL;
		}
		else
		{
			return new node<T>(subTreeRoot->data, copyTree(subTreeRoot->left), copyTree(subTreeRoot->right));
			//ako e return new node<T>(STR->data,STR->left,STR->right) taka kopirame samo korena a drugite node-ove
			//si ostavat ot staroto durvo
		}
	}
	void listLeavesPrivate(node<T>* subTreeRoot, vector<T> &v)
	{
		if (subTreeRoot == NULL)
		{
			return;
		}
		/*else//tova e ako iskame ne samo listata a vsichki nodes
		{
		v.push_back(subTreeRoot->data);
		listLeavesPrivate(subTreeRoot->left, v);
		listLeavesPrivate(subTreeRoot->right, v);
		}*/
		else
		{
			if (subTreeRoot->left == NULL&& subTreeRoot->right == NULL)
			{
				v.push_back(subTreeRoot->data);
			}
			if (subTreeRoot->left != NULL)
			{
				listLeavesPrivate(subTreeRoot->left, v);
			}
			if (subTreeRoot->right != NULL)
			{
				listLeavesPrivate(subTreeRoot->right, v);
			}
		}
	}
	void levelVector(node<T>* subTreeRoot, vector<T> &v, int k, int level)
	{
		if (subTreeRoot == NULL)
		{
			return;
		}
		else
		{
			if (k == level)
			{
				v.push_back(subTreeRoot->data);
			}
			else
			{
				levelVector(subTreeRoot->left, v, k, level + 1);
				levelVector(subTreeRoot->right, v, k, level + 1);
			}
		}
	}
	void serializePrivate(node<T>* subTreeRoot, ostream& out)
	{
		if (subTreeRoot == NULL)
		{
			out << "()";
		}
		else
		{
			out << "(";
			out << subTreeRoot->data;
			serializePrivate(subTreeRoot->right, out);
			serializePrivate(subTreeRoot->left, out);
			out << ")";
		}

	}
	bool isCompletePrivate()
	{
		int c = countPrivate(root);
		int h = findHeightPrivate(root);
		if (c == pow(2, h) - 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	T& findElement(int i, node<T>*subTreeRoot, int pos)
	{
		if (pos == i&&subTreeRoot != NULL)
		{
			return subTreeRoot->data;
		}
		if (subTreeRoot == NULL)
		{
			T a = 0;
			return a;
		}
		T n = findElement(i, subTreeRoot->left, (pos * 2 + 1));
		if (n != 0)
		{
			return n;
		}
		else
		{
			n = findElement(i, subTreeRoot->right, (pos * 2 + 2));
		}
		return n;
	}
	void insertBotPrivate(node<T>* &subTreeRoot, const T& addData)
		//ako ne e po referencia nishto nqma da se otpechata zashtoto pri root-a nqma nishto da se smeni i shte si sochi kum NULL
	{
		if (subTreeRoot == NULL)
		{
			subTreeRoot = new node<T>(addData, NULL, NULL);
		}
		else
		{
			if (addData < subTreeRoot->data)
			{
				insertBotPrivate(subTreeRoot->left, addData);
			}
			else if (addData>subTreeRoot->data)
			{
				insertBotPrivate(subTreeRoot->right, addData);
			}
		}
	}
	node<T>* insertedBotPrivate(node<T>* subTreeRoot, const T& addData)
	{
		if (subTreeRoot == NULL)
		{
			return new node<T>(addData, NULL, NULL);
		}
		else
		{
			if (addData < subTreeRoot->data)
			{
				return new node<T>(subTreeRoot->data, insertedBotPrivate(subTreeRoot->left, addData), copyTree(subTreeRoot->right));
			}
			else if (addData>subTreeRoot->data)
			{
				return new node<T>(subTreeRoot->data, copyTree(subTreeRoot->left), insertedBotPrivate(subTreeRoot->right, addData));
				//vikam copyTree za STR->left t.k iskam sushtoto i nishto ne dobavqm
				//a za str->right obrazuvam novo durvo
			}
			
		}
	}

	T minElementPrivate(node<T>* subTreeRoot)const
	{
		assert(subTreeRoot != NULL);
		node<T>* current = subTreeRoot;
		while (current->left != NULL)
		{
			current = current->left;
		}
		return current->data;
	}	
	void deleteElement(node<T> *&subTreeRoot, const T&x)
	{
		T rootData = subTreeRoot->data;
		//триене от празно дърво
		if (subTreeRoot == NULL)
		{
			return;
		}
		//триене от листо
		if (subTreeRoot->data == x &&
			subTreeRoot->left == NULL &&
			subTreeRoot->right == NULL)

		{
			delete subTreeRoot;
			subTreeRoot = NULL;
			return;
		}

		//триене от лявото поддърво
		if (x < subTreeRoot->data)
		{
			deleteElement(subTreeRoot->left, x);
			return;
		}

		//триене от дясното поддърво
		if (x > subTreeRoot->data)
		{
			deleteElement(subTreeRoot->right, x);
			return;
		}

		//вече сме сигурни, че трием корена!
		//освен това сме сигурни, че корена има ПОНЕ ЕДИН
		//наследник

		//триене на корен само с 1 наследник
		if (subTreeRoot->right == NULL)
		{
			node<T> *delPtr = subTreeRoot;
			subTreeRoot = subTreeRoot->left;
			delPtr->left = NULL;//because we want to copmpletely disconnect this node from the tree
			delete delPtr;
			return;
		}

		//триене на корен само с 1 наследник
		//този случй може да не се разглежда
		if (subTreeRoot->left == NULL)
		{
			node<T> *delPtr = subTreeRoot;
			subTreeRoot = subTreeRoot->right;
			delPtr->right = NULL;
			delete delPtr;
			return;
		}


		//триене на корена
		//вече сме сигурни, че корена има точно два наследника
		else {
			T smallestInRightSubtree = minElementPrivate(subTreeRoot->right);
			subTreeRoot->data = smallestInRightSubtree;
			deleteElement(subTreeRoot->right, smallestInRightSubtree);
			cout << "the root node with data " << rootData << " was deleted and the new root contains data: " << subTreeRoot->data;
		}
	}
	
	bool isBinaryPrivate(node<T>* subTreeRoot,int minData, int maxData)
	{
		if (subTreeRoot == NULL)
		{
			return true;
		}
		if (subTreeRoot->data > minData&&subTreeRoot->data < maxData
			&& isBinaryPrivate(subTreeRoot->left, minData, subTreeRoot->data)
			&& isBinaryPrivate(subTreeRoot->right, subTreeRoot->data, maxData))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void changeDataPrivate(node<T>* &subTreeRoot)
	{
		if (subTreeRoot == NULL)
		{
			return;
		}
			int n = countPrivate(subTreeRoot);
			subTreeRoot->data =n;
			if (subTreeRoot->left != NULL)
			{
				changeDataPrivate(subTreeRoot->left);
			}
			if (subTreeRoot->right != NULL)
			{
				changeDataPrivate(subTreeRoot->right);
			}
	}
	
public:
	// i tova si raboti
	/*bt(const bt<T> &other)
		:root(nullptr)
	{
		cout << "copy constructor is called" << endl;
		copy(other.root, root);//2riq root e nashiq
	}*/
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
	void add(const T& newData, const char* trace)// zashto po psevdonim
	{
		addPrivate(newData, trace, root);
		//	return*this;
	}
	bt()
	{
		root = NULL;
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
	//checks if there is a node with the given data
	bool member(const T& searchedData)
	{
		return memberPrivate(searchedData, root);
	}
	~bt()
	{
		deleteAll(root);
	}
	void map(mapFn<T> f)
	{
		mapPrivate(f, root);
	}
	int count()
	{
		return countPrivate(root);
	}
	int countEvens()
	{
		return countEvensPrivate(root);
	}

	int searchCount(bool(*pred)(const T&))
	{
		return countOdds(pred, root);
	}
	int findHeight()
	{
		return findHeightPrivate(root);
	}
	int shortestHeight()
	{
		return findShortestHeightPrivate(root);
	}
	int findLevel(T searchedData)
	{
		return findLevelPrivate(searchedData, root, 1);
	}
	int countLeaves()
	{
		return countLeavesPrivate(root);
	}
	int maxLeaf()
	{
		return maxLeafPrivate(root);
	}
	T& getElement(const char*trace)
	{
		return getElementPrivate(trace, root);
	}
	string findTrace(const T x)
	{
		string trace = "";
		return findTracePrivate(root, x, trace);
	}
	vector<T> listLeaves()
	{
		vector<T> v;
		listLeavesPrivate(root, v);
		return v;
	}
	vector<T> level(int k)
	{
		vector<T> v;
		levelVector(root, v, k, 1);
		return v;
	}
	int numberOfElementsAtALevel(int k)
	{
		vector<T> v;
		levelVector(root, v, k, 1);
		return (v.size()+1);
	}
	
	
	void seriazlize(ostream& out)
	{
		serializePrivate(root, out);
		cout << endl;
	}
	bool isComplete()
	{
		return isCompletePrivate();
	}
	T& operator[](int index)
	{
		return findElement(index, root, 0);
	}
	bt& insertBOT(const T& addData)//vseki put vmukvame v staroto durvo
	{
		insertBotPrivate(root, addData);	
		return *this;
	}
	bt insertedBOT(const T& addData)//tuk vseki put kato dobavqme pravim novo durvo
	{
		bt<T> result;
		result.root = insertedBotPrivate(root, addData);
		return result;
	}
	T minElement()const
	{
		return minElementPrivate(root);
	}
	void deleteElement(const T& removeData)
	{
		deleteElement(root, removeData);
	}
	//3 zad 3 zzs
	bool isBinary()
	{
		
		return isBinaryPrivate(root,INT_MIN,INT_MAX);
	}
	//4 zad 3 zzs
	void changeData()
	{
		changeDataPrivate(root);
	}
	//5 zad 3 zzs
	int evaluate()
	{
		return evaluate(root);
	}
	int evaluate(node<T>* subTreeRoot)
	{
		
		if (subTreeRoot == NULL)
		{
			return 0;
		}
		if (subTreeRoot->left == NULL&&subTreeRoot->right == NULL)
		{
			
			return subTreeRoot->data - '0';
		}
		else
		{
			int x = evaluate(subTreeRoot->left);
			int y = evaluate(subTreeRoot->right);
			return applyOp(subTreeRoot->data, x, y);
		}
	}
	int applyOp(char op,int a,int b)
	{
		if (op == '+')
		{
			return a + b;
		}
		 if (op == '-')
		{
			return a - b;
		}
		if (op == '*')
		{
			return a * b;
		}
		if (op == '/')
		{
			return a / b;
		}
	}
	void testNodes(node<T>* subTreeRoot)
	{
		if (subTreeRoot->left == NULL&&subTreeRoot->right == NULL)
		{
			assert(isdigit(subTreeRoot->data));
		}
		else
		{
			assert(subTreeRoot->data == '+' || subTreeRoot->data == '-' || subTreeRoot->data == '/' || subTreeRoot->data == '*');
		}
	}
	void testAssignment()
	{
		assert(this->isComplete());
		testNodes(root);
	}
};

bool odd(const int& a)
{
	if (a % 2 != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int plusOne(const int& i)
{
	return i + 1;
}
bool pred(int a)
{
	if (a % 2 == 0)
	{
		return true;
	}
	else
		return false;
}
template <typename T>
void printVector(vector<T> &v)
{
	cout << "vector: ";
	for (size_t i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}

int main()
{
	/*bt<int> t;
	t.add(10, "");
	t.add(8, "L");
	t.add(14, "R");
	t.add(9, "LR");
	
	t.print();
	cout << endl;
	t.prettyPrint();
	t.changeData();
	t.prettyPrint();

	printVector(t.listLeaves());
	printVector(t.level(2));
	cout << t[4] << endl;
	cout << t.isBinary() << endl;

	cout << t.isComplete() << endl;

	t.seriazlize(cout);

	cout << t.member(14) << endl;
	cout << endl;
	cout << "Number of nodes:" << t.count() << endl;
	cout << "Number of even numbers: " << t.countEvens() << endl;
	cout << "Number of odd numbers: " << t.searchCount(odd) << endl;
	cout << "Height of the tree: " << t.findHeight() << endl;
	cout << "Shortest height of the tree: " << t.shortestHeight() << endl;
	cout << "This node is at level: " << t.findLevel(14) << endl;
	cout << "Number of leaves: " << t.countLeaves() << endl;
	cout << "MaxLeaf: " << t.maxLeaf() << endl;
	cout << "The data in this position is: " << t.getElement("L") << endl;
	cout << "the trace is: " << t.findTrace(12) << endl;

	t.map(plusOne);
	cout << "after mapping: ";
	t.print();
	cout << "Number of odd numbers: " << t.searchCount(odd) << endl;

	bt<int> t3;
	t3 = t;//operator=

	bt<int> t2 = t;//cpy constr
	t2.prettyPrint();*/
	
	

	/*bt<int> binaryt;
	binaryt.insertBOT(56);
	binaryt.insertBOT(23);
	binaryt.insertBOT(68);
	binaryt.insertBOT(190);
	binaryt.insertBOT(41);
	binaryt.insertBOT(60);
	binaryt.insertBOT(65);
	binaryt.insertBOT(59);
	cout << endl;
	cout << binaryt.minElement() << endl;
	binaryt.deleteElement(56);
	binaryt.prettyPrint();*/

	/*cout << endl;
	bt<int> tt;
	tt.insertedBOT(20);
	tt.insertedBOT(10);
	tt.insertedBOT(30);
	tt.insertedBOT(5);
	//tt.prettyPrint();*/

	bt<char> expressionTree;
	expressionTree.add('+', "");
	expressionTree.add('*', "L");
	expressionTree.add('+', "R");
	expressionTree.add('2', "LL");
	expressionTree.add('3', "LR");
	expressionTree.add('5', "RL");//ako e samo char ne moga da zpaisha 15 a samo ednocfreni chisla
	expressionTree.add('0', "RR");
	//expressionTree.add('0', "RRL"); ako go napravq tova se izpisva ssertion failed blagodarenie na testAssignment
	expressionTree.testAssignment();
	cout<<"the result after evaluating is: " << expressionTree.evaluate() << endl;



	/*char*s = "LRL";
	cout << s << endl;
	cout << (s+1)[0] << endl;
	cout << *(s + 1) << endl;
	cout << s[1] << endl;*/


	return 0;
}
