#pragma once

#include <iostream>
#include "binaryTree.h"

using namespace std;

class binaryExpressionTree : public binaryTreeType<string> {
public:
	void buildExpressionTree(string postFixExpr);
	double evaluateExpressionTree();

	bool search(const string& searchItem) const override;
	void insert(const string& insItem) override;
	void deleteNode(const string& delItem) override;
private:
	double evaluateExpressionTree(nodeType<string>* p);
};