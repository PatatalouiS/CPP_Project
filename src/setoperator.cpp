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

struct BindInfo {
    unsigned int valuePlaceHolder;
    unsigned int indexArg;
};

pair<Args, vector<BindInfo>> parseArgs_PlaceHolders(Func_ptr& func,
                                                stack<AbstractToken_ptr>& stack) {
    Args firstArgs;
    vector<BindInfo> placeHolders;

    for(unsigned int i = 0; i < *func->nbArgs(); ++i) {
        auto token = topAndPop(stack);
        auto value = get<double>(token->eval(stack));

        if(token->isPlaceHolder())   {
            BindInfo b;
            b.valuePlaceHolder = unsigned(value);
            b.indexArg = *func->nbArgs() -1 - i;
            placeHolders.emplace_back(b);
        }
        else {
            firstArgs.push_back(value);
        }
    }

    reverse(firstArgs.begin(), firstArgs.end());

    return { move(firstArgs), move(placeHolders) };
}

FunctionDescriptor buildCurryfiedFunc (const Args& firstArgs,
                                   const Func_ptr& func) {
    auto& baseDescriptor = func->getDescriptor();

    if(baseDescriptor.variadic) {
        throw EvalError("Eval Error : Variadic functions are not valid"
                        " for curryfication");
    }

    FunctionDescriptor newFunction;
    newFunction.variadic = baseDescriptor.variadic;
    newFunction.nbArgs = baseDescriptor.nbArgs - *func->nbArgs();

    newFunction.fct = [firstArgs, baseDescriptor](const Args& lastArgs) -> double {
        auto args = concat(firstArgs, lastArgs);
        return baseDescriptor.fct(move(args));
    };

    return newFunction;
}

FunctionDescriptor buildPlaceHoldedFunc (const Args& firstArgs,
                                     const Func_ptr& func,
                                     const vector<BindInfo>& placeHolders) {
    auto& baseDescriptor = func->getDescriptor();
    FunctionDescriptor newFunction;
    newFunction.variadic = baseDescriptor.variadic;
    newFunction.nbArgs = placeHolders.size();

    newFunction.fct = [func, firstArgs, baseDescriptor, placeHolders](const Args& lastArgs) -> double {
        Args args(*func->nbArgs());
        auto itArgs = firstArgs.begin();

        for(unsigned int i = 0; i < args.size(); ++i) {
            bool isPlaceHolder = false;
            for(unsigned int ph = 0; ph < placeHolders.size(); ++ph) {
                auto& currentPH = placeHolders[ph];
                if(currentPH.indexArg == i) {
                    args[currentPH.indexArg] = lastArgs[currentPH.valuePlaceHolder - 1];
                    isPlaceHolder = true;
                    break;
                }
            }
            if(!isPlaceHolder)
                args[i] = *itArgs++;
        }
        return baseDescriptor.fct(move(args));
    };
    return newFunction;
}

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
    auto args_placeholders = parseArgs_PlaceHolders(func, stack);
    auto& firstArgs = args_placeholders.first;
    auto& placeHolders = args_placeholders.second;
    auto name = topAndPop(stack)->str();

    FunctionDescriptor newFunction = !placeHolders.empty()
            ? buildPlaceHoldedFunc(firstArgs, func, placeHolders)
            : buildCurryfiedFunc(firstArgs, func);

    Func::putFunction(name, newFunction);
    auto result = make_pair(name, move(newFunction));
    return result;
}

ValueExpr SetOperator::eval(stack<AbstractToken_ptr>& stack) const {
    return stack.top()->isConst()
            ? setNewVar(stack)
            : setNewFunction(stack);
}

void SetOperator::print(std::ostream &out) const {
    out << "SET";
}
