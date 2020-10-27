
#include "exprapp.hpp"
#include "utils.hpp"
#include "constants.hpp"
#include "expr.hpp"

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

        if(!line.empty() && (line.back() != SEMI)) {
            Expr expr(line);
            cout << expr.eval() << endl;
        }
        else {

        }
        line.clear();
    }

    cin.clear();
}

void ExprApp::putVariable(const std::pair<std::string, double> &var) {
    memory.insert(var);
}
