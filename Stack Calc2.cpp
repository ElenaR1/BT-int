#include <iostream>
#include <string.h>
#include <math.h>
#include <string>
#include <stack>
#include <assert.h>

using namespace std;

bool isNumber(char&a)
{
	if (!isdigit(a))
	{
		return false;
	}
	else
		return true;
}
bool IsOperand(char ch)
{
	if (ch >= '0' && ch <= '9' || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
	{
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
bool IsFunction(char C)
{
	if (C == 'r' || C == 's' || C == 'c' || C == 'l' ) {
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

bool IsRightAssociative(char op)
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


void inputString(string exp)
{
	getline(cin, exp);
	cout << exp << endl;
}
int getSize(string exp)
{
	return exp.size();
}

template<class T>
struct node {
	node<T>* next;
	T data;
	node() :next(NULL) {}
	node(const T& d, node<T>* n) :data(d), next(n) {}
};

template<class T>
class calcStack {
private:
	node<T>* head;
public:
	calcStack()
	{
		head = NULL;
	}
	void push(const T& newData)
	{
		node<T>* n = new node<T>(newData, head);
		head = n;
	}
	void pop()
	{
		if (head == NULL)
		{
			cout << "the stack is empty" << endl;
		}
		else
		{
			node<T>* temp = head;
			head = head->next;
			//cout << "Deleting the first node with value " << temp->data << endl;
			delete temp;
		}
	}
	void show()
	{
		node<T>*curr;
		curr = head;
		while (curr != NULL)
		{
			cout << curr->data << " ";
			curr = curr->next;
		}
	}
	T& top()//??operator=
	{
		return head->data;
	}
	bool empty()
	{
		if (head == NULL)
		{
			return true;
		}
		return false;
	}
	void clear()
	{
		node<T>* temp = head;
		while (!empty())
		{
			pop();
		}
		pop();
	}
	T exponent(T num,T k)
	{
		return pow(num, k);
	}
	T squareRoot(T num)
	{
		return sqrt(num);
	}
	void handleNumber(int&i, string exp)
	{
		int value = 0;
		while (isNumber(exp[i]))
		{
			value *= 10;
			value += (int)(exp[i] - 48);
			i++;
		}
		push(value);
	}
	void calculate(string exp)
	{
		calcStack<char>op;
		int size = getSize(exp);
		int index = 0;
		while (index < size)
		{
			if (exp[index] == ' ')
			{
				continue;
			}
			
			if (exp[index] == '(')
			{
				op.push(exp[index]);
				index++;
			}
			if (IsFunction(exp[index]) && op.empty())
			{
				op.push(exp[index]);
				index++;
			}
			if (IsFunction(exp[index]) && op.top() == '(')//&& num.top() != '('
			{
				op.push(exp[index]);
				index++;
			}
			if (IsOperator(exp[index]) && op.empty())
			{
				op.push(exp[index]);
				index++;
			}
			if (IsOperator(exp[index]) && op.top() == '(')//&& num.top() != '('
			{
				op.push(exp[index]);
				index++;
			}
			if (IsOperator(exp[index]) && !HasHigherPrecedence(op.top(), exp[index]))//&& num.top() != '('
			{
				op.push(exp[index]);
				index++;
			}
			if (IsOperator(exp[index]) && HasHigherPrecedence(op.top(), exp[index]))//&& num.top() != '('
			{
				char operation = op.top();
				op.pop();
				op.push(exp[index]);
				int num1 = top();
				pop();
				int num2 = top();
				pop();
				int result;
				if (operation == '+')
				{
					result = num1 + num2;
					push(result);
				}
				if (operation == '*')
				{
					result = num1 * num2;
					push(result);
				}
				if (operation == '-')
				{
					result = num2 - num1;
					push(result);
				}
				if (operation == '/')
				{
					result = num2 / num1;
					push(result);
				}
				if (operation == '^')
				{
					result = exponent(num2,num1);
					push(result);
				}
				index++;
			}
			if (exp[index] == ')')
			{
				while (!op.empty() && op.top() != '(')
				{
					char operation = op.top();
					op.pop();
					int num1 = top();
					pop();
					int num2 = top();
					pop();
					int result;
					if (operation == '+')
					{
						result = num1 + num2;
						push(result);
					}
					if (operation == '*')
					{
						result = num1 * num2;
						push(result);
					}
					if (operation == '-')
					{
						result = num2 - num1;
						push(result);
					}
					if (operation == '/')
					{
						result = num2 / num1;
						push(result);
					}
					if (operation == '^')
					{
						result = exponent(num2, num1);
						push(result);
					}
				}
				index++;
				op.pop();
			}
			if (IsOperand(exp[index]))
			{
				handleNumber(index, exp);//index-ut se promenq v handleNumber
			}
		}
		while (!op.empty())
		{
			char operation = op.top();
			op.pop();
			int num1 = top();
			pop();
			int num2 = top();
			pop();
			int result;
			if (operation == '+')
			{
				result = num1 + num2;
				push(result);
			}
			if (operation == '*')
			{
				result = num1 * num2;
				push(result);
			}
			if (operation == '-')
			{
				result = num2 - num1;
				push(result);
			}
			if (operation == '/')
			{
				result = num2 / num1;
				push(result);
			}
			if (operation == '^')
			{
				result = exponent(num2, num1);
				push(result);
			}
		}
		cout << "the result is: " << top() << endl;
	}
};


int main()
{
	//char a = '4';
	//int b = (int)(a - 48);
	//cout << b;

	//index = 0;
	//handleNumber(index, "58+10");
	//cout << num.top() << endl;//58
	/*string x = "34+10";
	int pos = x.find("+");
	string sub = x.substr(pos + 1);
	handleNumber(index, sub);
	int n= num.top();
	cout << n << endl;
	cout << "index: " << index;*/

	//string exp = "34*10-20/5";
	//string exp = "10-5*5";
	//string exp = "((10+5)*2)/3";
	string exp = "(17+3)^2";
	//string exp = "sqrt4+5";
	cout << "You can choose between theese operation: + , - , * , / ." << endl;
	cout<<"For the exponent of a number write '^'." << endl;
	cout << "For the square root of a number write 'r'." << endl;
	cout << "For the sin of a number write 's'." << endl;
	cout << "For the cos of a number write 'c'." << endl;
	cout << "For the log of a number write 'l'." << endl;
	//string exp;
	//cin >> exp;
	calcStack<int> s;
	s.calculate(exp);
	cout << s.top() << endl;
	
	return 0;
}
