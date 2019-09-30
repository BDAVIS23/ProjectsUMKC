// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//Jacob Anderson, Bryan Davis
#include<iostream>
#include<string>
#include<stack>
#include<sstream>
#include<math.h>

using namespace std;

int getPriority(string op);
void performOp(stack<string>& op, stack<int>& num);
void parser(string input, stack<string>& op, stack<int>& num);

int main()
{
	stack<int> num;
	stack<string> op;

	string input;

	cout << "Please input an expression: ";
	getline(cin, input);

	parser(input, op, num);
	cout << "The size of the op stack is: " << op.size() << endl;
	cout << "The size of the num stack is: " << num.size() << endl;

	while (op.empty() == false && num.empty() == false)
	{
		cout << "Performing Operation: " << endl;
		performOp(op, num);
	}

	if (num.empty() == false)
		cout << endl << "The result is: " << num.top() << endl;

	system("pause");
	return 0;

}

void parser(string input, stack<string>& op, stack<int>& num)
{
	int i;
	int n;
	string substring;
	int checkParinth = 0;
	bool isNum = false;
	bool isBiOp = false;
	bool isValid = true;
	bool isUnOp = false;
	bool isNeg = false;

	if (input[0] == ')')
	{
		cout << "Error. Cannot start with a closed paranthesis at index 0." << endl;
		isValid = false;
	}
	if (input[0] == '&' || input[0] == '|')
	{
		cout << "Error. Cannot start with a binary operator at index 0." << endl;
		isValid = false;
	}
	if (input[0] == '>' || input[0] == '<' || input[0] == '=')
	{
		cout << "Error. Cannot start with a comparason operator at index 0." << endl;
		isValid = false;
	}
	if (input[0] == '!' && input[1] == '=')
	{
		cout << "Error. Cannot start with a comparason operator at index 0." << endl;
		isValid = false;
	}
	for (i = 0; i < input.size(); i++)
	{
		cout << "i is: " << i << endl;

		if (isValid == true)
		{
			switch (input[i])
			{

			case ' ':
			{cout << "This index is blank and will be skipped." << endl;
			break;
			}

			case '+':

				if (input[i + 1] == '+')
				{
					isUnOp = true;
					if (isNum == true)
					{
						cout << "Error. Cannot have a unary operator after an operand at index: " << i << endl;
						isValid = false;
					}

					substring = input.substr(i, 2);
					if (op.empty() == true || getPriority(op.top()) <= getPriority(substring))
					{
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);
						i++;

						break;
					}
					else if (op.empty() == false && getPriority(op.top()) > getPriority(substring))
					{

						while (op.empty() == false && getPriority(op.top()) > getPriority(substring))
						{
							cout << "Performing operation" << endl;
							performOp(op, num);
						}
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);
						i++;

						break;
					}
				}
				else if (input[i + 1] != '+')
				{
					if (isUnOp == true)
					{
						cout << "Error. Cannot have a binary operator next to a unary operator at index: " << i << endl;
						isValid = false;
						break;
					}
					if (isBiOp == true)
					{
						cout << "Error. Cannot have two binary operators next to each other at index: " << i << endl;
						isValid = false;
						break;
					}
					isUnOp = false;
					isBiOp = true;
					isNum = false;
					substring = input.substr(i, 1);
					if (op.empty() == true || getPriority(op.top()) <= getPriority(substring))
					{
						cout << "Case 1" << endl;
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);
						break;
					}
					else if (getPriority(op.top()) > getPriority(substring))
					{
						while (op.empty() == false && getPriority(op.top()) > getPriority(substring))
						{
							cout << "Performing operation" << endl;
							performOp(op, num);
						}
						cout << "case 2" << endl;
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);

						break;
					}
				}

				break;
			case '-':


				if (input[i + 1] == '-')
				{
					isUnOp = true;
					substring = input.substr(i, 2);
					if (op.empty() == true || getPriority(op.top()) <= getPriority(substring))
					{
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);
						i++;
					}
					else if (getPriority(op.top()) >= getPriority(substring))
					{
						while (op.empty() == false && getPriority(op.top()) > getPriority(substring))
						{
							cout << "Performing operation" << endl;
							performOp(op, num);
						}
					}
				}
				else
				{
					if (isUnOp == true)
					{
						cout << "Error. Cannot have a binary operator next to a unary operator at index: " << i << endl;
						isValid = false;
						break;
					}
					if (isBiOp == true)
					{
						cout << "Error. Cannot have two binary operators next to each other at index: " << i << endl;
						isValid = false;
						break;
					}
					isUnOp = false;
					isBiOp = true;
					isNum = false;


					substring = input.substr(i, 1);
					if (op.empty() == true || getPriority(op.top()) <= getPriority(substring))
					{
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);
						break;
					}
					else if (getPriority(op.top()) >= getPriority(substring))
					{
						while (op.empty() == false && getPriority(op.top()) > getPriority(substring))
						{
							cout << "Performing operation" << endl;
							performOp(op, num);
						}
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);

						break;
					}
				}

				break;
			case '*':
				if (isUnOp == true)
				{
					cout << "Error. Cannot have a binary operator next to a unary operator at index: " << i << endl;
					isValid = false;
					break;
				}
				if (isBiOp == true)
				{
					cout << "Error. Cannot have two binary operators next to each other at index: " << i << endl;
					isValid = false;
					break;
				}
				isUnOp = false;
				isBiOp = true;
				isNum = false;
				substring = input.substr(i, 1);
				if (op.empty() == true || getPriority(op.top()) <= getPriority(substring))
				{
					cout << "The op being pushed onto the op stack is: " << substring << endl;
					op.push(substring);
					break;
				}
				else if (getPriority(op.top()) > getPriority(substring))
				{
					while (op.empty() == false && getPriority(op.top()) > getPriority(substring))
					{
						cout << "Performing operation" << endl;
						performOp(op, num);
					}

					cout << "The op being pushed onto the op stack is: " << substring << endl;
					op.push(substring);

					break;
				}
				break;
			case '/':
				if (isUnOp == true)
				{
					cout << "Error. Cannot have a binary operator next to a unary operator at index: " << i << endl;
					isValid = false;
					break;
				}
				if (isBiOp == true)
				{
					cout << "Error. Cannot have two binary operators next to each other at index: " << i << endl;
					isValid = false;
					break;
				}
				isUnOp = false;
				isBiOp = true;
				isNum = false;
				substring = input.substr(i, 1);
				if (op.empty() == true || getPriority(op.top()) <= getPriority(substring))
				{
					cout << "The op being pushed onto the op stack is: " << substring << endl;
					op.push(substring);
					break;
				}
				else if (getPriority(op.top()) > getPriority(substring))
				{
					while (op.empty() == false && getPriority(op.top()) > getPriority(substring))
					{
						cout << "Performing operation" << endl;
						performOp(op, num);
					}
					cout << "The op being pushed onto the op stack is: " << substring << endl;
					op.push(substring);

					break;
				}
				break;
			case '%':
				if (isUnOp == true)
				{
					cout << "Error. Cannot have a binary operator next to a unary operator at index: " << i << endl;
					isValid = false;
					break;
				}
				if (isBiOp == true)
				{
					cout << "Error. Cannot have two binary operators next to each other at index: " << i << endl;
					isValid = false;
					break;
				}
				isUnOp = false;
				isBiOp = true;
				isNum = false;
				substring = input.substr(i, 1);
				if (op.empty() == true || getPriority(op.top()) <= getPriority(substring))
				{
					cout << "The op being pushed onto the op stack is: " << substring << endl;
					op.push(substring);
					break;
				}
				else if (getPriority(op.top()) > getPriority(substring))
				{
					while (op.empty() == false && getPriority(op.top()) >= getPriority(substring))
					{
						cout << "Performing operation" << endl;
						performOp(op, num);
					}
					cout << "The op being pushed onto the op stack is: " << substring << endl;
					op.push(substring);

					break;
				}
				break;
			case '^':
				isUnOp = false;
				isBiOp = false;
				isNum = false;
				substring = input.substr(i, 1);
				if (op.empty() == true || getPriority(op.top()) <= getPriority(substring))
				{
					cout << "The op being pushed onto the op stack is: " << substring << endl;
					op.push(substring);
					break;
				}
				else if (getPriority(op.top()) > getPriority(substring))
				{
					while (op.empty() == false && getPriority(op.top()) > getPriority(substring))
					{
						cout << "Performing operation" << endl;
						performOp(op, num);
					}
					cout << "The op being pushed onto the op stack is: " << substring << endl;
					op.push(substring);

					break;
				}
				break;
			case '&':
				if (isUnOp == true)
				{
					cout << "Error. Cannot have a binary operator next to a unary operator at index: " << i << endl;
					isValid = false;
					break;
				}
				if (isBiOp == true)
				{
					cout << "Error. Cannot have two binary operators next to each other at index: " << i << endl;
					isValid = false;
					break;
				}
				isBiOp = true;
				isNum = false;
				if (input[i + 1] == '&')
				{
					substring = input.substr(i, 2);
					if (op.empty() == true || getPriority(op.top()) <= getPriority(substring))
					{
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);
						i++;
						break;
					}
					else if (getPriority(op.top()) > getPriority(substring))
					{
						while (op.empty() == false && getPriority(op.top()) > getPriority(substring))
						{
							cout << "Performing operation" << endl;
							performOp(op, num);
						}
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);
						i++;
						break;
					}
				}
				else
				{
					cout << "Error. Incomplete Binary Operator at index: " << i << endl;
					isValid = false;
				}
				break;
			case '|':
				if (isUnOp == true)
				{
					cout << "Error. Cannot have a binary operator next to a unary operator at index: " << i << endl;
					isValid = false;
					break;
				}
				if (isBiOp == true)
				{
					cout << "Error. Cannot have two binary operators next to each other at index: " << i << endl;
					isValid = false;
					break;
				}
				isBiOp = true;
				isNum = false;
				if (input[i + 1] == '|')
				{
					substring = input.substr(i, 2);
					if (op.empty() == true || getPriority(op.top()) <= getPriority(substring))
					{
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);
						i++;
						break;
					}
					else if (getPriority(op.top()) > getPriority(substring))
					{
						while (op.empty() == false && getPriority(op.top()) > getPriority(substring))
						{
							cout << "Performing operation" << endl;
							performOp(op, num);
						}
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);
						i++;
						break;
					}
				}
				else
				{
					cout << "Error. Incomplete Binary Operator at index: " << i << endl;
					isValid = false;
				}
				break;
			case '!':
				if (isUnOp == true)
				{
					cout << "Error. Cannot have a binary operator next to a unary operator at index: " << i << endl;
					isValid = false;
					break;
				}
				if (isBiOp == true)
				{
					cout << "Error. Cannot have two binary operators next to each other at index: " << i << endl;
					isValid = false;
					break;
				}
				isBiOp = true;
				isNum = false;
				if (input[i + 1] == '=')
				{
					substring = input.substr(i, 2);
					if (op.empty() == true || getPriority(op.top()) <= getPriority(substring))
					{
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);
						i++;
						break;
					}
					else if (getPriority(op.top()) > getPriority(substring))
					{
						while (op.empty() == false && getPriority(op.top()) > getPriority(substring))
						{
							cout << "Performing operation" << endl;
							performOp(op, num);
						}
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);
						i++;
						break;
					}
				}
				else
				{
					substring = input.substr(i, 1);
					if (op.empty() == true || getPriority(op.top()) <= getPriority(substring))
					{
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);
						break;
					}
					else if (getPriority(op.top()) > getPriority(substring))
					{
						while (op.empty() == false && getPriority(op.top()) > getPriority(substring))
						{
							cout << "Performing operation" << endl;
							performOp(op, num);
						}
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);

						break;
					}
				}
				break;
			case '=':
				if (isUnOp == true)
				{
					cout << "Error. Cannot have a binary operator next to a unary operator at index: " << i << endl;
					isValid = false;
					break;
				}
				if (isBiOp == true)
				{
					cout << "Error. Cannot have two binary operators next to each other at index: " << i << endl;
					isValid = false;
					break;
				}
				isBiOp = true;
				isNum = false;
				if (input[i + 1] == '=')
				{
					substring = input.substr(i, 2);
					if (op.empty() == true || getPriority(op.top()) <= getPriority(substring))
					{
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);
						i++;
						break;
					}
					else if (getPriority(op.top()) > getPriority(substring))
					{
						while (op.empty() == false && getPriority(op.top()) > getPriority(substring))
						{
							cout << "Performing operation" << endl;
							performOp(op, num);
						}
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);
						i++;
						break;
					}
				}
				else
				{
					cout << "Error. Incomplete Comparison Operator at index: " << i << endl;
					isValid = false;
				}
				break;
			case '(':

				checkParinth++;

				isNum = false;

				substring = input.substr(i, 1);

				cout << "The op being pushed onto the op stack is: " << substring << endl;
				op.push(substring);

				break;
			case ')':
				checkParinth--;
				if (checkParinth < 0)
				{
					cout << "Error unbalanced parenthesis at index: " << i << endl;
					isValid = false;

					break;
				}


				isNum = false;
				substring = input.substr(i, 1);
				if (op.empty() == true || getPriority(op.top()) <= getPriority(substring))
				{
					cout << "The op being pushed onto the op stack is: " << substring << endl;
					op.push(substring);
					break;
				}
				else if (getPriority(op.top()) > getPriority(substring))
				{
					while (op.empty() == false && getPriority(op.top()) > getPriority(substring))
					{
						cout << "Performing operation" << endl;
						performOp(op, num);
					}
					cout << "The op being pushed onto the op stack is: " << substring << endl;
					op.push(substring);
					break;
				}

				break;
			case '<':
				if (isUnOp == true)
				{
					cout << "Error. Cannot have a binary operator next to a unary operator at index: " << i << endl;
					isValid = false;
					break;
				}
				if (isBiOp == true)
				{
					cout << "Error. Cannot have two binary operators next to each other at index: " << i << endl;
					isValid = false;
					break;
				}
				isBiOp = true;
				isNum = false;
				if (input[i + 1] == '=')
				{
					substring = input.substr(i, 2);
					if (op.empty() == true || getPriority(op.top()) <= getPriority(substring))
					{
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);
						i++;
						break;
					}
					else if (getPriority(op.top()) > getPriority(substring))
					{
						while (op.empty() == false && getPriority(op.top()) > getPriority(substring))
						{
							cout << "Performing operation" << endl;
							performOp(op, num);
						}
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);
						i++;
						break;
					}
				}
				else
				{
					substring = input.substr(i, 1);
					if (op.empty() == true || getPriority(op.top()) <= getPriority(substring))
					{
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);
						break;
					}
					else if (getPriority(op.top()) > getPriority(substring))
					{
						while (op.empty() == false && getPriority(op.top()) > getPriority(substring))
						{
							cout << "Performing operation" << endl;
							performOp(op, num);
						}
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);

						break;
					}
				}
				break;
			case '>':
				if (isUnOp == true)
				{
					cout << "Error. Cannot have a binary operator next to a unary operator at index: " << i << endl;
					isValid = false;
					break;
				}
				if (isBiOp == true)
				{
					cout << "Error. Cannot have two binary operators next to each other at index: " << i << endl;
					isValid = false;
					break;
				}
				isBiOp = true;
				isNum = false;
				if (input[i + 1] == '=')
				{

					substring = input.substr(i, 2);
					if (op.empty() == true || getPriority(op.top()) <= getPriority(substring))
					{
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);
						i++;
						break;
					}
					else if (getPriority(op.top()) > getPriority(substring))
					{
						while (op.empty() == false && getPriority(op.top()) > getPriority(substring))
						{
							cout << "Performing operation" << endl;
							performOp(op, num);
						}
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);
						i++;
						break;
					}
				}
				else
				{
					substring = input.substr(i, 1);
					if (op.empty() == true || getPriority(op.top()) <= getPriority(substring))
					{
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);
						break;
					}
					else if (getPriority(op.top()) > getPriority(substring))
					{
						while (op.empty() == false && getPriority(op.top()) > getPriority(substring))
						{
							cout << "Performing operation" << endl;
							performOp(op, num);
						}
						cout << "The op being pushed onto the op stack is: " << substring << endl;
						op.push(substring);

						break;
					}

				}

				break;
			default:
				isUnOp = false;
				isBiOp = false;


				if (isNum == true)
				{
					cout << "Error. Cannot have 2 numbers next to each other at index: " << i << endl;
					bool isValid = false;
					break;
				}
				substring = input.substr(i);

				if (istringstream(substring) >> n)
				{
					if (isNeg == true)
					{
						n = n * -1;
					}

					cout << "The number being pushed onto the num stack is: " << n << endl;
					num.push(n);
					substring = to_string(n);
					i = i + substring.size() - 1;
				}

			}
		}


		else if (isValid == false)
		{
			break;
		}



		if (checkParinth > 0)
		{
			cout << "Error unbalanced parenthesis at index: " << i << endl;
			isValid == false;
		}
		if (isValid == false)
		{
			while (op.empty() == false)
			{
				op.pop();
			}
		}
	}
}
	
	int getPriority(string op)
{
	if (op == "(" || op == ")")
	{
		return 0;
	}
	else if (op == "||")
	{
		return 1;
	}
	else if (op == "&&")
	{
		return 2;
	}
	else if (op == "==" || op == "!=")
	{
		return 3;
	}
	else if (op == ">" || op == "<")
	{
		return 4;
	}
	else if (op == ">=" || op == "<=")
	{
		return 4;
	}
	else if (op == "+" || op == "-")
	{
		return 5;
	}
	else if (op == "*" || op == "/" || op == "%")
	{
		return 6;
	}
	else if (op == "^")
	{
		return 7;
	}
	else if (op == "++" || op == "--")
	{
		return 8;
	}
	else if (op == "!")
	{
		return 8;
	}
	else
	{
		return 0;
	}
}

