#include "setoperator.hpp"
#include "utils.hpp"
#include "exprapp.hpp"
#include <iostream>
#include "function.hpp"
#include "placeholder.hpp"

using namespace std;


namespace  {

Args concat(const Args& a, const Args& b) {
    auto result = a;
    for(auto& arg : b)
        result.push_back(arg);
    return result;
}

struct Bind {
    unsigned int valuePlaceHolder;
    unsigned int indexArg;
};

}

ValueExpr SetOperator::setNewVar(stack<AbstractToken_ptr> &stack) {
    auto value = get<double>(topAndPop(stack)->eval(stack));
    auto idToken = topAndPop(stack);
    assert(idToken->isID());
    ExprApp::putVariable({ idToken->str(), value});
    return value;
}

ValueExpr SetOperator::setNewFunction(stack<AbstractToken_ptr> &stack) {
    auto func = tokenCast_ptr<Func>(topAndPop(stack));

    // take first given args
    Args firstArgs;
    vector<Bind> placeHolders;

    for(unsigned int i = 0; i < func->nbArgs(); ++i) {
        auto tok = topAndPop(stack);
        auto val = get<double>(tok->eval(stack));

        if(tok->isPlaceHolder())   {
            Bind b;
            b.valuePlaceHolder = unsigned(val);
            b.indexArg = *func->nbArgs() -1 - i;
            placeHolders.push_back(b);
        }
        else {
            firstArgs.push_back(val);
        }
    }

    auto name = topAndPop(stack)->str();

    reverse(firstArgs.begin(), firstArgs.end());
    auto descriptor = func->getDescriptor();

    auto nbArgs = descriptor.variadic
            ? INT_MAX
            : descriptor.nbArgs - *func->nbArgs();

    FunctionDescriptor newFunction;

    newFunction.variadic = descriptor.variadic;



    if(!placeHolders.empty()) {
        newFunction.nbArgs =  placeHolders.size();
        newFunction.fct = [firstArgs, descriptor, placeHolders](const Args& lastArgs) -> double {

            Args args(descriptor.nbArgs, 0);

             for(auto& a : lastArgs)
                cout << "ARGLAST  " << a << endl;

            for(unsigned int i = 0; i < lastArgs.size(); ++i) {
                for(unsigned int p = 0; p < placeHolders.size(); ++p) {
                    auto placeholder = placeHolders[p];

                    cout << "P_VALUE " << placeholder.valuePlaceHolder;
                    cout << "P_INDEX " << placeholder.indexArg << endl;

                    if(placeHolders[p].valuePlaceHolder == (i + 1)) {
                        args[placeHolders[p].indexArg] = lastArgs[i];
                        break;
                    }
                }
            }

            for(auto& a : args)
               cout << "ARG " << a;

            for(unsigned int i = 0; i < args.size(); ++i) {
                bool isPlaceHolder= false;
                for(unsigned int p = 0; p < placeHolders.size(); ++p) {
                    if(placeHolders[p].indexArg == i) {
                        isPlaceHolder = true;
                        break;
                    }
                }
                if(!isPlaceHolder) {
                    args[i] = firstArgs[i - placeHolders.size()];
                }
            }

             cout << "HEY1" << endl;



            return descriptor.fct(move(args));
        };
    }
    else {
        newFunction.nbArgs = nbArgs;
        newFunction.fct = [firstArgs, descriptor](const Args& lastArgs) -> double {
            auto args = concat(firstArgs, lastArgs);
            return descriptor.fct(move(args));
        };
    }

    Func::putFunction(name, newFunction);
    auto res = make_pair(name, newFunction);
    return res;
}

ValueExpr SetOperator::eval(stack<AbstractToken_ptr>& stack) const {
    return stack.top()->isConst()
            ? setNewVar(stack)
            : setNewFunction(stack);
}

void SetOperator::print(std::ostream &out) const {
    out << "SET";
}
