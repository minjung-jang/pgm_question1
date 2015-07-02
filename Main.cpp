#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Calculator.h"
#include "Expression.h"
using namespace std;

string toString(double);

void main(int argc, char *argv[]) {

	if (argc < 2) {
		cout << "execute : Program.exe file.txt" << endl;
		exit(-1);
	}

	ifstream in;
	in.open(argv[1]);

	string expression;
	getline(in, expression);

	Expression exp(expression);
	exp.calculate();

	cout << "°á°ú : " << exp.getResult() << endl;
}