void performOp(stack<string>& op, stack<int>& num)
{
	int rightNum, leftNum;
	int result;
	cout << "Calculating: " << endl;

	if (op.top() == "+")
	{
		rightNum = num.top();
		num.pop();
		leftNum = num.top();
		num.pop();
		result = rightNum + leftNum;
		cout << "the result of the calculation is: " << result << endl;
		num.push(result);


	}
	if (op.top() == "-")
	{
		rightNum = num.top();
		num.pop();
		leftNum = num.top();
		num.pop();
		result = leftNum - rightNum;
		cout << "the result of the calculation is: " << result << endl;
		num.push(result);

	}

	if (op.top() == "++")
	{
		rightNum = num.top();
		num.pop();
		result = rightNum + 1;
		cout << "the result of the calculation is: " << result << endl;
		num.push(result);

	}
	if (op.top() == "--")
	{
		rightNum = num.top();
		num.pop();
		result = rightNum - 1;
		cout << "the result of the calculation is: " << result << endl;
		num.push(result);

	}
	if (op.top() == "*")
	{
		rightNum = num.top();
		num.pop();
		leftNum = num.top();
		num.pop();
		result = rightNum * leftNum;
		cout << "the result of the calculation is: " << result << endl;
		num.push(result);

	}
	if (op.top() == "/")
	{
		rightNum = num.top();
		num.pop();
		leftNum = num.top();
		num.pop();
		if (rightNum != 0)
		{
			result = leftNum / rightNum;
			cout << "the result of the calculation is: " << result << endl;
			num.push(result);
		}
		else
		{
			cout << "Error division by 0!" << endl;
			while (op.empty == false)
			{
				op.pop();
			}
		}
	}
	if (op.top() == "%")
	{
		rightNum = num.top();
		num.pop();
		leftNum = num.top();
		num.pop();
		result = leftNum % rightNum;
		cout << "the result of the calculation is: " << result << endl;
		num.push(result);

	}
	if (op.top() == "^")
	{
		rightNum = num.top();
		num.pop();
		leftNum = num.top();
		num.pop();
		result = pow(leftNum, rightNum);
		cout << "the result of the calculation is: " << result << endl;
		num.push(result);

	}
	if (op.top() == ">")
	{
		rightNum = num.top();
		num.pop();
		leftNum = num.top();
		num.pop();
		result = leftNum > rightNum;
		num.push(result);

	}
	if (op.top() == ">=")
	{
		rightNum = num.top();
		num.pop();
		leftNum = num.top();
		num.pop();
		result = leftNum >= rightNum;
		num.push(result);
	}
	if (op.top() == "<")
	{
		rightNum = num.top();
		num.pop();
		leftNum = num.top();
		num.pop();
		result = leftNum < rightNum;
		num.push(result);
	}
	if (op.top() == "<=")
	{
		rightNum = num.top();
		num.pop();
		leftNum = num.top();
		num.pop();
		result = leftNum <= rightNum;
		num.push(result);
	}
	if (op.top() == "==")
	{
		rightNum = num.top();
		num.pop();
		leftNum = num.top();
		num.pop();
		result = leftNum == rightNum;
		num.push(result);
	}
	if (op.top() == "&&")
	{
		rightNum = num.top();
		num.pop();
		leftNum = num.top();
		num.pop();
		result = leftNum && rightNum;
		num.push(result);
	}
	if (op.top() == "||")
	{
		rightNum = num.top();
		num.pop();
		leftNum = num.top();
		num.pop();
		result = leftNum || rightNum;
		num.push(result);
	}
	if (op.top() == "!")
	{
		rightNum = num.top();
		num.pop();
		result = !rightNum;
		num.push(result);

	}
	if (op.top() == "!=")
	{
		rightNum = num.top();
		num.pop();
		leftNum = num.top();
		num.pop();
		result = leftNum != rightNum;
		num.push(result);
	}


	op.pop();

}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file