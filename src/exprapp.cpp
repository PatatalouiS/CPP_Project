
#include "exprapp.hpp"
#include "utils.hpp"
#include "constants.hpp"
#include "expr.hpp"
#include "error.hpp"

#include <exception>

using namespace std;
using namespace BasicCharacters;

Memory ExprApp::memory{Memory()};

void ExprApp::run() {
    auto pipeIsUsed = !isatty(fileno(stdin));
    string line;

    while(true) {

        if(!pipeIsUsed) {
            cout << PROMPT;
        }

        while(true) {
            auto character = cin.get();

            if((character == CR) || (character == LF)) {
                break;
            }
            else if(character != EOF){
                line.push_back(character);
            }
            else { // handle ^D signal/EOF
                cout << endl;
                exit(EXIT_SUCCESS);
            }
        }

        if((line.empty() && pipeIsUsed)) {
            break;
        }

        if(!line.empty()) {
            string stringToEval = line;

            if(line.back() == SEMI) {
                stringToEval.pop_back();
            }

            try{
                Expr expr(stringToEval);
                auto result = expr.eval();

                if(line.back() != SEMI) {
                   cout << result << endl;
                }
            }
            catch(SyntaxError& err) {
                cerr << err.what() << endl;
            }
            catch(LexerError& err) {
                cerr << err.what() << endl;
            }
        }

        line.clear();
    }

    cin.clear();
}

void ExprApp::putVariable(const std::pair<std::string, double> &var) {
    auto find = memory.find(var.first);

    if(find != memory.end()) {
        find->second = var.second;
    }
    else {
        memory.insert(var);
    }
}

double ExprApp::getVariable(const string& name) {
    auto find = memory.find(name);


    if(find == memory.end()) {
        throw NoDefError("Syntax Error : ID \"" + name+
                           "\" is not defined !" );
    }

    return find->second;
}

bool ExprApp::isDefined(const string& name) {
    return memory.find(name) != memory.end();
}
