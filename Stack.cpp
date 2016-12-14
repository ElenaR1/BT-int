//с вграден стек:
#include <iostream>
#include<iomanip>
#include<string.h>
#include<string>
#include <vector>
#include <stack>
#include <algorithm>
#include <assert.h>
using namespace std;

template<typename T>
const T& getMax(stack<T> s)
{
	stack<int> s2;
	int max = s.top();
	while (!s.empty())
	{
		if (s.top() > max)
		{
			max = s.top();
		}
		else
		{
			s2.push(s.top());
			s.pop();
		}
	}
	while (!s2.empty())
	{
		s.push(s2.top());
		s2.pop();
	}
	return max;
}
bool bracket(string a)
{
	stack<char>s;
	for (size_t i = 0; i < a.size(); i++)
	{
		if (a[i] == '(')
		{
			s.push(a[i]);
		}
		if (a[i] == ')')
		{
			if (s.empty())
			{
				return false;
			}
			else
			s.pop();
		}
	}
	if (s.empty()) return true;
	else
		return false;
}
void reverse1(char a[])
{
	stack<char> s;
	int len = strlen(a);
	for (size_t i = 0; i < len; i++)
	{
		s.push(a[i]);
	}
	for (size_t i = 0; i < len; i++)
	{
		a[i] = s.top();
		s.pop();
	}
}
void evaluatePostfix(string a)
{
	int n;
	int result;
	stack<int> newStack;
	//int len = strlen(a);
	for (size_t i = 0; i < a.size(); i++)// "63+2*"=18
	{
		if (isdigit(a[i]))
		{
			char c = a[i];
			n = c - '0';
			newStack.push(n);//6 vliza posle 3 vliza

		}
		if (a[i] == '+')
		{
			int x = newStack.top();//x=3
			newStack.pop();
			int y = newStack.top();//y=6
			newStack.pop();
			result = x + y;//8
			newStack.push(result);//vkarvame v steka 9
		}
		if (a[i] == '-')
		{
			int x = newStack.top();
			newStack.pop();
			int y = newStack.top();
			newStack.pop();
			result = y - x;//8
			newStack.push(result);

		}
		if (a[i] == '*')
		{
			int x = newStack.top();
			newStack.pop();
			int y = newStack.top();
			newStack.pop();
			result = x*y;//8
			newStack.push(result);

		}
		if (a[i] == '/')
		{
			int x = newStack.top();
			newStack.pop();
			int y = newStack.top();
			newStack.pop();
			result = y / x;//8
			newStack.push(result);
		}
	}
	cout << "result of expression is  " << newStack.top();
}

//greshno
/*void evaluatePrefix(string a)
{
	reverse(a.begin(),a.end());
	evaluatePostfix(a);
}*/
void evaluatePrefix2(char a[])
{
	//reverse(a);
	//evaluatePrefix(a);
	stack<int> s;
	int n;
	int result;
	int len = strlen(a);
	reverse1(a);
	for (int i =0; i <len; i++)
	{
		if (isdigit(a[i]))
		{
			char c = a[i];
			n = c - '0';
			s.push(n);
		}
		if (a[i] == '+')
		{
			int x = s.top();
			s.pop();
			int y = s.top();
			s.pop();
			result = x + y;
			s.push(result);
		}
		if (a[i] == '-')
		{
			int x = s.top();
			s.pop();
			int y = s.top();
			s.pop();
			result = x - y;
			s.push(result);
		}
		if (a[i] == '*')
		{
			int x = s.top();
			s.pop();
			int y = s.top();
			s.pop();
			result = y * x;
			s.push(result);
		}
		if (a[i] == '/')
		{
			int x = s.top();
			s.pop();
			int y = s.top();
			s.pop();
			result = x / y;
			s.push(result);
		}
	}
	cout << "result: " << s.top() << endl;
}


