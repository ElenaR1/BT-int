#include <iostream>
#include <string.h>
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
//??
bool IsOperand(char ch)
{
	if (ch >= '0' && ch <= '9') 
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
	for (int i = 0; i < expression.length(); i++)
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

void calculate()
{
	stack<char> s;
	string expression;
	cout << "Please enter an expression" << endl;
	cin >> expression;
	string newExpression = InfixToPostfix(expression);
	int len = expression.length();
	int result;
	for (size_t i = 0; i < len; i++)
	{
		if (Flag(expression[i]))
		{
			continue;
		}
		if (isNumber(newExpression[i]))
		{
			int a = newExpression[i] - '0';
			s.push(a);
		}
		if (newExpression[i] == '+')
		{
			int x = s.top();//x=3
			s.pop();
			int y = s.top();//y=6
			s.pop();
			result = x + y;//8
			s.push(result);//vkarvame v steka 9
		}
		if (newExpression[i] == '-')
		{
			int x = s.top();
			s.pop();
			int y = s.top();
			s.pop();
			result = y - x;//8
			s.push(result);

		}
		if (newExpression[i] == '*')
		{
			int x = s.top();
			s.pop();
			int y = s.top();
			s.pop();
			result = x*y;//8
			s.push(result);

		}
		if (newExpression[i] == '/')
		{
			int x = s.top();
			s.pop();
			int y = s.top();
			s.pop();
			result = y / x;//8
			s.push(result);
		}
	}
	cout << "result of expression is  " << s.top();

	}

int main()
{
	
	
	calculate();
	
	return 0;
}


















//new
#include <iostream>
#include <string.h>
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
	/*void calculate(string a)
	{
		int n;
		int result;
		int len = a.size();
		for (size_t i = 0; i < len; i++)
		{
			if (isNumber(a[i]))
			{
				char c = a[i];
				n = c - '0';
				push(n);

			}
			if (a[i] == '+')
			{
				int x = top();//x=3
				pop();
				int y = top();//y=6
				pop();
				result = x + y;//8
				push(result);//vkarvame v steka 9
			}
			if (a[i] == '-')
			{
				int x = top();//x=3
				pop();
				int y = top();//y=6
				pop();
				result = y-x;//8
				push(result);//vkarvame v steka 9
			}
			if (a[i] == '*')
			{
				int x = top();//x=3
				pop();
				int y = top();//y=6
				pop();
				result = x * y;//8
				push(result);//vkarvame v steka 9
			}
			if (a[i] == '/')
			{
				int x = top();//x=3
				pop();
				int y = top();//y=6
				pop();
				result = y/x;
				push(result);//vkarvame v steka 9
			}
		}
		cout << "result of expression is  " << top();
	}*/
	
};
calcStack<int>num;
calcStack<char>op;
int index;
void inputString(string exp)
{
	getline(cin, exp);
	cout << exp << endl;
}
void handleNumber(int&i,string exp)
{
	int value = 0;
	while (isNumber(exp[i]))
	{
		value *= 10;
		value += (int)(exp[i] - 48);
		i++;
	}
	num.push(value);
}
int getSize(string exp)
{
	return exp.size();
}
void calculate(string exp)
{
	int size = getSize(exp);
	while (index < size)
	{
		if (exp[index]==' ')
		{
			continue;
		}
		if (exp[index] == '(')
		{
			op.push(exp[index]);
		}
		if (IsOperator(exp[index]) && !HasHigherPrecedence(num.top(), exp[index]))//&& num.top() != '('
		{
			op.push(exp[index]);
		}
		if (IsOperator(exp[index]) && HasHigherPrecedence(num.top(), exp[index]))//&& num.top() != '('
		{
			char operation = op.top();
			op.pop();

		}
	}
}
string InfixToPostfix(string expression)
{
	calcStack <char> S;
	string postfix = "";
	for (int i = 0; i < expression.length(); i++)
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

int main()
{
	//char a = '4';
	//int b = (int)(a - 48);
	//cout << b;

	index = 0;
	handleNumber(index, "58+10");
	cout << num.top() << endl;
	string x = "dog:cat";
	int pos = x.find(":");
	string sub = x.substr(pos + 1);
	cout << sub;

	return 0;
}
