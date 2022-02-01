#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

int addNum (int& varX, int& varY, int& result)
{
    result = varY + varX;
    return result;
}

int subtractNum (int& varX, int& varY, int& result)
{
    result = varY - varX;
    return result;
}

int multiplyNum (int& varX, int& varY, int& result)
{
    result = varY * varX;
    return result;
}
int divideNum (int& varX, int& varY, int& result)
{
    result = varY / varX;
    return result;
}

bool divideByZero(int& varX)
{
    if(varX == 0)
    {
        return true;
    }
    return false;
}

int declarePrecedence(char operatorTypePrecedence)
{
    if (operatorTypePrecedence == '-' || operatorTypePrecedence == '+')
    {
        return 1;
    }
    else if (operatorTypePrecedence == '*' || operatorTypePrecedence == '/')
    {
        return 2;
    }
    return 0; 
}

bool applyPrecedence(char cone, char ctwo)
{
    int fOper = declarePrecedence(cone);
    int sOper = declarePrecedence(ctwo);
    bool hasHigherPrecedence = (fOper >= sOper);
    return (hasHigherPrecedence);
}

int infixToPostfixTranslation(string& infix, const Map& values, string& postfix, int numbers, int symbol, int p1, int p2)
{
    stack<char> converter;
    char openParen = '(';
    int i = 0;

    int pSymbol = 0;
    int fVal = 0;

    int pcount = 0;
    for (; i < infix.size(); i++)
    {
        if (infix[i] == openParen)
        {
            
          if(pSymbol == numbers || pSymbol == p2)
          {
              return 1;
          }
            
          converter.push(infix[i]);
            
          pcount++;
          pSymbol = p1;
            
        }
        
        else if(infix[i] == ')')
        {
            if(pSymbol == p1 )
            {
                return 1;
            }
            if(pSymbol == symbol)
            {
                return 1;
            }
            if(pSymbol == 0 )
            {
                return 1;
            }
            if(pcount <= 0)
            {
            return 1;
            }
            else
            {
            pcount--;
            }
            
            while(converter.size() != 0 && converter.top() != openParen)
            {
                postfix += converter.top();
                converter.pop();
            }
            
            converter.pop();
            pSymbol = p2;
            
        }
        else if(isalpha(infix[i]) && islower(infix[i]))
        {
            if(!values.contains(infix[i]))
            {
                fVal = 2;
            }
            if(pSymbol == p2 || pSymbol == numbers)
            {
                return 1;
            }
            pSymbol = numbers;
            postfix += infix[i];
        }
        else
        {
          switch(infix[i])
          {
            case '+':
            case '-':
            case '*':
            case '/':
                  
              if(pSymbol == 0 )
              {
                  return 1;
              }
              if(pSymbol == p1 )
              {
                  return 1;
              }
              if(pSymbol == symbol)
              {
                  return 1;
              }
              while(!converter.empty() && converter.top() != openParen && applyPrecedence(converter.top(),infix[i]))
              {
                postfix += converter.top();
                converter.pop();
              }
              converter.push(infix[i]);
              pSymbol = symbol;
              break;
                  
            case ' ':
                  
                continue;
                break;
                  
            default:
                  
              return 1;
          }
        }
      }
    if(pSymbol == symbol)
    {
        return 1;
    }
    if(pSymbol == p1)
    {
        return 1;
    }
    if(pSymbol == 0)
    {
        return 1;
    }
    if(pcount != 0)
    {
        return 1;
    }
    while(!converter.empty())
    {
        postfix += converter.top();
        converter.pop();
    }

    return fVal;
    
}

int evaluate(string infix, const Map& values, string& postfix, int& result)
{
    postfix = "";
    int i = 0;
    int correspondingValue;
    stack<int> finStack;

    int finResult = infixToPostfixTranslation(infix, values, postfix, 1, 2, 3, 4);
    if(finResult != 0)
    {
        return finResult;
    }
    while (i != postfix.size())
    {
    int result = 0;

    if(isalpha(postfix[i]) && islower(postfix[i]))
    {
        values.get(postfix[i], correspondingValue);
        finStack.push(correspondingValue);
    }
        
    else
    {
        int varX = finStack.top();
        finStack.pop();
        int varY = finStack.top();
        finStack.pop();
        
        switch (postfix[i])
        {
        case '+':
            addNum(varX, varY, result);
            break;
        case '-':
            subtractNum(varX, varY, result);
            break;
        case '*':
            multiplyNum(varX, varY, result);
            break;
        case '/':
            if(divideByZero(varX))
            {
                return 3;
            }
            divideNum(varX, varY, result);
            break;
          }
        
        finStack.push(result);
        }
        i++;
    }
    
    result = finStack.top();
    finStack.pop();
    return 0;
}


int main()
{
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
        m.insert(vars[k], vals[k]);
    string pf;
    int answer;
    assert(evaluate("a+ e", m, pf, answer) == 0  &&
                            pf == "ae+"  &&  answer == -6);
    answer = 999;
    assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()o", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(*o)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a*b", m, pf, answer) == 2  &&
                            pf == "ab*"  &&  answer == 999);
    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
                            pf == "yoau-*+"  &&  answer == -1);
    answer = 999;
    assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
                            pf == "oyy-/"  &&  answer == 999);
    assert(evaluate(" a  ", m, pf, answer) == 0  &&
                            pf == "a"  &&  answer == 3);
    assert(evaluate("((a))", m, pf, answer) == 0  &&
                            pf == "a"  &&  answer == 3);
    cout << "Passed all tests" << endl;
}

