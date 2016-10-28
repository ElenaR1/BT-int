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

//NE RABOTI
void reverse(char* a)// a="Hello/0"
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
		a[i] = s.peek();//a[0]='/0' 1. a[1]='o' 2.a[2]='l' 3.a[3]='l' 4.a[4]='e' 5.a[5]='H' 
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


void evaluatePrefix(char*a)
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
void infixToPostfix(char*a)
{
	stack<int> stack1;
	int len = strlen(a) + 1;
	char *postfix;
	postfix = new char[len];
	for (size_t i = 0; i < len; i++)
	{
		if (isNumber(a[i]))
		{
			postfix[i] = a[i];
		}
		if (a[i] == '+')
		{
			stack1.push(a[i]);
		}
	}
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
	evaluatePrefix(expression);
	
	char str[] = "Hello";
	reverse(str);
	cout << "after reversing the string: " << str << endl;//// ? zashto ne stava


	cout << endl;
	cout<<"the max data in the stack is: " << s.getMax();

	return 0;
}
