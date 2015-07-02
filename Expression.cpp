#include <iostream>
#include <sstream>
#include <cmath>

#include "Expression.h"
#include "Calculator.h"

using namespace std;

Expression::Expression(string exp) {
	setExp(exp);
	m_rslt = 0.0;
}

string Expression::getExp() const {
	return m_exp;
}

string Expression::getOriExp() const {
	return m_oriExp;
}

void Expression::setExp(string exp) {
	m_exp = exp;
	m_oriExp = exp;
}

int Expression::getResult() const {
	return m_rslt;
}

string Expression::getInnerExp(int* st, int* en) const {
    string::size_type open_bracket;
    string::size_type close_bracket;
	string innerExp;

    close_bracket = m_exp.find(")");
    open_bracket = m_exp.rfind("(", close_bracket);

	if (close_bracket == string::npos) {
		innerExp = m_exp;
		*st = 0;
		*en = m_exp.length()-1;
	} else {
		innerExp = m_exp.substr(open_bracket+1, close_bracket-(open_bracket+1));
		*st = open_bracket;
		*en = close_bracket;
	}

    return innerExp;
}

void Expression::calculate() {
	string inner_exp;
	string::size_type p_oper = string::npos;

	int st;
	int en;

	int priority = 1;
	char oper;
	int x = 0, y = 0;
	
    while (isExistOperator(m_exp)) {
		priority = 1;
		inner_exp = getInnerExp(&st, &en);

		while (priority <= OPER_RANGE) {
			p_oper = findWithPriority(inner_exp, priority);

			if (p_oper == string::npos) {
				priority++;
				continue;
			}

			oper = inner_exp[p_oper];
			x = atoi(inner_exp.substr((getNextOperator(inner_exp, p_oper-1, -1) < 0 ? 0 : getNextOperator(inner_exp, p_oper-1, -1)+1), p_oper).c_str());
			y = atoi(inner_exp.substr(p_oper+1, (getNextOperator(inner_exp, p_oper+1, 1) >= inner_exp.length() ? inner_exp.length()-1 : getNextOperator(inner_exp, p_oper+1, 1))).c_str());

			Calculator cal(oper, x, y);
			cal.execute();

			cout << " x " << oper << " y = " << x << oper << y << endl;
			cout << "befo inner_exp : " << inner_exp << endl;
			replaceExp(inner_exp, (getNextOperator(inner_exp, p_oper-1, -1) < 0 ? 0 : getNextOperator(inner_exp, p_oper-1, -1)+1), (getNextOperator(inner_exp, p_oper+1, 1) >= inner_exp.length() ? inner_exp.length()-1 : getNextOperator(inner_exp, p_oper+1, 1)-1), toString(cal.getResult()));
			cout << "aftr inner_exp : " << inner_exp << endl;
		}
	
		replaceExp(m_exp, st, en, inner_exp);
    }

	m_rslt = atoi(m_exp.c_str());
}

bool Expression::isOperator(string exp, const int pos) const {
	bool b_rtn;

	if (exp[pos] >= '0' && exp[pos] <= '9') {
		b_rtn = false;
	} else {
		if (exp[pos] == '+' || exp[pos] == '-') {
			if (isOperator(exp, pos-1)) 
				b_rtn = false;
			else
				b_rtn = true;
		} else if (exp[pos] == '.') {
			b_rtn = false;
		} else {
			b_rtn = true;
		}
	}

	return b_rtn;
}

bool Expression::isExistOperator(string exp) const {
	string::size_type expLen = exp.length();
	int  nCnt = 0;

	string::size_type pos = 0;
	while (pos < expLen) {
		if (isOperator(exp, pos)) {
			nCnt++;
			break;
		}

		pos++;
	}

	if (nCnt == 0)
		return false;
	else
		return true;
}

void Expression::replaceExp(string& exp, const int st, const int en, string chg_exp) {
	exp.replace(st, en-st+1, chg_exp);
}

string Expression::toString(int number) {
	ostringstream sout;

	sout << number;

	return sout.str();
}

int Expression::getPriority(char oper) {
	int nPriority = 0;

    switch(oper) {
    case '^' : nPriority = 1; break;
    case '*' : nPriority = 2; break;
    case '/' : nPriority = 2; break;
    case '+' : nPriority = 3; break;
    case '-' : nPriority = 3; break;
    case '#' : nPriority = 4; break;
    default  : break;
    }

    return nPriority;
}

int Expression::findWithPriority(string exp, int priority) {
	string::size_type pos = string::npos;

	switch(priority) {
	case 1 : pos = exp.find("^"); break;
	case 2 : 
		{
			string::size_type pos_m = 0;    /* * 위치 */
			string::size_type pos_d = 0;    /* / 위치 */

			pos_m = exp.find("*");
			pos_d = exp.find("/");

			if (pos_m == string::npos && pos_d == string::npos) {
				pos = string::npos;
			} else if (pos_m < pos_d || pos_d == string::npos) {
				pos = pos_m;
			} else if (pos_m > pos_d || pos_m == string::npos) {
				pos = pos_d;
			}

			break;
		}
	case 3 : 
		{
			string::size_type pos_p = 0;	/* + 위치 */
			string::size_type pos_m = 0;	/* - 위치 */
			while(true) {
				pos_p = exp.find("+", pos_p);			

				if (isOperator(exp, pos_p) || pos_p == string::npos) {
					break;
				}
				pos_p++;
			}

			while(true) {
				pos_m = exp.find("-", pos_m);

				if (isOperator(exp, pos_m) || pos_m == string::npos) {
					break;
				}
				pos_m++;
			}

			if (pos_p == string::npos && pos_m == string::npos) {
				pos = string::npos;
			} else if (pos_p < pos_m || pos_m == string::npos) {
				pos = pos_p;
			} else if (pos_p > pos_m || pos_p == string::npos) {
				pos = pos_m;
			} 

			break;
		}
	case 4 : pos = exp.find("#"); break;
	default : break;
	}

	return pos;
}

/* -------------------------------------------------
    다음 연산자 위치
--------------------------------------------------*/
int Expression::getNextOperator(string exp, int std_pos, int f_direction) {
    string::size_type pos = std_pos;
    
    while(true) {
        if (isOperator(exp, pos)) 
	        break;

        if (f_direction > 0)
            pos++;
	    else
	        pos--;
    }

    return pos;
}