/*char* f()
{
char*a = "few";
return a;
}
string str()
{
string a = "few";
return a;
}
char* ff()
{
char a[] = "few";
return a;
}
char* fff()
{

char*a = new char[4];
strcpy_s(a, 4, "few");
return a;
}*/
int main()
{
	stack<int> s;
	s.push(5);
	s.push(2);
	s.push(17);
	s.push(0);
	s.push(11);
	cout << getMax<int>(s) << endl;
	string a = "((()))";
	cout << bracket(a) << endl;
	char str[] = "Hello";
	reverse1(str);
	cout << "after reversing the string: " << str << endl;
	cout << strlen(str) << endl;
	string expression = "63+2*";
	string ex = "5234+*-";
	evaluatePostfix(expression);//po razlichen nachin se presmqta ot prefix expression-a
	cout << endl;
	evaluatePostfix(ex);
	cout << endl;
	//string exp = "-*+4325"; GRESHNO
	//evaluatePrefix(exp);//9
	cout << endl;
	char sameexp[] = "-*+4325";
	evaluatePrefix2(sameexp);//VQRNO
	cout << endl;


	/*cout << f << endl << ff << endl ;
	cout << str();
	char*c = fff();
	cout<< *c;*/
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
        node<T>* n = new node<T>(newData, top);//top purvonachalno e NULL zaradi default-niq kontruktor
//i vsqko sledvashto dobaveno trqbva da stava top-a t.k e nai-otgore na steka
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
	for (int i = 0; i < expression.length(); i++)//
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
void changeOfBrackets(string &a)
{
	int n = a.size();
	char l = '(';
	char r = ')';
	for (size_t i = 0; i < n; i++)
	{
		if (IsLeftParenthesis(a[i]))
		{
			a[i] = r;
		}
		else if (IsRightParenthesis(a[i]))
		{
			a[i] = l;
		}
	}
}




void reverse1(string &expression)
{
	reverse(expression.begin(), expression.end());
	changeOfBrackets(expression);	
}

string InfixToPrefix(string &expression)
{
	reverse1(expression);
	string c= InfixToPostfix(expression);	
	reverse(c.begin(), c.end());
	return c;
};

int main()
{

	//string a = "A+B*C-D*E";
	string a = "(A+B/C*(D+E)-F)";
	cout << InfixToPostfix(a) << endl;
	//string b = "((A+B)*C-D)*E";
	string c = "A+(B*C-(D/E^F)*G)";
	//cout << InfixToPostfix(b) << endl;
	cout << InfixToPrefix(c);//rezultatu trqbva da e: +A-*BC*/DÊFG
	
	
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


//sorted stack 
#include <iostream>
#include <iomanip>
#include <stack>
#include <set>
#include<fstream>

using namespace std;

void printStack(stack<int> s)
{
	while (!s.empty()) {
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;
}
stack<int> sortAscending(stack<int> s)// 1 3 2 4
{
	stack<int> newstack;
	if (s.empty())
	{
		return s;
	}
	int x = s.top();
	s.pop();
	newstack.push(x);//x=1
	while (!s.empty())
	{
		int temp = s.top();//3
		s.pop();
		while (!newstack.empty()&&temp>newstack.top())//3 > 1
		{
			s.push(newstack.top());//s.push(1), s= 1 2 4
			newstack.pop();
		}
		newstack.push(temp);//newstack=3
	}
	return newstack;
}

stack<int> sortDescending(stack<int> s)// 1 3 2 4
{
	stack<int> newstack;
	if (s.empty())
	{
		return s;
	}
	int x = s.top();
	s.pop();
	newstack.push(x);//x=1
	while (!s.empty())
	{
		int temp = s.top();//3
		s.pop();
		while (!newstack.empty() && temp<newstack.top())//3 > 1
		{
			s.push(newstack.top());//s.push(1), s= 1 2 4
			newstack.pop();
		}
		newstack.push(temp);//newstack=3
	}
	return newstack;
}
int main()
{
	stack<int> s;
	s.push(4);
	s.push(2);
	s.push(3);
	s.push(1);
	printStack(sortAscending(s));
	printStack(sortDescending(s));
	
}
