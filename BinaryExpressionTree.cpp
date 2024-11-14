#include <iostream>
#include <fstream>
#include <string>
#include "binaryExpression.h"

using namespace std;

int main() {
	ifstream input("RpnData.txt");
	ofstream output("RpnOutput.txt");

    // Check if files are successfully opened
    if (!input) {
        cerr << "Error opening input file." << endl;
        return 1;
    }
    if (!output) {
        cerr << "Error opening output file." << endl;
        return 1;
    }

    // Create an instance of binaryExpressionTree
    binaryExpressionTree exprTree;
    string expression;

    // Read each line (postfix expression) from the input file
    while (getline(input, expression)) {
        // Clear the tree before processing a new expression
        exprTree.destroyTree();

        // Build the expression tree based on the current postfix expression
        exprTree.buildExpressionTree(expression);

        // Evaluate the expression tree and get the result
        double result = exprTree.evaluateExpressionTree();

        // Write the result to the output file
        output << "Result of expression '" << expression << "': " << result << endl;
    }

    // Close the files
    input.close();
    output.close();

    cout << "Expression evaluations completed and results written to output file." << endl;

    return 0;
}