
#include "exprapp.hpp"
#include "utils.hpp"
#include "constants.hpp"
#include "expr.hpp"

#include <exception>

using namespace std;
using namespace BasicCharacters;

Memory ExprApp::memory{Memory()};

void ExprApp::run() {
    auto pipeIsUsed = InputUtils::pipe_is_used();
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

            Expr expr(stringToEval);
            auto result = expr.eval();

            if(line.back() != SEMI) {
               cout << result << endl;
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

void ExprApp::setVariable(const std::shared_ptr<ID> &tokenId) {
    auto id = tokenId->str();
    auto find = memory.find(id);

    try {
        if(find == memory.end()) {
            throw out_of_range("Out Of Range Error : ID \"" + id +
                               "\" is not defined !" );
        }
    }
    catch (out_of_range& err) {
        cerr << err.what() << endl;
    }

    tokenId->set(find->second);
}
