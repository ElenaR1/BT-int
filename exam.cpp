#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <assert.h>
using namespace std;

struct node {
	int data;
	node* next;

	node(): next(NULL) {}
	node(int data,node* next): data(data), next(NULL) {}
};
void f1(node* head1,node*head2)
{
    map<int,bool> mp;
    node*current1=head1;
    while(current1!=NULL)
    {
        mp[current1->data]=true;
        current1=current1->next;
    }
    node* current2=head2;
    while(current2!=NULL)
    {
        if(mp.find(current2->data)==mp.end())
        {
            cout<<current2->data;
        }
        current2=current2->next;
    }

    map<int,bool> mp2;
    node*c2=head2;
     while(c2!=NULL)
    {
        mp2[current1->data]=true;
        c2=c2->next;
    }
    node* c1=head1;
    while(c1!=NULL)
    {
        if(mp.find(c1->data)==mp2.end())
        {
            cout<<c1->data;
        }
        c1=c1->next;
    }
}
void intersection(node* head1,node*head2)
{
     map<int,bool> mp;
    node*current1=head1;
    while(current1!=NULL)
    {
        mp[current1->data]=true;
        current1=current1->next;
    }
    node* current2=head2;
    
    while(current2!=NULL)
    {
        if(mp.find(current2->data)!=mp.end())//ako go nameri ne dostiga do end sledovatelno elementa e i vuv 2riq spisuk \
            //i v takuv sluchai go printim
        {
            cout<<current2->data;
        }
        current2=current2->next;
    }
    
}
class list {
private:
	node*head;
	node *curr;
	node *temp;
	node *last;
public:
    list()
	{
		head = NULL;
		curr = NULL;
		temp = NULL;
	}
	void addFront( int addData)
	{
		node *n = new node(addData,head);
		head = n;
		if (last == NULL)
			last = head;
		assert(head != NULL);
	}
	void addEnd( int addData)
	{
		node *n = new node(addData, NULL);
		if (head == NULL)
        {
			addFront(addData);
		}
		else {
			last->next = n;
			last = last->next;
		}
	}

};
int main()
{
    list l;
    l.addEnd(2);
    l.addEnd(4);
    l.addEnd(6);

    return 0;
}













#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <assert.h>
using namespace std;

template <class T>
struct node {
	T data;
	node<T> *left;
	node<T> *right;
	node() :left(NULL), right(NULL) {}
	node(const T d, node<T> *l, node<T> *r) :data(d), left(l), right(r) {}
};
template <class T>
class tree{
private:
    node<T>* root;
public:
    tree():root(NULL){}
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
	 void swap(int &a, int &b)
    {
        int temp = a;
        a = b;
        b = temp;
    }
    node<T>* find(node<T>* ptr,T x)
    {
        if(ptr==NULL) return NULL;
        if(ptr->data==x) return ptr;
        else
        {
            if(x<ptr->data)
            {
                find(ptr->left,x);
            }
             if(x>ptr->data)
            {
                find(ptr->right,x);
            }
        }
    }
    node<T>* find(T x)
    {
        find(root,x);
    }
	void changeData(T data1,T data2)
	{
	    changeData(root,data1,data2);
	}
	void changeData(node<T>* &ptr,T data1,T data2)
	{
	    if(ptr==NULL) return;

	    node<T>* ptr1=find(data1);
	    node<T>* ptr2=find(data2);
	    swap(ptr1->data,ptr2->data);
	}

    void findError(node<T>* ptr,T rootData)
    {
        assert(ptr!=NULL);
        if(ptr->left->data<rootData&&ptr->left!=NULL)
        {
            cout<<-1;
            findError(ptr->left,ptr->left->data);
        }
        if(ptr->right->data>rootData&&ptr->right!=NULL)
        {
            findError(ptr->right,ptr->right->data&&ptr->right!=NULL);
        }


        if(rootData<ptr->left->data)
        {
            swap(rootData,ptr->left->data);
            if(ptr->left!=NULL)
            {
                findError(ptr->left,ptr->left->data);
            }

        }

        if(rootData>ptr->right->data)
        {
            cout<<-1;
            swap(rootData,ptr->right->data);
            if(ptr->right!=NULL)
            {
                findError(ptr->right,ptr->right->data);
            }

        }
    }
    void findError()
    {
         findError(root,root->data);
    }

 void addNode(const T& x)
 {
     addNode(root,x);
 }
 void print(node<T> * subTreeRoot)const
	{
		if (subTreeRoot == NULL)
		{
			return;// kakvo pravi??
		}
		if (subTreeRoot != NULL)
		{
			cout << subTreeRoot->data << " ";
			print(subTreeRoot->left);
			print(subTreeRoot->right);
		}
	}
	void print()
	{
	    print(root);
	}
};
int main()
{
    tree<int> t;
    t.addNode(5);
    t.addNode(10);
    t.addNode(2);
    t.print();
    cout<<endl;
    t.changeData(5,10);
    t.print();
    cout<<endl;
    t.findError();
    t.print();

   // return 0;
}
