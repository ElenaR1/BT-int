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
