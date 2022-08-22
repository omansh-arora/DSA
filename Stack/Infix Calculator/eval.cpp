
#include "Scanner.h"
#include "Stack.h"

#include <iostream>

using namespace std;

void result(Stack<Token> &numstack, Stack<Token> &opstack){

    if (opstack.peek().tt == pltok)
    {
        int rhs = numstack.pop().val;
        int lhs = numstack.pop().val;
        opstack.pop();
        int result = 0;
        result = lhs + rhs;

        Token lhsT;
        lhsT.tt = integer;
        lhsT.val = result;
        lhsT.text = to_string(result);
        numstack.push(lhsT);
    }
    else if (opstack.peek().tt == mitok)
    {
        int rhs = numstack.pop().val;
        int lhs = numstack.pop().val;
        opstack.pop();
        int result = 0;
        result = lhs - rhs;
        
        Token lhsT;
        lhsT.tt = integer;
        lhsT.val = result;
        lhsT.text = to_string(result);
        numstack.push(lhsT);
    }
    else if (opstack.peek().tt == asttok)
    {
        int rhs = numstack.pop().val;
        int lhs = numstack.pop().val;
        opstack.pop();
        int result = 0;
        result = lhs * rhs;
        
        Token lhsT;
        lhsT.tt = integer;
        lhsT.val = result;
        lhsT.text = to_string(result);
        numstack.push(lhsT);
    }
    else if (opstack.peek().tt == slashtok)
    {
        int rhs = numstack.pop().val;
        int lhs = numstack.pop().val;
        opstack.pop();
        int result = 0;
        result = lhs / rhs;
        
        Token lhsT;
        lhsT.tt = integer;
        lhsT.val = result;
        lhsT.text = to_string(result);
        numstack.push(lhsT);
    }

}

int main()
{
    Scanner S(cin);
    Token t;

    Stack<Token> numstack, opstack; // 2x Stacks of type Token

    t = S.getnext();

    while (t.tt != eof || !opstack.isEmpty())
    {
        if (t.tt == integer)
        {
            numstack.push(t);
            t = S.getnext();
        }
        else if (t.tt == lptok)
        {
            opstack.push(t);
            t = S.getnext();
        }
        else if (t.tt == rptok)
        {
            if (opstack.peek().tt == lptok)
            {
                opstack.pop();
                t = S.getnext();
            }
            else
            {
                result(numstack,opstack);
            }
        }
        else if (t.tt == pltok || t.tt == mitok || t.tt == eof)
        {

            if (!opstack.isEmpty() && (opstack.peek().tt == pltok ||
                opstack.peek().tt == mitok || opstack.peek().tt == asttok
                || opstack.peek().tt == slashtok))
            {
                result(numstack,opstack);
            }
            else
            {
                opstack.push(t);
                t = S.getnext();
            }
        }
        else if (t.tt == asttok || t.tt == slashtok)
        {
            if (!opstack.isEmpty() && (opstack.peek().tt == asttok || opstack.peek().tt == slashtok))
            {
                result(numstack,opstack);
            }
            else
            {
                opstack.push(t);
                t = S.getnext();
            }
        }
    }

    cout << "\nAnswer: " << numstack.peek().val << endl;

    return 0;
}


