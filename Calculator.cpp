#include <iostream>
#include <cmath>
#include "Calculator.h"

using namespace std;

Calculator::Calculator(char oper, int x, int y) {
    setExp(oper, x, y);
}

void Calculator::setExp(char oper, int x, int y) {
    m_x = x;
    m_y = y;
    m_oper = oper;
}

int Calculator::getResult() const {
    return m_result;
}

/*------------------------------------------------------------
	연산자, 피연산자 2개로 이루어진 단순한 산수
--------------------------------------------------------------*/
void Calculator::execute() {
	signed int max_value = 0x7fffffff;
	signed int min_value = 0x80000000;

    switch(m_oper) {
    case '+' :
		{
			if ((double)m_x + m_y > max_value || (double)m_x + m_y < min_value)
				m_result = 1;
			else
				m_result = m_x + m_y;
			
			break;
		}
    case '-' :
		{
			if ((double)m_x - m_y > max_value || (double)m_x - m_y < min_value)
				m_result = 1;
			else
				m_result = m_x - m_y;
			
			break;
		}
    case '*' :
		{
			if ((double)m_x * m_y > max_value || (double)m_x * m_y < min_value)
				m_result = 1;
			else
				m_result = m_x * m_y;
			
			break;
		}
    case '/' :
		{
			if (m_y == 0) 
				m_result = 1;
			else
				m_result = m_x / m_y; 
		
			break;
		}
    case '^' :
		{
			if (pow((double)m_x, (double)m_y) > max_value || pow((double)m_x, (double)m_y) < min_value)
				m_result = 1;
			else
				m_result = pow(m_x, m_y);
			
			break;
		}
    case '#' :
		{
			if ((m_x ^ m_y) > max_value || (m_x ^ m_y) < min_value)
				m_result = 1;
			else
				m_result = m_x ^ m_y;
			
			break;
		}
    default :
        m_result = 0;
    }
}