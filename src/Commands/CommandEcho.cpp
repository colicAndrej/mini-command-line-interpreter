#include "Commands/CommandEcho.h"

string CommandEcho::execute(const vector<string>& args) {
    if (!args.empty())
        return args[0];
    return "";
}

void CommandEcho::validate(const vector<unique_ptr<Token>> &tokens) {
    matchOpt(tokens, false);
    matchArgs(tokens, {1});
}

bool CommandEcho::requiresArgument(const vector<unique_ptr<Token>>& tokens) {
    int n = numOfArgs(tokens);
    if (!hasOpt(tokens) && n == 0)
        return true;
    return false;
}