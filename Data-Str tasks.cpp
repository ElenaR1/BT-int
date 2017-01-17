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
