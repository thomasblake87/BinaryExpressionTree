#define _CRT_SECURE_NO_WARNINGS

#include "binaryExpression.h"
#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>

void binaryExpressionTree::buildExpressionTree(string postFixExpr) {
	stack<nodeType<string>*> nodeStack;

	char* expression = new char[postFixExpr.length() + 1];
	strcpy(expression, postFixExpr.c_str());

	string token;
	for (char* token = strtok(expression, " "); token != nullptr; token = strtok(nullptr, " ")) {
		string tokenStr(token);

		if (isdigit(tokenStr[0]) || (tokenStr.length() > 1 && isdigit(tokenStr[1]))) { //If token is a #
			nodeType<string>* node = new nodeType<string>;
			node->info = tokenStr;
			node->lLink = nullptr;
			node->rLink = nullptr;
			nodeStack.push(node);
		}
		else if (tokenStr == "+" || tokenStr == "-" || tokenStr == "*" || tokenStr == "/") { //if token is an operator
			nodeType<string>* node = new nodeType<string>;
			node->info = tokenStr;
			if (!nodeStack.empty()) {
				node->rLink = nodeStack.top();
				nodeStack.pop();
				if (!nodeStack.empty()) {
					node->lLink = nodeStack.top();
					nodeStack.pop();
				}
				else {
					cerr << "Error, stack is empty for left operand" << endl;
					destroyTree();
					return;
				}
			}
			else {
				cerr << "Error, stack is empty for right operand" << endl;
				destroyTree();
				return;
			}
			nodeStack.push(node);
		}
		else {
			cerr << "Error, unsupported token: " << tokenStr << endl;
			destroyTree();
			return;
		}
	}

	if (!nodeStack.empty()) {
		root = nodeStack.top();
		nodeStack.pop();

		if (!nodeStack.empty()) {
			cerr << "There was an error, setting root to 0" << endl;
			root = nullptr;
		}
	}
}

double binaryExpressionTree::evaluateExpressionTree(nodeType<string>* p) {
	//Base case: return node if leaf
	if (!p->lLink && !p->rLink) {
		return stod(p->info);
	}
	else {
		// Recursive case: evaluate left and right
		double leftVal = evaluateExpressionTree(p->lLink);
		double rightVal = evaluateExpressionTree(p->rLink);

		// Perform operation based on operator in node
		if (p->info == "+") {
			return leftVal + rightVal;
		}
		else if (p->info == "-") {
			return leftVal - rightVal;
		}
		else if (p->info == "*") {
			return leftVal * rightVal;
		}
		else if (p->info == "/") {
			if (rightVal == 0) {
				cerr << "Error: Can't divide by zero." << endl;
				return -1;
			}
			return leftVal / rightVal;
		}
		return 0;
	}
}

double binaryExpressionTree::evaluateExpressionTree() {
	if (root == nullptr) {
		cerr << "Error: Tree is empty." << endl;
		return 0;
	}
	return evaluateExpressionTree(root);
}

bool binaryExpressionTree::search(const string& searchItem) const {
	return false;
}

void binaryExpressionTree::insert(const string& insItem) {
	// Not needed
}

void binaryExpressionTree::deleteNode(const string& delItem) {
	// Not needed
}