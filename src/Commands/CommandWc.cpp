#include "Commands/CommandWc.h"

string CommandWc::execute(const vector<string>& args) {
    string opt = args[0];
    string argument = "";
    if (args.size() > 1)
        argument = args[1];
    if (opt == "-w") {
        int count = 0;
        bool inWord = false;
        for (char c : argument) {
            if (isspace(c)) {
                inWord = false;
            }
            else if (!inWord) {
                inWord = true;
                count++;
            }
        }
        return to_string(count);
    }
    if(opt == "-c") {
        int count = 0;
        for (char c : argument)
            count++;
        return to_string(count);
    }
    throw InvalidOptionError(opt);
}

void CommandWc::validate(const vector<unique_ptr<Token>> &tokens) {
    matchOpt(tokens, true);
    matchArgs(tokens, {1});
    string opt = tokens[0]->getData();
    if (opt != "-w" && opt != "-c")
        throw InvalidOptionError(opt);
}

bool CommandWc::requiresArgument(const vector<unique_ptr<Token>>& tokens) {
    int n = numOfArgs(tokens);
    if (hasOpt(tokens) && n == 0)
        return true;
    return false;
}