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
