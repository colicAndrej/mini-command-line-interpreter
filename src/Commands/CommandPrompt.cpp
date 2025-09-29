#include "Commands/CommandPrompt.h"

string prompt = "$";

string Prompt::execute(const vector<string>& args) {
    prompt = args[0];
    return "";
}

void Prompt::validate(const vector<unique_ptr<Token>> &tokens) {
    matchOpt(tokens, false);
    matchArgs(tokens, {1});
    if (tokens[0]->getType() != "argument")
        throw SemanticErrorCommand("Prompt argument must be given enclosed in quotation marks");
}

bool Prompt::requiresArgument(const vector<unique_ptr<Token>>& tokens) {
    int n = numOfArgs(tokens);
    if (!hasOpt(tokens) && n == 0)
        return true;
    return false;
}