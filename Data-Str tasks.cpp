1.void printReverse()
	{
		cout << "Reverse print: " << endl;
		printReverse(head);
	}
	void printReverse(node<T>* head)
	{
		
		if (head == NULL)
			return;
		printReverse(head -> next);
		cout << head->data << " ";
	}
  
  //2 Check if two given sets are disjoint.
  bool disjointt(int*a,int sizea,int sizeb, int*b)
{
	for (size_t i = 0; i < sizea; i++)
	{
		for (size_t j = 0; j < sizeb; j++)
		{
			if (a[i] == b[j])
				return false;
		}
	}
	// If no element of set1 is present in set2
	return true;
}

int main()
{
	int a[3] = { 1,2,3 };
	int b[3] = { 4,2,5 };
	cout << disjointt(a, 3, 3, b) << endl;
  

	
#include <iostream>
#include <map>
using namespace std;

bool func(int*a,int*b,int n1,int n2)
{
    map<int,bool> funcmap;
    for (int i=0;i<n1;i++)
    {
        funcmap[a[i]]=true;
    }
     for (int i=0;i<n2;i++)
    {
        if(funcmap.find(b[i])!=funcmap.end())//ako vurne funcmap.end() zmachi ne go e nameril
        {
            return false;
        }
    }
    return true;
}

int main()
{

    int a[4]={1,2,5,7};
    int b[5]={10,9,0,4,6};
    cout<<func(a,b,4,5);

    return 0;
}

  
  4//Implement queue using two stacks.
  #include <iostream>
#include <stack>
using namespace std;
template <typename T>
class queue {
private:
	stack<T>s1;
	stack<T>s2;
public:
	void enque(T elem)
	{
		s1.push(elem);//1,2,3
	}
	void deque()//=pop t.e trqbva da maha 1viq element ot opashkata
	{
		while (!s1.empty())
		{
			s2.push(s1.top());//3,2,1
			s1.pop();
		}
		//T fst = s2.top();
		s2.pop();//mahame 1 po tozi nachin
		while (!s2.empty())
		{
			s1.push(s2.top());//2,3
			s2.pop();
		}
	}
	T front()
	{
		while (!s1.empty())
		{
			s2.push(s1.top());//3,2,1
			s1.pop();
		}
		T fst = s2.top();
		while (!s2.empty())
		{
			s1.push(s2.top());//1,2,3
			s2.pop();
		}
		return fst;
	}
	T last()
	{
		return s1.top();
	}
	void print()
	{
		cout << "\nDisplaying the queue :-\n";
		while (!s1.empty()) {
			s2.push(s1.top());
			s1.pop();
		}
		while (!s2.empty()) {
			cout << s2.top() << " ";
			s1.push(s2.top());
			s2.pop();
		}
		cout << endl;
	}
};

int main()
{
	queue<int> q;
	for (size_t i = 0; i < 5; i++)
	{
		q.enque(i);
	}
	q.print();
	cout << q.front() << endl;
	cout << q.last() << endl;
	q.deque();
	q.print();
	return 0;
}

	
	

	
#include <iostream>
#include <iomanip>
#include <vector>
#include <string.h>
#include <string>
#include <assert.h>


using namespace std;
template <typename T>
using mapFn = T(*)(const T&);

template <typename T>
struct node
{
	T data;
	node<T>* left;
	node<T>* right;
	node() :left(nullptr), right(nullptr) {}
	node(const T d, node<T> *l, node<T> *r) :data(d), left(l), right(r) {}
};
template <typename T>
class tree
{
private:
	node<T>* root;
	void add(T x, char*trace, node<T>* &subTreeRoot)
	{
		if (subTreeRoot == NULL)
		{
			if (strlen(trace) == 0)
			{
				subTreeRoot = new node<T>(x, NULL, NULL);

			}
		}
		if (strlen(trace) > 0)
		{
			if (trace[0] == 'L')
			{
				 add(x, trace + 1, subTreeRoot->left);
			}
			if (trace[0] == 'R')
			{
				 add(x, trace + 1, subTreeRoot->right);
			}
		}
	}
	void print(node<T>* subTreeRoot)
	{
		if (subTreeRoot == NULL) return;
		else
		{
			cout << subTreeRoot->data << " ";
			print(subTreeRoot->left);
			print(subTreeRoot->right);
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
	bool member(const T& x, node<T>* subTreeRoot)
	{
		if (subTreeRoot == NULL) return false;
		else
		{
			if (subTreeRoot->data == x) return true;
			else
			{
				return member(x, subTreeRoot->left) || member(x, subTreeRoot->right);
			}
		}
	}
	void deleteAll(node<T>*subTreeRoot)
	{
		if (subTreeRoot == NULL) return;
		else
		{
			deleteAll(subTreeRoot->left);
			deleteAll(subTreeRoot->right);
			delete subTreeRoot;
		}
	}
	void map(mapFn<T> f, node<T>*subTreeRoot)
	{
		if (subTreeRoot == NULL) return;
		else
		{
			subTreeRoot->data = f(subTreeRoot->data);
			map(f, subTreeRoot->left);
			map(f, subTreeRoot->right);
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
	void longestSequence(node<T>* subTreeRoot, T expected, int curLen, int &len)
	{
		if (subTreeRoot == NULL) return;

		if (subTreeRoot->data == expected)
			curLen++;
		else
			curLen = 1;

		len = max(len, curLen);

		cout << len << " ";
		if (subTreeRoot->right)
			longestSequence(subTreeRoot->right, subTreeRoot->data + 1, curLen, len);

		if (subTreeRoot->left)
			longestSequence(subTreeRoot->left, subTreeRoot->data + 1, curLen, len);
	}
public:
	tree() :root(nullptr) {}
	void add(T x, char*trace)
	{
		 add(x, trace, root);
	}
	void print()
	{
		print(root);
	}
	void prettyPrint()
	{
		prettyPrintPrivate(root, 1);
	}
	bool member(const T& x)
	{
		return member(x, root);
	}
	~tree()
	{
		deleteAll(root);
	}
	void map(mapFn<T> f)
	{
		map(f, root);
	}
	int findHeight()
	{
		return findHeightPrivate(root);
	}
	//Find longest consecutive sequence in binary tree.
	int longestSequence()
	{
		int len = 0;
		longestSequence(root, root->data, 0, len);
		return len;
	}
	//2. Construct a binary tree from given postorder and inorder traversals.
	node<T>* buildTree(int*in, int*post, int start, int end, int index)
	{
		if (start > end) return NULL;
		node<T>* newNode = new node<T>(post[index], NULL, NULL);//vzima posledniq element na postorder-a
		index--;
		//if this node has no children
		if (start == end)
			return newNode;
		/* Else find the index of this node in Inorder
		traversal */
		int itindex = search(in, start, end, newNode->data);

		newNode->right = buildTree(in, post, itindex + 1, end, index);
		newNode->left = buildTree(in, post, start, itindex - 1, index);
	}
	node<T>* buildTree(int*in, int*post, int n)
	{
		int index = n - 1;
		return buildTree(in, post, 0, n - 1, index);

	}
	/* Function to find index of value in arr[start...end]
	The function assumes that value is postsent in in[] */
	int search(int arr[], int strt, int end, int value)
	{
		int i;
		for (i = strt; i <= end; i++)
		{
			if (arr[i] == value)
				break;
		}
		return i;
	}
	bool isLeaf(node<T>* subTreeRoot,T data)
	{
        if(subTreeRoot->data==data&&subTreeRoot->left==NULL&&subTreeRoot->right==NULL)
            return true;
        else if(subTreeRoot->left!=NULL)
        {
            return isLeaf(subTreeRoot->left,data);
        }
        else if(subTreeRoot->right!=NULL)
        {
            return isLeaf(subTreeRoot->right,data);
        }

	}
	bool isLeaf(T data)
	{
	    return isLeaf(root,data);
	}
	void sumofAllLeft(node<T>* subTreeRoot,int& sum,bool flag)
	{
        if(subTreeRoot->left==NULL&&subTreeRoot->right==NULL&&flag==1)
        {
           sum+=subTreeRoot->data;
        }

           if(subTreeRoot->left!=NULL)
            sumofAllLeft(subTreeRoot->left,sum,1);
              if(subTreeRoot->right!=NULL)
            sumofAllLeft(subTreeRoot->right,sum,0);
	}
	int sumofAllLeft2(node<T>* subTreeRoot,bool flag)
	{
	    if(subTreeRoot==NULL) return 0;
	    if(subTreeRoot->left==NULL&&subTreeRoot->right==NULL&&flag==1)
        {
           return subTreeRoot->data;
        }

          return  sumofAllLeft2(subTreeRoot->left,1)+sumofAllLeft2(subTreeRoot->right,0);
	}
	int sumofAllLeft2()
	{

        cout<<"sum of all left2: "<<endl;
	    return sumofAllLeft2(root,1);

	}

	int sumofAllLeft()
	{
	    int sum=0;
        cout<<"sum of all left: "<<endl;
	     sumofAllLeft(root,sum,1);
	    return sum;
	}

};
int main() {
	tree<int> t;
	t.add(6, "");
	t.add(9, "R");
	t.add(10, "RR");
	t.add(5, "RRL");
	t.add(11, "RRR");
	t.add(7, "L");
	t.prettyPrint();
	cout << endl;
	cout << t.longestSequence()<<endl;
    cout<<t.isLeaf(7)<<endl;
    cout<<t.isLeaf(9)<<endl;
    cout<<t.sumofAllLeft()<<endl;
     cout<<t.sumofAllLeft2()<<endl;
	int inOrder[] = { 4,2,5,1,6,7,3,8 };
	int postOrder[] = { 4,5,2,6,7,8,3,1 };
	tree<int> ord;
	ord.buildTree(inOrder, postOrder, 8);

	return 0;
}

	
	
	
	
	
	
	
//Tree
#include <iostream>
#include <iomanip>
#include <vector>
#include <string.h>
#include <string>
#include <assert.h>

using namespace std;
template <typename T>
using mapFn = T(*)(const T&);
template<typename T>
struct node {
	T data;
	node<T>* left;
	node<T>* right;
	node() :left(nullptr), right(nullptr) {}
	node(const T d, node<T> *l, node<T> *r) :data(d), left(l), right(r) {}
};

template <typename T>
class tree
{
private:
	node<T>*root;
	void add(T x, char*trace, node<T>* &subTreeRoot)
	{
		if (subTreeRoot == NULL)
		{
			if (strlen(trace) == 0)
				subTreeRoot = new node<T>(x, NULL, NULL);
		}
		if (strlen(trace) > 0)
		{
			if (trace[0] == 'L')
				add(x, trace + 1, subTreeRoot->left);
			if (trace[0] == 'R')
				add(x, trace + 1, subTreeRoot->right);
		}
	}
	void print(node<T>* subTreeRoot)
	{
		if (subTreeRoot == NULL) return;
		else
		{
			cout << subTreeRoot->data << " ";
			print(subTreeRoot->left);
			print(subTreeRoot->right);
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
	bool member(const T& x, node<T>* subTreeRoot)
	{
		if (subTreeRoot == NULL) return false;
		else
		{
			if (subTreeRoot->data == x) return true;
			else
			{
				return member(x, subTreeRoot->left) || member(x, subTreeRoot->right);
			}
		}
	}
	void deleteAll(node<T>*subTreeRoot)
	{
		if (subTreeRoot == NULL) return;
		else
		{
			deleteAll(subTreeRoot->left);
			deleteAll(subTreeRoot->right);
			delete subTreeRoot;
		}
	}
	void map(mapFn<T> f, node<T>*subTreeRoot)
	{
		if (subTreeRoot == NULL) return;
		else
		{
			subTreeRoot->data = f(subTreeRoot->data);
			map(f, subTreeRoot->left);
			map(f, subTreeRoot->right);
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
	bool isLeaf(node<T>*subTreeRoot, T x)
	{
		if (subTreeRoot == NULL)
			return false;
		if (subTreeRoot->data == x && subTreeRoot->left == NULL && subTreeRoot->right == NULL)
		{
			return true;
		}
		else
		{
			return isLeaf(subTreeRoot->left, x) || isLeaf(subTreeRoot->right, x);
		}
		/*
		*/
	}
	
public:
	tree():root(nullptr){}
	void add(T x, char*trace)
	{
		add(x, trace, root);
	}
	void print()
	{
		print(root);
	}
	void prettyPrint()
	{
		prettyPrintPrivate(root, 1);
	}
	bool member(const T& x)
	{
		return member(x, root);
	}
	~tree()
	{
		deleteAll(root);
	}
	void map(mapFn<T> f)
	{
		map(f, root);
	}
	int findHeight()
	{
		return findHeightPrivate(root);
	}
	bool isLeaf(T x)
	{
		return isLeaf(root,x);
	}
	void sumofAllLeft(node<T>* subTreeRoot,int&sum,bool flag)
	{
		if (subTreeRoot == NULL) return;
		if (subTreeRoot->left == NULL&&subTreeRoot->right == NULL&&flag)
		{
			sum += subTreeRoot->data;
		}
		else
		{
			sumofAllLeft(subTreeRoot->left, sum, 1);
			sumofAllLeft(subTreeRoot->right, sum, 0);
		}
	}

	int sumofAllLeft()
	{
		int sum = 0;
		sumofAllLeft(root, sum, 1);
		return sum;
	}
	int sumofAllLeft2(node<T>* subTreeRoot, int&sum, bool flag)
	{
		if (subTreeRoot == NULL) return 0;
		if (subTreeRoot->left == NULL&&subTreeRoot->right == NULL&&flag)
		{
			return subTreeRoot->data;
		}
		else
		{
			sumofAllLeft2(subTreeRoot->left,  1)+sumofAllLeft2(subTreeRoot->right, 0);
		}
	}

	int sumofAllLeft2()
	{
		cout << "sum of all left2: " << endl;
		return sumofAllLeft2(root, 1);
	}
	void longestSequence(node<T>*subTreeRoot,T expected,int curlen, int &maxLen)
	{
		if (subTreeRoot->data == expected)
			curlen++;
		else
			curlen = 1;

		maxLen = max(len, maxLen);
		longestSequence(subTreeRoot->right, subTreeRoot->data + 1, curlen, maxLen);//tova se izvurshva 1vo i maxLen stava 3

		longestSequence(subTreeRoot->left, subTreeRoot->data + 1, curlen, maxLen);//tuk shte e taka: maxLen=max(1,3) i pak
		//shte si e 3/ Zashtoto sme podali  longestSequence(subTreeRoot->left, subTreeRoot->data + 1, 3, 3); curlen stava 1 
		//no maxLen si ostava 3	
	}
	int longestSequence()
	{
		int len = 0;
		return longestSequence(root,root->data,0, len);
		return len;
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
	int count()
	{
		return countPrivate(root);
	}
	bool isComplete(node<T>*subTreeRoot,int index,int count)
	{
		if (subTreeRoot == NULL)
			return true;
		if (index >= count) return false;
		else
		{
			return isComplete(subTreeRoot->left, 2 * index + 1, count) && 
				isComplete(subTreeRoot->right, 2 * index + 2, count);
		}
	}
	bool isComplete()
	{
		int count = this->count();
		return isComplete(root,0,count);
	}
	bool isFull(node<T>*subTreeRoot)
	{
		if (subTreeRoot == NULL) return true;
		 if (subTreeRoot-> left == NULL&&subTreeRoot->right == NULL) return true;
		 if ((subTreeRoot->left) && (subTreeRoot->right))
		 {
			 return isFull(subTreeRoot->left) && isFull(subTreeRoot->right);
		 }
		else return false;
	}
	bool isFull()
	{
		return isFull(root);
	}
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
			if (x > subTreeRoot->data)
			{
				addNode(subTreeRoot->right, x);
			}
		}
	}
	///binary search tree
	void addNode(T x)
	{
		return addNode(root, x);
	}
};

int main()
{
	tree<int> t;
	t.add(6, "");
	t.add(9, "R");
	t.add(10, "RR");
	t.add(5, "RRL");
	t.add(11, "RRR");
	t.add(7, "L");
	t.add(12, "LL");
	t.prettyPrint();
	cout << endl;
	cout << t.sumofAllLeft() << endl;
	tree<int> t1;
	t1.add(1, "");
	t1.add(2, "L");
	t1.add(3, "R");
	t1.add(4, "LL");
	t1.add(5, "LR");
	t1.add(6, "RR");
	cout << t1.isComplete() << endl;
	cout << t1.isFull() << endl;
	tree<int> bt;
	bt.addNode(10);
	bt.addNode(20);
	bt.addNode(9);
	bt.prettyPrint();

}
