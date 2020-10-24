#include "exprparser.hpp"
#include "binaryop.hpp"
#include "typealiases.hpp"

#include <stack>

using namespace std;

vector<Token*> ExprParser::parse(const vector<Token*>& tokens) {
    stack<Token*> stack;
        vector<Token*> out;

        for(auto& token : tokens) {
            // It's a litteral
            if(!token->isOperator()) {
                out.push_back(token);
            }// It's an operator
            else {

                BinaryOp* binaryOp = static_cast<BinaryOp*>(token);

                while(!stack.empty() &&
                    (*static_cast<BinaryOp*>(stack.top()) >= *binaryOp)){

                    out.push_back(stack.top());
                    stack.pop();
                }

                stack.push(token);
            }
        }

        while(!stack.empty()) {
            out.push_back(stack.top());
            stack.pop();
        }

        return out;
}
