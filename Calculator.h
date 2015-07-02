#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator {
private :
    char m_oper;
    int m_x;
    int m_y;
    int m_result;    

public :
    explicit Calculator(char oper, int x, int y);
    void setExp(char oper, int x, int y);
    void execute();
    int getResult() const;
};

#endif