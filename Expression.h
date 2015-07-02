#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
using namespace std;

#define OPER_RANGE 4

class Expression {
private :
	string m_oriExp;
    string m_exp; 
    int m_rslt;

public :
    explicit Expression(string exp);
    string getExp() const;
	string getOriExp() const;
    void setExp(string exp);
    int getResult() const;
    string getInnerExp(int* st, int* en) const;
	void calculate();

private :
    bool isOperator(string exp, const int pos) const;
    bool isExistOperator(string exp) const;
	void replaceExp(string& exp, const int st, const int en, string chg_exp);
	string toString(int number);
	int getPriority(char oper);
	int findWithPriority(string exp, int priority);
	int getNextOperator(string exp, int std_pos, int f_direction);

};

#endif
