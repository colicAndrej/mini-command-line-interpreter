#include "Commands/CommandHead.h"

string CommandHead::execute(const vector<string>& args) {
    string nStr;
    for (int i = 2; i < args[0].size();i++)
        nStr += args[0][i];
    int n = stoi(nStr);
    if (n == 0)
        return "";
    string res;
    int i = 0;
    int count = 0;
    string arg = args[1];
    for (; i < arg.size(); i++) {
        if (arg[i] == '\n') {
            count++;
            if (count == n)
                break;
        }
    }

    return arg.substr(0, i);
}

void CommandHead::validate(const vector<unique_ptr<Token>> &tokens) {
    matchOpt(tokens, true);
    matchArgs(tokens, {1});
    string opt = tokens[0]->getData();
    if (opt.length() > 2 && opt.length() <= 7 && opt[1] == 'n') {
        for (int i = 2; i < opt.length(); i++) {
            if (!isdigit(opt[i]))
                throw InvalidOptionError(opt);
        }
    }
    else
        throw InvalidOptionError(opt);
}

bool CommandHead::requiresArgument(const vector<unique_ptr<Token>>& tokens) {
    int n = numOfArgs(tokens);
    if (hasOpt(tokens) && n == 0)
        return true;
    return false;
}